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
struct Sudoku {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  Sudoku ; 
 int /*<<< orphan*/  Sudoku_Solve (struct Sudoku*,char*) ; 
 int /*<<< orphan*/  del (struct Sudoku*) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ ) ; 
 struct Sudoku* new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdin ; 
 int strlen (char*) ; 

int main(int argc, char** argv) {
	struct Sudoku* a = new(Sudoku);
	char buf[1024];
	while (fgets(buf, 1024, stdin) != 0) {
		if (strlen(buf) < 81) continue;
		Sudoku_Solve(a, buf);
		//putchar('\n');
	}
	del(a);
	return 0;
}