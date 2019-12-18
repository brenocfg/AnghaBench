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
 char* _ (char*) ; 
 int /*<<< orphan*/  dlg_attrset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlg_draw_box (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlg_get_attrs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlg_print_text (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  title_attr ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void
mydraw_mixed_box(WINDOW *win, int y, int x, int height, int width,
		 chtype boxchar, chtype borderchar)
{
    dlg_draw_box(win, y, x, height, width, boxchar, borderchar);
    {
	chtype attr = A_NORMAL;
	const char *message = _("Overall Progress");
	chtype save2 = dlg_get_attrs(win);
	dlg_attrset(win, title_attr);
	(void) wmove(win, y, x + 2);
	dlg_print_text(win, message, width, &attr);
	dlg_attrset(win, save2);
    }
}