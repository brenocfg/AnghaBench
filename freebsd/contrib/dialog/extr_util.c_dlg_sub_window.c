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
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  add_subwindow (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlg_exiterr (char*,int,int,int,int) ; 
 int /*<<< orphan*/  keypad (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * subwin (int /*<<< orphan*/ *,int,int,int,int) ; 

WINDOW *
dlg_sub_window(WINDOW *parent, int height, int width, int y, int x)
{
    WINDOW *win;

    if ((win = subwin(parent, height, width, y, x)) == 0) {
	dlg_exiterr("Can't make sub-window at (%d,%d), size (%d,%d).\n",
		    y, x, height, width);
    }

    add_subwindow(parent, win);
    (void) keypad(win, TRUE);
    return win;
}