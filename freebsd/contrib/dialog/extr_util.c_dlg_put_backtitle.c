#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  chtype ;
struct TYPE_2__ {int /*<<< orphan*/ * backtitle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACS_HLINE ; 
 int /*<<< orphan*/  A_NORMAL ; 
 int COLS ; 
 TYPE_1__ dialog_vars ; 
 int /*<<< orphan*/  dlg_attrset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char dlg_boxchar (int /*<<< orphan*/ ) ; 
 int dlg_count_columns (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlg_print_text (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  screen_attr ; 
 int /*<<< orphan*/  stdscr ; 
 int /*<<< orphan*/  waddch (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  wnoutrefresh (int /*<<< orphan*/ ) ; 

void
dlg_put_backtitle(void)
{
    int i;

    if (dialog_vars.backtitle != NULL) {
	chtype attr = A_NORMAL;
	int backwidth = dlg_count_columns(dialog_vars.backtitle);

	dlg_attrset(stdscr, screen_attr);
	(void) wmove(stdscr, 0, 1);
	dlg_print_text(stdscr, dialog_vars.backtitle, COLS - 2, &attr);
	for (i = 0; i < COLS - backwidth; i++)
	    (void) waddch(stdscr, ' ');
	(void) wmove(stdscr, 1, 1);
	for (i = 0; i < COLS - 2; i++)
	    (void) waddch(stdscr, dlg_boxchar(ACS_HLINE));
    }

    (void) wnoutrefresh(stdscr);
}