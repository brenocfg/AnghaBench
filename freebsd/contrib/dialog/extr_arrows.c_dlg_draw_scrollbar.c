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
struct TYPE_2__ {scalar_t__ use_scrollbar; } ;

/* Variables and functions */
 int ACS_BLOCK ; 
 int /*<<< orphan*/  ACS_HLINE ; 
 int ACS_VLINE ; 
 scalar_t__ ARROWS_COL ; 
 int A_REVERSE ; 
 int BARSIZE (long) ; 
 long MAX (int /*<<< orphan*/ ,long) ; 
 int MIN (int,int) ; 
 int ORDSIZE (long) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WACS_BLOCK ; 
 int /*<<< orphan*/  border_attr ; 
 TYPE_1__ dialog_state ; 
 int /*<<< orphan*/  dlg_attron (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dlg_attrset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlg_boxchar (int /*<<< orphan*/ ) ; 
 int dlg_count_columns (char*) ; 
 int /*<<< orphan*/  dlg_draw_arrows2 (int /*<<< orphan*/ *,int,int,scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlg_draw_helpline (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlg_get_attrs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getyx (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  position_indicator_attr ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  waddstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  whline (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  wvline (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  wvline_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void
dlg_draw_scrollbar(WINDOW *win,
		   long first_data,
		   long this_data,
		   long next_data,
		   long total_data,
		   int left,
		   int right,
		   int top,
		   int bottom,
		   chtype attr,
		   chtype borderattr)
{
    char buffer[80];
    int percent;
    int len;
    int oldy, oldx;

    chtype save = dlg_get_attrs(win);
    int top_arrow = (first_data != 0);
    int bottom_arrow = (next_data < total_data);

    getyx(win, oldy, oldx);

    dlg_draw_helpline(win, TRUE);
    if (bottom_arrow || top_arrow || dialog_state.use_scrollbar) {
	percent = (!total_data
		   ? 100
		   : (int) ((next_data * 100)
			    / total_data));

	if (percent < 0)
	    percent = 0;
	else if (percent > 100)
	    percent = 100;

	dlg_attrset(win, position_indicator_attr);
	(void) sprintf(buffer, "%d%%", percent);
	(void) wmove(win, bottom, right - 7);
	(void) waddstr(win, buffer);
	if ((len = dlg_count_columns(buffer)) < 4) {
	    dlg_attrset(win, border_attr);
	    whline(win, dlg_boxchar(ACS_HLINE), 4 - len);
	}
    }
#define BARSIZE(num) (int) (0.5 + (double) ((all_high * (int) (num)) / (double) total_data))
#define ORDSIZE(num) (int) ((double) ((all_high * (int) (num)) / (double) all_diff))

    if (dialog_state.use_scrollbar) {
	int all_high = (bottom - top - 1);

	this_data = MAX(0, this_data);

	if (total_data > 0 && all_high > 0) {
	    int all_diff = (int) (total_data + 1);
	    int bar_diff = (int) (next_data + 1 - this_data);
	    int bar_high;
	    int bar_y;

	    bar_high = ORDSIZE(bar_diff);
	    if (bar_high <= 0)
		bar_high = 1;

	    if (bar_high < all_high) {
		int bar_last = BARSIZE(next_data);

		wmove(win, top + 1, right);

		dlg_attrset(win, save);
		wvline(win, ACS_VLINE | A_REVERSE, all_high);

		bar_y = ORDSIZE(this_data);
		if (bar_y >= bar_last && bar_y > 0)
		    bar_y = bar_last - 1;
		if (bar_last - bar_y > bar_high && bar_high > 1)
		    ++bar_y;
		bar_last = MIN(bar_last, all_high);

		wmove(win, top + 1 + bar_y, right);

		dlg_attrset(win, position_indicator_attr);
		dlg_attron(win, A_REVERSE);
#if defined(WACS_BLOCK) && defined(NCURSES_VERSION) && defined(USE_WIDE_CURSES)
		wvline_set(win, WACS_BLOCK, bar_last - bar_y);
#else
		wvline(win, ACS_BLOCK, bar_last - bar_y);
#endif
	    }
	}
    }
    dlg_draw_arrows2(win,
		     top_arrow,
		     bottom_arrow,
		     left + ARROWS_COL,
		     top,
		     bottom,
		     attr,
		     borderattr);

    dlg_attrset(win, save);
    wmove(win, oldy, oldx);
}