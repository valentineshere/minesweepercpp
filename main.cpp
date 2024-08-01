#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

const int WIDTH = 10;
const int HEIGHT = 10;
const int MINES = 10;

vector<vector<char>> board(HEIGHT, vector<char>(WIDTH, '-'));
vector<vector<char>> mines(HEIGHT, vector<char>(WIDTH, '0'));

void initializeBoard() {
    srand(time(0));
    int minesPlaced = 0;
    while (minesPlaced < MINES) {
        int x = rand() % WIDTH;
        int y = rand() % HEIGHT;
        if (mines[y][x] == '0') {
            mines[y][x] = '*';
            minesPlaced++;
        }
    }

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (mines[i][j] == '*') continue;
            int mineCount = 0;
            for (int y = max(0, i - 1); y <= min(HEIGHT - 1, i + 1); y++) {
                for (int x = max(0, j - 1); x <= min(WIDTH - 1, j + 1); x++) {
                    if (mines[y][x] == '*') mineCount++;
                }
            }
            mines[i][j] = '0' + mineCount;
        }
    }
}

void printBoard(const vector<vector<char>>& board) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

bool revealCell(int x, int y) {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) return false;
    if (board[y][x] != '-') return false;

    board[y][x] = mines[y][x];
    if (mines[y][x] == '0') {
        for (int dy = -1; dy <= 1; dy++) {
            for (int dx = -1; dx <= 1; dx++) {
                if (dx != 0 || dy != 0) revealCell(x + dx, y + dy);
            }
        }
    }
    return mines[y][x] != '*';
}

int main() {
    initializeBoard();
    bool gameover = false;

    while (!gameover) {
        printBoard(board);
        int x, y;
        cout << "Enter coordinates (x y): ";
        cin >> x >> y;
        if (!revealCell(x, y)) {
            cout << "Game Over! You hit a mine." << endl;
            gameover = true;
        } else {
            bool won = true;
            for (int i = 0; i < HEIGHT; i++) {
                for (int j = 0; j < WIDTH; j++) {
                    if (board[i][j] == '-' && mines[i][j] != '*') {
                        won = false;
                    }
                }
            }
            if (won) {
                cout << "Congratulations! You found all the mines." << endl;
                gameover = true;
            }
        }
    }

    printBoard(mines); // Show mines after game over
    return 0;
}
