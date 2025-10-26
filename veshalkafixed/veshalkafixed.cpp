#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <chrono>
#include <fstream>
using namespace std;
using namespace std::chrono;

int main()
{
	auto startT = high_resolution_clock::now();

	bool end = false;
	int tries = 0;
	int wrongTries = 0;
	char choice;
	vector<char> choices;

	bool did = false;

	vector<string> words;
	ifstream file("words.txt");
	string word;

	if (file.is_open()) {
		while (file >> word) {
			string deword = "";
			for (int i = 0; i < word.length(); i++) {
				deword += char((word[i] - 'a' - 3 + 26) % 26 + 'a');
			}
			words.push_back(deword);
		}
		file.close();
	}

	srand(time(0));
	int randId = rand() % words.size();
	string randWord = words[randId];
	string coveredWord = randWord;

	for (int i = 0; i < randWord.length(); i++) {
		coveredWord[i] = '_';
	}
	cout << coveredWord << endl;

	while (end == false) {
		cout << "choose a letter: ";
		cin >> choice;
		choices.push_back(choice);
		for (int i = 0; i < randWord.length(); i++) {
			for (int c = 0; c < choices.size(); c++) {
				if (randWord[i] == choices[c] and not(randWord[i] == coveredWord[i])) {
					coveredWord[i] = choices[c];
					did = true;
				}
			}
		}
		if (did == false) {
			wrongTries += 1;
		}
		else {
			did = false;
		}
		tries += 1;
		cout << coveredWord << endl;

		if (coveredWord == randWord) {
			auto endT = chrono::high_resolution_clock::now();
			auto secondduration = chrono::duration_cast<chrono::seconds>(endT - startT);
			auto milliduration = chrono::duration_cast<chrono::milliseconds>(endT - startT);

			cout << "|---<=| You won! |=>---|" << endl;
			cout << "|- Tries: " << tries << endl;
			cout << "|- Wrong tries: " << wrongTries << endl;
			cout << "|- Letters you tried: ";
			for (char c : choices) cout << c << ' ';
			cout << endl;
			cout << "|- Word: " << randWord << endl;
			cout << "|- Time taken: " << secondduration.count() << "." << milliduration.count() << " seconds" << endl;
			end = true;
		}
	}
}