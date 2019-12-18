#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int chtype ;
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_3__ {int current; int max_value; int min_value; int slide_len; int slide_inc; int slide_y; int slide_x; int value_x; int /*<<< orphan*/  value_len; int /*<<< orphan*/ * window; } ;
typedef  TYPE_1__ VALUE ;

/* Variables and functions */
 int A_REVERSE ; 
 int /*<<< orphan*/  DLG_TRACE (char*) ; 
 int dialog_attr ; 
 int /*<<< orphan*/  dlg_attroff (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dlg_attrset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dlg_trace_win (int /*<<< orphan*/ *) ; 
 int gauge_attr ; 
 int /*<<< orphan*/  getyx (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  waddch (int /*<<< orphan*/ *,int) ; 
 int winch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  wprintw (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
draw_value(VALUE * data, int value)
{
    if (value != data->current) {
	WINDOW *win = data->window;
	int y, x;
	int n;
	int ranges = (data->max_value + 1 - data->min_value);
	int offset = (value - data->min_value);
	int scaled;

	getyx(win, y, x);

	if (ranges > data->slide_len) {
	    scaled = (offset + data->slide_inc) / data->slide_inc;
	} else if (ranges < data->slide_len) {
	    scaled = (offset + 1) * data->slide_inc;
	} else {
	    scaled = offset;
	}

	dlg_attrset(win, gauge_attr);
	wmove(win, data->slide_y, data->slide_x);
	for (n = 0; n < data->slide_len; ++n) {
	    (void) waddch(win, ' ');
	}
	wmove(win, data->slide_y, data->value_x);
	wprintw(win, "%*d", data->value_len, value);
	if ((gauge_attr & A_REVERSE) != 0) {
	    dlg_attroff(win, A_REVERSE);
	} else {
	    dlg_attrset(win, A_REVERSE);
	}
	wmove(win, data->slide_y, data->slide_x);
	for (n = 0; n < scaled; ++n) {
	    chtype ch2 = winch(win);
	    if (gauge_attr & A_REVERSE) {
		ch2 &= ~A_REVERSE;
	    }
	    (void) waddch(win, ch2);
	}
	dlg_attrset(win, dialog_attr);

	wmove(win, y, x);
	data->current = value;

	DLG_TRACE(("# drew %d offset %d scaled %d limit %d inc %d\n",
		   value,
		   offset,
		   scaled,
		   data->slide_len,
		   data->slide_inc));

	dlg_trace_win(win);
    }
}