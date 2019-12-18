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
typedef  int /*<<< orphan*/  chtype ;

/* Variables and functions */
 int A_COLOR ; 
 int /*<<< orphan*/  A_NORMAL ; 
 int COLS ; 
 scalar_t__ LINES ; 
 scalar_t__ USE_ITEM_HELP (char const*) ; 
 int /*<<< orphan*/  addch (char) ; 
 int /*<<< orphan*/  dlg_attrset (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dlg_print_text (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getyx (int /*<<< orphan*/ ,int,int) ; 
 int itemhelp_attr ; 
 int /*<<< orphan*/  stdscr ; 
 int /*<<< orphan*/  wclrtoeol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wnoutrefresh (int /*<<< orphan*/ ) ; 

void
dlg_item_help(const char *txt)
{
    if (USE_ITEM_HELP(txt)) {
	chtype attr = A_NORMAL;
	int y, x;

	dlg_attrset(stdscr, itemhelp_attr);
	(void) wmove(stdscr, LINES - 1, 0);
	(void) wclrtoeol(stdscr);
	(void) addch(' ');
	dlg_print_text(stdscr, txt, COLS - 1, &attr);
	if (itemhelp_attr & A_COLOR) {
	    /* fill the remainder of the line with the window's attributes */
	    getyx(stdscr, y, x);
	    (void) y;
	    while (x < COLS) {
		(void) addch(' ');
		++x;
	    }
	}
	(void) wnoutrefresh(stdscr);
    }
}