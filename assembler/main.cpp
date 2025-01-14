#include <bits/stdc++.h>
#include "globals.h"
#include "conversions.h"
using namespace std;

/* Opens the file and reads it, creates a table of tokens (no spaces) */
void splitFile(char *filename){
    ifstream file;
    file.open(filename);

    if(!file.is_open()){ //If the file does not exist the program crashes.
        cout << "Failed to open the file!" << endl;
        exit(EXIT_FAILURE);
    }

    else{
        int i = 0;
        char temp;

        while (!file.eof()){
            file.get(temp);
            tokens.push_back(temp);

            i++;
            tSize++;
        }
        i = 0;
        tSize--;

        ofstream dataFile;
        dataFile.open("tempFiles/dataFile.txt");
        for(i = 6; i < tSize; i++){
            if(tokens[i]=='.' && tokens[i+1]=='t' && tokens[i+2] == 'e' && tokens[i+3] == 'x' && tokens[i+4] == 't')//cant have less than one instruction
                break;
            dataFile << tokens[i] << "";
        }

        ofstream textFile;
        textFile.open("tempFiles/textFile.txt");
        i=i+24;
        for(; i < tSize; i++){
            textFile << tokens[i] << "";
        }
    }
}

void openTextFile(){
    ifstream file;
    file.open("tempFiles/textFile.txt");

    if(!file.is_open()){ //If the file does not exist the program crashes.
        cout << "Failed to open the file!" << endl;
        exit(EXIT_FAILURE);
    }

    else{
        int i = 0;
        char temp;

        while (!file.eof()){
            file.get(temp);
            textTokens.push_back(temp);

            i++;
            tokenSize++;
        }
        i = 0;
        tokenSize--;
    }
}

void openDataFile(){
    ifstream file;
    file.open("tempFiles/dataFile.txt");

    if(!file.is_open()){ //If the file does not exist the program crashes.
        cout << "Failed to open the file!" << endl;
        exit(EXIT_FAILURE);
    }

    else{
        int i = 0;
        char temp;

        while (!file.eof()){
            file.get(temp);
            dataTokens.push_back(temp);

            i++;
            tokenSize_data++;
        }
        i = 0;
        tokenSize_data--;
    }
}

/* The immdiateTable function handles the immediate values of I-type instructions */
string immediateTable(int &numberOfSymbols, int &symbolCounter){
    string temp;

    if(symbolCounter == numberOfSymbols){ //Check for overflow of 'symbols' vector.
        return "";
    }

    symbolCounter++; //Increment counter to the immediate value symbol.
    string temp_symbol = symbols[symbolCounter]; //Store the value symbol in a temporary variable.

    temp = hex2bin(temp_symbol); //Convert the symbol to binary (since it was in hex) and concatenate to the rest of the binary string.

    return temp;
}

/* The branchTable function handles the branch address for branch instructions. */
string branchTable(int &numberOfSymbols, int &symbolCounter, string &temp, int &labelsCounter, int &lineCounter){
    int offset = 0;
    string bin;

    if(symbolCounter == numberOfSymbols){ //Check for overflow of 'symbols' vector.
        return "";
    }

    symbolCounter++; //Increment counter to the branch address symbol.
    string temp_symbol = symbols[symbolCounter]; //Store the branch address symbol in a temporary variable.

    for(int i = 0; i < labelsCounter; i++){ //Search the label vector (That we made in pass 1) for the branch label.
        if(label[i].name == temp_symbol){
            if(label[i].address >  lineCounter){
                offset = (label[i].address - lineCounter) - 1;
            }
            else{
                offset = -((lineCounter - label[i].address));
            }

            //After finding it we turn it into binary form.
            bin = dec2bin(offset);
            temp = temp + bin;
            break;
        }
    }


    return temp; //We return the address in binary form to be added to the rest of the branch instruction.
}

/*The registerTable handles register symbols, matching them with the correct registers*/
string registerTable(int &numberOfSymbols, int &symbolCounter){
    string temp;

    if(symbolCounter == numberOfSymbols){ //Check for overflow of 'symbols' vector.
        return "";
    }

    symbolCounter++; //Increment the counter for 'symbols' vector.
    string temp_symbol = symbols[symbolCounter]; //Stores the register symbol in a temporary variable.
        //Assigns appropriate binary representation of each register symbol.
        if(temp_symbol == "$0") temp = "00000";
        else if(temp_symbol == "$1") temp = "00001";
        else if(temp_symbol == "$2") temp = "00010";
        else if(temp_symbol == "$3") temp = "00011";
        else if(temp_symbol == "$4") temp = "00100";
        else if(temp_symbol == "$5") temp = "00101";
        else if(temp_symbol == "$6") temp = "00110";
        else if(temp_symbol == "$7") temp = "00111";
        else if(temp_symbol == "$8") temp = "01000";
        else if(temp_symbol == "$9") temp = "01001";
        else if(temp_symbol == "$10") temp = "01010";
        else if(temp_symbol == "$11") temp = "01011";
        else if(temp_symbol == "$12") temp = "01100";
        else if(temp_symbol == "$13") temp = "01101";
        else if(temp_symbol == "$14") temp = "01110";
        else if(temp_symbol == "$15") temp = "01111";
        else if(temp_symbol == "$16") temp = "10000";
        else if(temp_symbol == "$17") temp = "10001";
        else if(temp_symbol == "$18") temp = "10010";
        else if(temp_symbol == "$19") temp = "10011";
        else if(temp_symbol == "$20") temp = "10100";
        else if(temp_symbol == "$21") temp = "10101";
        else if(temp_symbol == "$22") temp = "10110";
        else if(temp_symbol == "$23") temp = "10111";
        else if(temp_symbol == "$24") temp = "11000";
        else if(temp_symbol == "$25") temp = "11001";
        else if(temp_symbol == "$26") temp = "11010";
        else if(temp_symbol == "$27") temp = "11011";
        else if(temp_symbol == "$28") temp = "11100";
        else if(temp_symbol == "$29") temp = "11101";
        else if(temp_symbol == "$30") temp = "11110";
        else if(temp_symbol == "$31") temp = "11111";
        else temp = temp + "00000";

        return temp; //We return the register number in binary form to be added to the rest of the instruction.
}

/* shiftTable takes care of the shift amount and turns it into a string for printing */
string shiftTable(int &numberOfSymbols, int &symbolCounter){
    string temp_symbol;
    string shift_ammount;

    if(symbolCounter == numberOfSymbols){ //Check for overflow of symbols vector.
        return "";
    }

    symbolCounter++;
    temp_symbol = symbols[symbolCounter]; //Store the shift amount symbol in a temporary symbol variable.

    //The algorithm below takes the string decimal and converts it into a integer decimal value, then converts
    //It to a 5-bit binary representation of the number.

    int decimal = atoi(temp_symbol.c_str());

    stringstream ht;
    ht << hex << decimal;

    stringstream bt;
    bt << hex << ht.str();
    unsigned n;
    bt >> n;
    bitset<5> b(n);

    shift_ammount = b.to_string();
    return shift_ammount;

}

/* The jumpTable function handles the jump location. */
string jumpTable(int &numberOfSymbols, int &symbolCounter, int &labelsCounter, int &lineCounter, string &temp){
    string temp_symbol;
    int offset; //Although I named this variable offset, it really is just the jump address.
    string bin;

    if(symbolCounter == numberOfSymbols){ //Check for overflow of symbols vector.
        return "";
    }

    symbolCounter++;
    temp_symbol = symbols[symbolCounter]; //Store the jump location in a temporary symbol variable.

    for(int i = 0; i < labelsCounter; i++){ //Search the label vector (That we made in pass 1) for the jump label.
        if(label[i].name == temp_symbol){
            offset = label[i].address;

            stringstream ht;    //After finding it we increment the address and turn it into binary form.
            ht << hex << offset;

            stringstream bt;
            bt << hex << ht.str();
            unsigned n;
            bt >> n;
            bitset<26> b(n);

            bin = b.to_string();

            temp = temp + bin;
            break;
        }
    }
    return temp; //We return the address in binary form to be added to the rest of the jump instruction.
}

/*This function handles the offset for the LW instruction */
string loadWordTable(int &numberOfSymbols, int &symbolCounter){
    string temp_symbol;
    string temp;
    string bin;

    if(symbolCounter == numberOfSymbols){ //Check for overflow of symbols vector.
        return "";
    }

    symbolCounter++;
    temp_symbol = symbols[symbolCounter]; //Store the offset amount symbol in a temporary symbol variable.

    signed decimal = atoi(temp_symbol.c_str());
        // cout << endl << "decimal " << decimal << endl; 

        stringstream ht;    //After finding it we increment the address and turn it into binary form.
        ht << hex << decimal;
        // cout << "ht " << ht << endl; 
        stringstream bt;
        bt << hex << ht.str();
        // cout << "bt " << bt << endl; 
        signed n;
        bt >> n;
        bitset<16> b(n);
        // cout << "b(n) " << b(n) << endl; 

        bin = b.to_string();
        temp = bin;


    return temp;
}

/* The symbolPrint function is the 2nd Pass of the symbol list, we are forming the instruction in BINARY which is then converted
    to HEX to the main printFile function */
string symbolPrint(int &addr, int &numberOfSymbols, int &symbolCounter, int &labelsCounter, int&lineCounter){
        string temp;
        string temp_symbol;
        //Src = source1, Tmp = source2, Dst = destination (Registers). Sft = shift ammount. Imm = immediate value amount. Lof = load word offset.
        string Src;
        string Tmp;
        string Dst;
        string Sft;
        string Imm;
        string Lof;

        if(symbolCounter == numberOfSymbols){ //Check for overflow of symbols vector.
            return "";
        }

        temp_symbol = symbols[symbolCounter]; //Store the symbol in a temporary symbol variable, it should be an instruction if no syntax errors.

        /*---------------------------------------------------------------------------------------------------------------------------------*/
        /* R-type - for these instructions we concatenate "000000" with the 3 registers (Src,Tmp,Dst) and then the function in binary.     */
        /* I-type - for these instructions we concatenate the OpCode in binary with the register required and the 16 bit immediate value.  */
        /* J-type - for these instructions we concatenate the OpCode with the offset of the jump.                                          */
        /*---------------------------------------------------------------------------------------------------------------------------------*/
        if(temp_symbol == "add"){
            temp = "000000";
            Dst = registerTable(numberOfSymbols, symbolCounter);
            Src = registerTable(numberOfSymbols, symbolCounter);
            Tmp = registerTable(numberOfSymbols, symbolCounter);
            temp = temp + Src + Tmp + Dst + "00000100000";
        }
        else if(temp_symbol == "addu"){
            temp = "000000";
            Dst = registerTable(numberOfSymbols, symbolCounter);
            Src = registerTable(numberOfSymbols, symbolCounter);
            Tmp = registerTable(numberOfSymbols, symbolCounter);
            temp = temp + Src + Tmp + Dst + "00000100001";
        }
        else if(temp_symbol == "addi"){
            temp = "001000";
            Tmp = registerTable(numberOfSymbols, symbolCounter);
            Src = registerTable(numberOfSymbols, symbolCounter);
            Imm = immediateTable(numberOfSymbols, symbolCounter);
            temp = temp + Src + Tmp + Imm;
        }
        else if(temp_symbol == "addiu"){
            temp = "001001";
            Tmp = registerTable(numberOfSymbols, symbolCounter);
            Src = registerTable(numberOfSymbols, symbolCounter);
            Imm = immediateTable(numberOfSymbols, symbolCounter);
            temp = temp + Src + Tmp + Imm;
        }
        else if(temp_symbol == "and"){
            temp = "000000";
            Dst = registerTable(numberOfSymbols, symbolCounter);
            Src = registerTable(numberOfSymbols, symbolCounter);
            Tmp = registerTable(numberOfSymbols, symbolCounter);
            temp = temp + Src + Tmp + Dst + "00000100100";
        }
        else if(temp_symbol == "andi"){
            temp = "001100";
            Tmp = registerTable(numberOfSymbols, symbolCounter);
            Src = registerTable(numberOfSymbols, symbolCounter);
            Imm = immediateTable(numberOfSymbols, symbolCounter);
            temp = temp + Src + Tmp + Imm;
        }
        else if(temp_symbol == "beq"){
            temp = "000100";
            Src = registerTable(numberOfSymbols, symbolCounter);
            Tmp = registerTable(numberOfSymbols, symbolCounter);
            temp = temp + Src + Tmp;
            branchTable(numberOfSymbols, symbolCounter, temp, labelsCounter, lineCounter);
        }
        else if(temp_symbol == "bne"){
            temp = "000101";
            Src = registerTable(numberOfSymbols, symbolCounter);
            Tmp = registerTable(numberOfSymbols, symbolCounter);
            temp = temp + Src + Tmp;
            branchTable(numberOfSymbols, symbolCounter, temp, labelsCounter, lineCounter);
        }
        else if(temp_symbol == "nor"){
            temp = "000000";
            Dst = registerTable(numberOfSymbols, symbolCounter);
            Src = registerTable(numberOfSymbols, symbolCounter);
            Tmp = registerTable(numberOfSymbols, symbolCounter);
            temp = temp + Src + Tmp + Dst + "00000100111";
        }
        else if(temp_symbol == "or"){
            temp = "000000";
            Dst = registerTable(numberOfSymbols, symbolCounter);
            Src = registerTable(numberOfSymbols, symbolCounter);
            Tmp = registerTable(numberOfSymbols, symbolCounter);
            temp = temp + Src + Tmp + Dst + "00000100101";
        }
        else if(temp_symbol == "ori"){
            temp = "001101";
            Tmp = registerTable(numberOfSymbols, symbolCounter);
            Src = registerTable(numberOfSymbols, symbolCounter);
            Imm = immediateTable(numberOfSymbols, symbolCounter);
            temp = temp + Src + Tmp + Imm;
        }
        else if(temp_symbol == "lui"){
            temp = "00111100000";
            Tmp = registerTable(numberOfSymbols, symbolCounter);
            Imm = immediateTable(numberOfSymbols, symbolCounter);
            temp = temp + Tmp + Imm;
        }
        else if(temp_symbol == "lw"){
            temp = "100011";
            Tmp = registerTable(numberOfSymbols, symbolCounter);
            Lof = loadWordTable(numberOfSymbols, symbolCounter);
            Src = registerTable(numberOfSymbols, symbolCounter);
            temp = temp + Src + Tmp + Lof;
        }
        else if(temp_symbol == "j"){
            temp = "000010";
            jumpTable(numberOfSymbols, symbolCounter, labelsCounter, lineCounter, temp);
        }
        else if(temp_symbol == "jal"){
            temp = "000011";
            jumpTable(numberOfSymbols, symbolCounter, labelsCounter, lineCounter, temp);
        }
        else if(temp_symbol == "jr"){
            temp = "000000";
            Src = registerTable(numberOfSymbols, symbolCounter);
            temp = temp + Src + "000000000000000001000";
        }
        else if(temp_symbol == "sub"){
            temp = "000000";
            Dst = registerTable(numberOfSymbols, symbolCounter);
            Src = registerTable(numberOfSymbols, symbolCounter);
            Tmp = registerTable(numberOfSymbols, symbolCounter);
            temp = temp + Src + Tmp + Dst + "00000100010";
        }
        else if(temp_symbol == "subu"){
            temp = "000000";
            Dst = registerTable(numberOfSymbols, symbolCounter);
            Src = registerTable(numberOfSymbols, symbolCounter);
            Tmp = registerTable(numberOfSymbols, symbolCounter);
            temp = temp + Src + Tmp + Dst + "00000100011";
        }
        else if(temp_symbol == "slt"){
            temp = "000000";
            Dst = registerTable(numberOfSymbols, symbolCounter);
            Src = registerTable(numberOfSymbols, symbolCounter);
            Tmp = registerTable(numberOfSymbols, symbolCounter);
            temp = temp + Src + Tmp + Dst + "00000101010";
        }
        else if(temp_symbol == "sltiu"){
            temp = "001011";
            Tmp = registerTable(numberOfSymbols, symbolCounter);
            Src = registerTable(numberOfSymbols, symbolCounter);
            Imm = immediateTable(numberOfSymbols, symbolCounter);
            temp = temp + Src + Tmp + Imm;
        }
        else if(temp_symbol == "sw"){
            temp = "101011";
            Tmp = registerTable(numberOfSymbols, symbolCounter);
            Imm = immediateTable(numberOfSymbols, symbolCounter);
            Src = registerTable(numberOfSymbols, symbolCounter);
            temp = temp + Src + Tmp + Imm;
        }
        else if(temp_symbol == "srl"){
            temp = "00000000000";
            Dst = registerTable(numberOfSymbols, symbolCounter);
            Tmp = registerTable(numberOfSymbols, symbolCounter);
            Sft = shiftTable(numberOfSymbols, symbolCounter);
            temp = temp + Tmp + Dst + Sft + "000010";
        }
        else if(temp_symbol == "sll"){
            temp = "00000000000";
            Dst = registerTable(numberOfSymbols, symbolCounter);
            Tmp = registerTable(numberOfSymbols, symbolCounter);
            Sft = shiftTable(numberOfSymbols, symbolCounter);
            temp = temp + Tmp + Dst + Sft + "000000";
        }
        else if(temp_symbol == "la"){
            temp = "";
        }
        else{
            //If a label is encountered we ignore it since we have previously recorded it.
            //However we increment the symbolCounter and we call the symbolPrint function to print the next line in it's place.

            symbolCounter++;
            temp = symbolPrint(addr,numberOfSymbols, symbolCounter, labelsCounter, lineCounter);
            return temp;
        }

    symbolCounter++;
    lineCounter++;
    temp = bin2hex(temp);
    return temp;
}

/* The firstPass function runs through the symbol list and records all labels and their addresses */
void firstPass(int &numberOfSymbols, int &symbolsCounter, int &lineCounter, int &labelsCounter){ //This function looks through all symbols to find labels.
    if(numberOfSymbols == symbolsCounter){
        return; 
    }
    string temp_symbol = symbols[symbolsCounter];

    if(temp_symbol == "add")    symbolsCounter = symbolsCounter + 4;
    else if(temp_symbol == "addi") symbolsCounter = symbolsCounter + 4;
    else if(temp_symbol == "addiu") symbolsCounter = symbolsCounter + 4;
    else if(temp_symbol == "addu") symbolsCounter = symbolsCounter + 4;
    else if(temp_symbol == "and") symbolsCounter = symbolsCounter + 4;
    else if(temp_symbol == "andi") symbolsCounter = symbolsCounter + 4;
    else if(temp_symbol == "beq") symbolsCounter = symbolsCounter + 4;
    else if(temp_symbol == "bne") symbolsCounter = symbolsCounter + 4;
    else if(temp_symbol == "j") symbolsCounter = symbolsCounter + 2;
    else if(temp_symbol == "jal") symbolsCounter = symbolsCounter + 2;
    else if(temp_symbol == "jr") symbolsCounter = symbolsCounter + 2;
    else if(temp_symbol == "lbu") symbolsCounter = symbolsCounter + 4;
    else if(temp_symbol == "lhu") symbolsCounter = symbolsCounter + 4;
    else if(temp_symbol == "lui") symbolsCounter = symbolsCounter + 3;
    else if(temp_symbol == "lw") symbolsCounter = symbolsCounter + 4;
    else if(temp_symbol == "nor") symbolsCounter = symbolsCounter + 4;
    else if(temp_symbol == "or") symbolsCounter = symbolsCounter + 4;
    else if(temp_symbol == "ori") symbolsCounter = symbolsCounter + 4;
    else if(temp_symbol == "slt") symbolsCounter = symbolsCounter + 4;
    else if(temp_symbol == "slti") symbolsCounter = symbolsCounter + 4;
    else if(temp_symbol == "sltiu") symbolsCounter = symbolsCounter + 4;
    else if(temp_symbol == "sltu") symbolsCounter = symbolsCounter + 4;
    else if(temp_symbol == "sll") symbolsCounter = symbolsCounter + 4;
    else if(temp_symbol == "srl") symbolsCounter = symbolsCounter + 4;
    else if(temp_symbol == "sb") symbolsCounter = symbolsCounter + 4;
    else if(temp_symbol == "sh") symbolsCounter = symbolsCounter + 4;
    else if(temp_symbol == "sw") symbolsCounter = symbolsCounter + 4;
    else if(temp_symbol == "sub") symbolsCounter = symbolsCounter + 4;
    else if(temp_symbol == "subu") symbolsCounter = symbolsCounter + 4;
    else{
            //If a label is found that isn't an instruction is probably is a label and is recorded.
            Labels newLabel; //We create a new Labels object.
            newLabel.name = temp_symbol; //We store the name of the label.
            newLabel.address = lineCounter; //We store the lineCounter (address in decimal).
            label.push_back(newLabel); //Then we push the object into a vector for storage.
            //We do not increment lineCounter because a label is just a placeholder for the next instruction's address not it's own.
            labelsCounter++; //We increment the labels counter keeping track of the size of our vector.
            symbolsCounter++; //We increment symbolsCounter because the label is a symbol in our symbols vector.
            return;
    }

    lineCounter++; //We increment the line counter once after each instruction is run through. Except for when a label is found!
}

/* This is the main print function that utilizes all the functions above it to print out the assembled instructions */
void printFile(){ //This function prints to file.
    ofstream oFile;
    oFile.open("objectfile.txt");




    //manipulate the .data section:
    




    int lineCounter = 0; //The line counter records the line address count.
    int numberOfSymbols = symbols.size(); //This is the number of symbols we parsed from the assembly file.
    int symbolCounter = 0; //Whenever we iterate through the symbols vector we want to keep count as to not overflow.
    string instruction; //This string holds the final instruction in HEX for printing.
    int labelsCounter = 0; //We keep a count of the labels we find in the symbols vector.

    for(int i = 0; i < numberOfSymbols; i++){ //1st pass through symbols list to see if there are any labels, to record their addresses.
        firstPass(numberOfSymbols, symbolCounter, lineCounter, labelsCounter);
    }

    //printing symbol table
    
    cout << setw(23) <<  "SYMBOL TABLE" << endl;
    cout << setw(15) << "label" << setw(10) << "ADDRESS" << endl;

    for(int i=0; i<label.size()-1; i++){
        cout << setw(15) << label[i].name << setw(10) << label[i].address << endl;
    }

    symbolCounter = 0; //Reset symbolCounter and lineCounter to be used in the second pass.
    lineCounter = 0;

    for(int i = 0; i < DEPTH-1; i++) //2nd pass goes through the symbol list and starts concatenating the correct str ing/instruction.
    {

        if((symbolCounter == numberOfSymbols-1) && (lineCounter != DEPTH-1)){
            break;
        }

        oFile << "   ";
        int bytenumber = lineCounter*4;
        // oFile << setw(3) << setfill('0') << hex << bytenumber << ":   ";
        instruction = symbolPrint(i,numberOfSymbols, symbolCounter, labelsCounter, lineCounter);
        oFile << instruction << endl;
    }
    oFile << endl;
    oFile.close();

}

/* Checks for identifiers (lowercase symbols, ex: addi, lw, etc.) */
void identifiers(char &value, int &i){
    string temp;
    while(islower(value)){
        if(i == tokenSize){
            break;
        }
        temp += value;
        i++;
        value = textTokens[i];
    }
    symbols.push_back(temp);
}

/* Checks for registers, knows if a register is being parsed a '$' symbol is encountered then records the number */
void registers(char &value, int &i){
    string temp;
    temp += value;
    i++;
    value = textTokens[i];

    while(isdigit(value)){
        if(i == tokenSize){
            break;
        }

        temp += value;
        i++;
        value = textTokens[i];
    }

    symbols.push_back(temp);
}

/* Checks for digits, digits are usually addressees or offsets, it disguishes between the two and records appropriate symbols */
void digits(char &value, int &i){
    string temp;
    if(value == '0' && textTokens[i+1] == 'x'){
        i = i + 2;
    }
    if(value == '-'){
        temp = value;
        i = i + 1;
    }
    value = textTokens[i];
    while(isdigit(value) || islower(value)){
        if(i == tokenSize){
            break;
        }
        temp += value;
        i++;
        value = textTokens[i];
    }
    symbols.push_back(temp);
}

/* This function generates the symbol vector using the functions above it to distinguish between symbols */
void compareTokens(){ //This function turns all tokens into symbols.
    for(int i = 0; i < tokenSize; i++){
            token = textTokens[i];

            if(islower(token)){
                identifiers(token, i);
            }
            if(token == '$'){
                registers(token, i);
            }
            if(isdigit(token) || token == '-'){
                digits(token, i);
            }
    }
}

void runDataSegment(){
    //data_symols contains all the .data segment related symbols
    string temp = "";
    for(int i = 0; i < tokenSize_data; i++){
        token = dataTokens[i];
        if(token!=':' && !isspace(token) && token!=',' && token!='.'){
            temp = temp + token;
        }
        else{
            if(isalpha(temp[0]) || isdigit(temp[0])){
                data_symbols.push_back(temp);
                temp = "";
            }
        }
    }
    // for(int i = 0; i < data_symbols.size(); i++){
    //     cout << data_symbols[i] << " ";
    // }
    // cout << endl;
    
    int t = 0;
    while(t < data_symbols.size()-1){
        struct data_label tem;
        tem.name = data_symbols[t];
        t++;
        tem.type = data_symbols[t];
        t++;
        if(tem.type=="word"){
            while(!isalpha(data_symbols[t][0])){
                tem.values.push_back(data_symbols[t]);
                
                if(t >= data_symbols.size()-1){
                    break;
                }
                t++;
            }
            dataLabels.push_back(tem);
        }
        if(tem.type=="asciiz"){
            //code for .asciiz
        }
    }

    int offset = 0;
    for(int i = 0; i < dataLabels.size(); i++){
        dataLabels[i].offsetBytes_forLbales = offset;
        offset += dataLabels[i].values.size() * 4;
    }

    // for(int i = 0; i < dataLabels.size(); i++){
    //     // cout << data_symbols[i] << " ";
    //     cout << dataLabels[i].name << " " << dataLabels[i].type << " " << dataLabels[i].offsetBytes_forLbales << " ";
    //     for(int j=0; j< dataLabels[i].values.size(); j++){
    //         cout << dataLabels[i].values[j] << " ";
    //     }
    //     cout << endl;
    // }
}

int main(int argc, char *argv[]){
    if(argc < 2) {
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }
    splitFile(argv[1]); //stores all characters in a vector called "tokens"
    openTextFile();
    compareTokens(); //pushes into "symbols" vector all the symbols
    // openDataFile();
    // runDataSegment();
    printFile();
    // cout << "Assembled file created..." << endl;
    return 0;
}

/*
Disclaimer: 
References - 1) Learnt using setfill and setw 
https://programmingdigest.com/c-manipulators-endl-setw-setfill-setprecision-with-examples/#The_setfill_C_Manipulators 

2) Reference used for mips machine code
https://web.engr.oregonstate.edu/~walkiner/cs271-wi13/slides/11-MachineCode.pdf 

3) https://github.com/JamesHearts 

4) https://eng.libretexts.org/Bookshelves/Computer_Science/Programming_Languages/Introduction_To_MIPS_Assembly_Language_Programming_(Kann)/07%3A_Assembly_Language_Program_Control_Structures/7.08%3A_How_to_Calculate_Branch_Amounts_in_Machine_Code - 
reference for branch instructions
*/