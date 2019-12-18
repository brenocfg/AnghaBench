#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  atr; } ;
struct TYPE_4__ {int /*<<< orphan*/ * backtitle; TYPE_1__ screen; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACS_HLINE ; 
 int COLS ; 
 int /*<<< orphan*/  LINES ; 
 int /*<<< orphan*/  attr_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_2__ dlg ; 
 int /*<<< orphan*/  mvwaddstr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  stdscr ; 
 int /*<<< orphan*/  waddch (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wattrset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  wnoutrefresh (int /*<<< orphan*/ ) ; 

void dialog_clear(void)
{
	attr_clear(stdscr, LINES, COLS, dlg.screen.atr);
	/* Display background title if it exists ... - SLH */
	if (dlg.backtitle != NULL) {
		int i;

		wattrset(stdscr, dlg.screen.atr);
		mvwaddstr(stdscr, 0, 1, (char *)dlg.backtitle);
		wmove(stdscr, 1, 1);
		for (i = 1; i < COLS - 1; i++)
			waddch(stdscr, ACS_HLINE);
	}
	wnoutrefresh(stdscr);
}