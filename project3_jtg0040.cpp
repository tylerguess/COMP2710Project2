/*
* project3_jtg0040.cpp
* John Guess
* jtg0040
* Project 3
* I used the sample code and the project 3 practice in my code.
* Compile using g++ command.
*/

#include <assert.h>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
// int* arr1 = new int[100];
// int* arr2 = new int[100];
// int* arr3 = new int[100];
const int MAX_SIZE = 100;

/* Checks if file is valid.
* Input: string is the name of the file.
* Return: boolea value of if the file is valid.
*/
bool checkFile(string);

/*
* Reads the file into an array.
* Input: inputArray[] The array storing data
* instream input file stream
* Return: size of the array.
*/
int readFile(int inputArray[], ifstream& instream);

/*
* Writes the array to a file.
* Input: intputArray[] is the input array.
* outStream is the output file stream.
*/
void writeFile(int inputArray[], ofstream& outStream, int arraySize);

/*
* Merges two arrays together.
* Input: array1[] is the first array.
* size1 is the size of array1.
* array2[] is the second array.
* size2 is the size of array2.
* array3[] is the output array.
* Return: Size of array3.
*/
int merge(int array1[], int size1, int array2[], int size2, int array3[]);

/*
* This is a test driver for checkFile()
*/
void testCheckFile();

/*
* This is a test driver for readFile()
*/
void testReadFile();

/*
* This is a test driver for writeFile()
*/
void testWriteFile();

/*
* This is a test driver for merge()
*/
void testMerge();

/*
* Merge the numbers in two specified files and write all the numbers
* to a specified third file in ascending order.
*
* Return: 1 Program completed successfully. (int)
*/
int main() {
  cout << "*** Unit Test Cases ***\n";
  testCheckFile();
  cout << "\t...\nPress any key to continue...\n\n";
  cin.ignore().get();
  testReadFile();
  cout << "\t...\nPress any key to continue...\n\n";
  cin.ignore().get();
  testWriteFile();
  cout << "\t...\nPress any key to continue...\n\n";
  cin.ignore().get();
  testMerge();
  cout << "\t...\nPress any key to continue...\n\n";
  cin.ignore().get();
  cout << "*** Welcome to John's sorting program ***\n";

  string input1;
  do {
    cout << "Enter the first input file name: ";
    cin >> input1;
  } while (cin.fail() || !checkFile(input1));

  ifstream inStream1;
  int iArray1[MAX_SIZE];
  int iArray1_size;
  inStream1.open(input1);
  iArray1_size = readFile(iArray1, inStream1);
  cout << "\nThe list of " << iArray1_size << " numbers in file ";
  cout << input1 << " is:\n";
  for (int i = 1; i <= iArray1_size; i++) {
    cout << iArray1[i] << "\n";
  }


  string input2;
  cout << "\n";
  do {
    cout << "Enter the second input file name: ";
    cin >> input2;
  } while (cin.fail() || !checkFile(input2));
  ifstream inStream2;
  int iArray2[MAX_SIZE];
  int iArray2_size;
  inStream2.open(input2);
  iArray2_size = readFile(iArray2, inStream2);
  cout << "The list of " << iArray2_size << " numbers in file ";
  cout << input2 << " is:\n";
  for (int i = 1; i <= iArray2_size; i++) {
    cout << iArray2[i] << "\n";
  }

  int oArray[2 * MAX_SIZE];
  int oArray_size;
  oArray_size = merge(iArray1, iArray1_size, iArray2, iArray2_size, oArray);
  cout << "\nThe sorted list of " << oArray_size << " numbers is: ";
  for (int i = 1; i <= oArray_size; i++) {
    cout << oArray[i] << " ";
  }

  string output;
  cout << "\n";
  do {
    cout << "Enter the output file name: ";
    cin >> output;
  } while (cin.fail() || !checkFile(output));
  ofstream outStream;
  outStream.open(output);
  writeFile(oArray, outStream, oArray_size);
  cout << "*** Please check the new file - " << output << " ***\n";
  cout << "*** Goodbye. ***\n";


  inStream1.close();
  inStream2.close();
  outStream.close();
  return 1;
}

bool checkFile(string file) {
  ifstream stream;
  stream.open(file.c_str());
  if (stream.fail()) {
    return false;
  }
  stream.close();
  return true;
}

void testCheckFile() {
  cout << "Unit Test Case 1: checkFile() - \n\tCase 1.1: Valid file.\n";
   assert(true == checkFile("input1.txt"));
   cout << "\tCase 1.1 passed\n";
   cout << "\tCase 1.2: Invalid file.\n";
   assert (false == checkFile("invalidFile.txt"));
   cout << "\tCase 1.2 passed\n";
}

int readFile(int inputArray[], ifstream& inStream) {
  int index = 1;

  inStream >> inputArray[index];
  while (! inStream.eof()) {
    index++;
    inStream >> inputArray[index];
  }
  return index;
}

void testReadFile() {
  ifstream inStream1;
  int iArray1[MAX_SIZE];
  int iArray1_size;
  inStream1.open("input1.txt");
  cout << "Unit Test Case 2: readFile() - \n\tCase 2.1: Read input1.txt\n";
  iArray1_size = readFile(iArray1, inStream1);
  assert(6 == iArray1_size);
  cout << "\tCase 2.1 passed\n";
  inStream1.close();
  inStream1.open("input2.txt");
  cout << "\tCase 2.2: Read input2.txt\n";
  assert(5 == readFile(iArray1, inStream1));
  inStream1.close();
  cout << "\tCase 2.2 passed\n";
}

void writeFile(int outputArray[], ofstream& outStream, int arraySize) {
  for (int i = 1; i <= arraySize; i++) {
    outStream << outputArray[i] << "\n";
  }
}

void testWriteFile() {
  ofstream outStream1;
  outStream1.open("output.txt");
  int outputArray[5] = {-1, 2, 3, 4, 5};
  cout << "Unit Test Case 3: writeFile() - \n\tCase 3.1: Write to output.txt\n";
  writeFile(outputArray, outStream1, 4);
  outStream1.close();
}

int merge(int array1[], int size1, int array2[], int size2, int array3[]) {
  if (size1 == 0) {
    array3 = array2;
    return 0;
  } else if (size2 == 0) {
    array3 = array1;
    return 0;
  }
  int index1 = 1;
  int index2 = 1;
  int index3 = 1;
  int maxComparisons;
  while (index1 <= size1 && index2 <= size2) {
    if(array1[index1] < array2[index2]) {
      array3[index3] = array1[index1];
      index1++;
      index3++;
    } else {
      array3[index3] = array2[index2];
      index2++;
      index3++;
    }
  }

  if (index1 <= size1) {
    while (index1 <= size1) {
      array3[index3] = array1[index1];
      index1++;
      index3++;
    }
  } else if (index2 <= size2) {
    while (index2 <= size2) {
      array3[index3] = array2[index2];
      index2++;
      index3++;
    }
  }
  return size1 + size2;
}

void testMerge() {
  int array1[MAX_SIZE] = {-1, 5, 7, 9, 10};
  int array2[MAX_SIZE] = {-1, 6, 8, 11, 12};
  int size1 = 4;
  int size2 = 4;
  int array3[MAX_SIZE];
  merge(array1, size1, array2, size2, array3);
  cout << "Unit Test Case 4: merge() - \n\tCase 4.1: Two arrays of size 4\n";
  assert(array3[1] == 5);
  cout << "\tCase 4.1 passed\n";
  cout << "\tCase 4.2: One empty, one nonempty array\n";
  int array4[MAX_SIZE];
  int array5[MAX_SIZE];
  merge (array1, size1, array4, 0, array5);
  assert(array3[1] == 5);
  cout << "\tCase 4.2 passed\n";
}
