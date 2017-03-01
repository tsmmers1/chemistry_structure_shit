#include <iostream>
#include <string>
#include <fstream>

#include "main.h"
#include "bond_angle.cpp"
// #include "bond_length.cpp"

using namespace std;
/**
 * @mainpage The Gaussian Optimization Analytical Tool (GOAT)
 *
 * Welcome to the Gaussian Optimization Analytical Tool (GOAT) documentation site! 
 * Users may find relevant info related to this program, a program designed to provide
 * structural analyses of biomolecules successfully optimized using Gaussian software.
 *
 * @short   Main program
 * @file    main.cpp
 * @author  Kate Charbonnet, Hannah Lozano, and Thomas Summers
 * @param   none
 * @return  0 on success
 *
 * The purpose of this program is to provide preliminary structural information on biomolecules
 * optimized using Gaussian computational chemistry software.  Structural and chemical properties 
 * identified include: element identification, bond length, bond order, central angles, and torsional
 * angles.  Input of the file to be analyzed will result in an output file listing all the structural
 * information of the biomolecule.
 */

int main(int argc, char* argv[]) {
    ifstream inputfile;
    ofstream logfile;
    ifstream bond_angle;
    string line;
    unsigned int count_line = 0;
    unsigned int total_lines = 0; 
    string header1 = "Redundant internal coordinates found in file";
    string footer1 = "Recover connectivity data from disk.";
    string print(string);

    //Check that input file was directed into the command line
    if (argc < 2) {
        cout << "Error: Inputfile not specified in command line\n";
        return 1;
    }

    //Open the input file and check that it opened
    inputfile.open(argv[1]);
    if (!inputfile.is_open()) {
        cout << "Error: Unable to open the input file.";
        return 2;
    }

    //Generate a log file and check that it opened
    logfile.open("log.txt");
    if (!logfile.is_open()) {
        cout << "Error: Unable to open the logfile.";
        return 3;
    } else {
        logfile << "Logfile for Gaussian Optimization Analytical Tool\n";
    }

    //Search the input file for the first keywords
    while (getline(inputfile, line)) {
        count_line++;
        if (line.find(header1, 0) != string::npos) {
            cout << "Found: " << header1 << " at position " << count_line << endl;
            logfile << "Found: " << header1 << " at position " << count_line << endl;	
	    for (int i = 1; i > 0; ++i) {
               logfile << line << "\n";
               getline (inputfile, line);
	       if (line.find(footer1, 0) != string::npos) {
		       cout << "Found: " << footer1 << endl;
		       logfile << "Found: " << footer1 << endl;
		       break;
	       }		
            }
        }
    }
    inputfile.close();
    cout << "Search Complete\n";
    logfile << "Search Complete" << endl;
    logfile.close();

    //Open the file bond_angle.cpp and check that it opened
    bond_angle.open("bond_angle.cpp");
    if (!bond_angle.is_open()) {
        cout << "Error: Unable to open bond_angle file.";
        return 1;
    }
    //Close the file bond_angle.cpp
    bond_angle.close();
    cout << "Bond angle calculation complete.";
    return 0;
}
