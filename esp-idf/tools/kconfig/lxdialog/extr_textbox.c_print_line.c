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
typedef  int /*<<< orphan*/  WINDOW ;

/* Variables and functions */
 int /*<<< orphan*/  MIN (int /*<<< orphan*/ ,int) ; 
 char* get_line () ; 
 int getcurx (int /*<<< orphan*/ *) ; 
 int hscroll ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  waddch (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  waddnstr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wclrtoeol (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_line(WINDOW * win, int row, int width)
{
	char *line;

	line = get_line();
	line += MIN(strlen(line), hscroll);	/* Scroll horizontally */
	wmove(win, row, 0);	/* move cursor to correct line */
	waddch(win, ' ');
	waddnstr(win, line, MIN(strlen(line), width - 2));

	/* Clear 'residue' of previous line */
#if OLD_NCURSES
	{
		int x = getcurx(win);
		int i;
		for (i = 0; i < width - x; i++)
			waddch(win, ' ');
	}
#else
	wclrtoeol(win);
#endif
}