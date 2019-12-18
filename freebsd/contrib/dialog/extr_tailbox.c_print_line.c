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
typedef  int /*<<< orphan*/  MY_OBJ ;

/* Variables and functions */
 int /*<<< orphan*/  MIN (int,int) ; 
 char* get_line (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getyx (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  waddch (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  waddnstr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_line(MY_OBJ * obj, WINDOW *win, int row, int width)
{
    int i, y, x;
    char *line = get_line(obj);

    (void) wmove(win, row, 0);	/* move cursor to correct line */
    (void) waddch(win, ' ');
    (void) waddnstr(win, line, MIN((int) strlen(line), width - 2));

    getyx(win, y, x);
    (void) y;
    /* Clear 'residue' of previous line */
    for (i = 0; i < width - x; i++)
	(void) waddch(win, ' ');
}