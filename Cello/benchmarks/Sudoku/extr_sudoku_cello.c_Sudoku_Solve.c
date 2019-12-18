#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint8_t ;
struct Sudoku {int** r; } ;
typedef  size_t int8_t ;
typedef  size_t int16_t ;

/* Variables and functions */
 int Sudoku_Update (struct Sudoku*,size_t*,int*,int,int) ; 

__attribute__((used)) static int Sudoku_Solve(struct Sudoku* aux, const char *_s) {
	int i, j, r, c, r2, dir, cand, n = 0, min, hints = 0; // dir=1: forward; dir=-1: backtrack
	int8_t sr[729], cr[81]; // sr[r]: # times the row is forbidden by others; cr[i]: row chosen at step i
	uint8_t sc[324]; // bit 1-7: # allowed choices; bit 8: the constraint has been used or not
	int16_t cc[81]; // cc[i]: col chosen at step i
	char out[82];
	for (r = 0; r < 729; ++r) sr[r] = 0; // no row is forbidden
	for (c = 0; c < 324; ++c) sc[c] = 0<<7|9; // 9 allowed choices; no constraint has been used
	for (i = 0; i < 81; ++i) {
		int a = _s[i] >= '1' && _s[i] <= '9'? _s[i] - '1' : -1; // number from -1 to 8
		if (a >= 0) Sudoku_Update(aux, sr, sc, i * 9 + a, 1); // set the choice
		if (a >= 0) ++hints; // count the number of hints
		cr[i] = cc[i] = -1, out[i] = _s[i];
	}
	for (i = 0, dir = 1, cand = 10<<16|0, out[81] = 0;;) {
		while (i >= 0 && i < 81 - hints) { // maximum 81-hints steps
			if (dir == 1) {
				min = cand>>16, cc[i] = cand&0xffff;
				if (min > 1) {
					for (c = 0; c < 324; ++c) {
						if (sc[c] < min) {
							min = sc[c], cc[i] = c; // choose the top constraint
							if (min <= 1) break; // this is for acceleration; slower without this line
						}
					}
				}
				if (min == 0 || min == 10) cr[i--] = dir = -1; // backtrack
			}
			c = cc[i];
			if (dir == -1 && cr[i] >= 0) Sudoku_Update(aux, sr, sc, aux->r[c][cr[i]], -1); // revert the choice
			for (r2 = cr[i] + 1; r2 < 9; ++r2) // search for the choice to make
				if (sr[aux->r[c][r2]] == 0) break; // found if the state equals 0
			if (r2 < 9) {
				cand = Sudoku_Update(aux, sr, sc, aux->r[c][r2], 1); // set the choice
				cr[i++] = r2; dir = 1; // moving forward
			} else cr[i--] = dir = -1; // backtrack
		}
		if (i < 0) break;
		for (j = 0; j < i; ++j) r = aux->r[cc[j]][cr[j]], out[r/9] = r%9 + '1'; // print
		//puts(out);
		++n; --i; dir = -1; // backtrack
	}
	return n; // return the number of solutions
}