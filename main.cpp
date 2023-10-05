// Project 1 (in c++):  Histogrm and thresholding.
// CSCI 381: Computer Vision
// Shane Wynne
// 02/13/2022
// compile g++ -std=c++11 main.cpp -o a.out
// ./a.out data
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
streamoff start = 0;
int* histAry = NULL;
int numRows = 0, numCols = 0,minVal = 0,maxVal = 0;//thresholdValue = 0; Not used-thrVal
streamoff* length = NULL;
//g++ -std=c++11 main.cpp
// ./a.out Project1_data1.txt 6 outFile1.txt outFile2.txt outFile3.txt outFile4.txt
// ./a.out Project1_data2.txt 30 outFile1.txt outFile2.txt outFile3.txt outFile4.txt

void ComputeHist(istream& inFile){ //argv[1]
    while (!inFile.eof()) {
        int val;
        inFile >> val;
        histAry[val]++;
    }
}


void printHist(ostream& outFile1){ //argv[3]
    outFile1 << numRows << ' ' << numCols << ' ' << minVal << ' ' << maxVal << endl;
    for(int i = 0; i <= maxVal; i++){
        outFile1 << i << " " << histAry[i] << endl;
    }
    outFile1 << endl;
}

void dispHist(ostream& outFile2){ //argv[4]
    for(int i = 0; i <= maxVal; i++){
        outFile2 << i << " (" << histAry[i] << "):";
        for(int y = 0; y < histAry[i]; y++){
            outFile2 << "+";
            if(y == 70){
                break;
            }
        }
        outFile2<<endl;
    }
}

void threshold(istream& inFile, ostream& outFile3, ostream& outFile4, int thrVal){ //argv[5] argv[6]
    minVal = 0;
    maxVal = 1;
    int count = 0;
    outFile3 << numRows << ' ' << numCols << ' ' << minVal << ' ' << maxVal << endl;
    outFile4 << numRows << ' ' << numCols << ' ' << minVal << ' ' << maxVal << endl;
    
    while (!inFile.eof()) {
        int pixelVal;
        inFile >> pixelVal;
        count++;
        
        if(pixelVal >= thrVal){
            outFile3 << '1' << ' ';
            outFile4 << '1' << ' ';
            if(count % numCols == 0 ){
                outFile3 << endl;
                outFile4 << endl;

            }
        }
        else{
            outFile3 << '0' << ' ';
            outFile4 << '.' << ' ';
            if(count % numCols == 0 ){
                outFile3 << endl;
                outFile4 << endl;
            }
        }
    }
}

int main(int argc, const char * argv[]) {
//STEP 0:
    if (argc < 2){
        cerr << "Please Insert Data";
        return EXIT_FAILURE;
    }
    if (argc < 3){
        cerr << "Please Insert number for the Threshold";
        return EXIT_FAILURE;
    }
    int thrVal = atoi(argv[2]); //argv[2]
    if(thrVal == 0){
        cerr << "Please Insert a number for the Threshold";
        return EXIT_FAILURE;
    }
    ifstream inFile(argv[1]);
    ofstream outFile1("Threshold_"+ to_string(thrVal) +"/histogram_Threshold_" + to_string(thrVal) + ".txt"), outFile2("Threshold_"+ to_string(thrVal) +"/histogram_display_plus_" + to_string(thrVal) + ".txt"), outFile3("Threshold_"+ to_string(thrVal) +"/binary_image_" + to_string(thrVal) + ".txt"), outFile4("Threshold_"+ to_string(thrVal) +"/display_image_" + to_string(thrVal) + ".txt");
    if (!inFile.is_open()) {
        cerr << "Could not open the inFile - '";
        return EXIT_FAILURE;
    }
   // Threshold_6/data1
//STEP 1:
    int tmp = 0;
    inFile >> tmp;
    numRows = tmp;
    
    inFile >> tmp;
    numCols = tmp;
    
    inFile >> tmp;
    minVal = tmp;
    
    inFile >> tmp;
    maxVal = tmp;
    start = inFile.tellg();
//STEP 2:
    histAry = new int[maxVal+1];
    //histAry = {0};

//STEP 3:
ComputeHist(inFile);

//STEP 4:
printHist(outFile1);

//STEP 5:
dispHist(outFile2);
    
//STEP 6:
inFile.close();
inFile.clear();
inFile.open(argv[1]);
inFile.seekg(9);

//STEP 7:
outFile3 << "The threshold value uses is " << thrVal<<endl;
outFile4 << "The threshold value uses is " << thrVal<<endl;
    
//STEP 8:
threshold(inFile, outFile3, outFile4, thrVal);

//STEP 9:
inFile.close();
outFile1.close();
outFile2.close();
outFile3.close();
outFile4.close();
//delete histAry;
    
return 0;
    
}
