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
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_2__ {scalar_t__* help_line; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_NORMAL ; 
 int ON_LEFT ; 
 int ON_RIGHT ; 
 TYPE_1__ dialog_vars ; 
 int dlg_count_columns (scalar_t__*) ; 
 int dlg_count_real_columns (scalar_t__*) ; 
 int /*<<< orphan*/  dlg_print_text (int /*<<< orphan*/ *,scalar_t__*,int,int /*<<< orphan*/ *) ; 
 int getmaxx (int /*<<< orphan*/ *) ; 
 int getmaxy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getyx (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  waddch (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ *,int,int) ; 

void
dlg_draw_helpline(WINDOW *win, bool decorations)
{
    int cur_x, cur_y;
    int bottom;

    if (dialog_vars.help_line != 0
	&& dialog_vars.help_line[0] != 0
	&& (bottom = getmaxy(win) - 1) > 0) {
	chtype attr = A_NORMAL;
	int cols = dlg_count_columns(dialog_vars.help_line);
	int other = decorations ? (ON_LEFT + ON_RIGHT) : 0;
	int avail = (getmaxx(win) - other - 2);
	int limit = dlg_count_real_columns(dialog_vars.help_line) + 2;

	if (limit < avail) {
	    getyx(win, cur_y, cur_x);
	    other = decorations ? ON_LEFT : 0;
	    (void) wmove(win, bottom, other + (avail - limit) / 2);
	    waddch(win, '[');
	    dlg_print_text(win, dialog_vars.help_line, cols, &attr);
	    waddch(win, ']');
	    wmove(win, cur_y, cur_x);
	}
    }
}