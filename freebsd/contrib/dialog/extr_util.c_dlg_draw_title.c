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
typedef  int /*<<< orphan*/  WINDOW ;

/* Variables and functions */
 int /*<<< orphan*/  A_NORMAL ; 
 int centered (scalar_t__,char const*) ; 
 int /*<<< orphan*/  dlg_attrset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlg_finish_string (char const*) ; 
 int /*<<< orphan*/  dlg_get_attrs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlg_print_text (int /*<<< orphan*/ *,char const*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ getmaxx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  title_attr ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void
dlg_draw_title(WINDOW *win, const char *title)
{
    if (title != NULL) {
	chtype attr = A_NORMAL;
	chtype save = dlg_get_attrs(win);
	int x = centered(getmaxx(win), title);

	dlg_attrset(win, title_attr);
	wmove(win, 0, x);
	dlg_print_text(win, title, getmaxx(win) - x, &attr);
	dlg_attrset(win, save);
	dlg_finish_string(title);
    }
}