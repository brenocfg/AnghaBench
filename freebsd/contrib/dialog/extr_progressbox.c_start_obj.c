#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  win; } ;
struct TYPE_5__ {char* prompt; int high; int /*<<< orphan*/  text; TYPE_1__ obj; scalar_t__ wide; } ;
typedef  TYPE_2__ MY_OBJ ;

/* Variables and functions */
 int /*<<< orphan*/  ACS_HLINE ; 
 int /*<<< orphan*/  FALSE ; 
 int MARGIN ; 
 int /*<<< orphan*/  MIN_HIGH ; 
 int /*<<< orphan*/  MIN_WIDE ; 
 int /*<<< orphan*/  border2_attr ; 
 int /*<<< orphan*/  border_attr ; 
 int /*<<< orphan*/  dialog_attr ; 
 int /*<<< orphan*/  dlg_attr_clear (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlg_attrset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlg_auto_size (char const*,char*,int*,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dlg_box_x_ordinate (scalar_t__) ; 
 int dlg_box_y_ordinate (int) ; 
 int /*<<< orphan*/  dlg_boxchar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlg_ctl_size (int,scalar_t__) ; 
 int /*<<< orphan*/  dlg_draw_box2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlg_draw_helpline (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlg_draw_title (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  dlg_new_window (int,scalar_t__,int,int) ; 
 int /*<<< orphan*/  dlg_print_autowrap (int /*<<< orphan*/ ,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  dlg_print_size (int,scalar_t__) ; 
 char* dlg_strclone (char const*) ; 
 int /*<<< orphan*/  dlg_sub_window (int /*<<< orphan*/ ,int,scalar_t__,int,int) ; 
 int /*<<< orphan*/  dlg_tab_correct_str (char*) ; 
 int getmaxx (int /*<<< orphan*/ ) ; 
 int getmaxy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getyx (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  waddch (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  wnoutrefresh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrefresh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
start_obj(MY_OBJ * obj, const char *title, const char *cprompt)
{
    int y, x, thigh;
    int i;

    obj->prompt = dlg_strclone(cprompt);
    dlg_tab_correct_str(obj->prompt);
    dlg_auto_size(title, obj->prompt, &obj->high, &obj->wide, MIN_HIGH, MIN_WIDE);

    dlg_print_size(obj->high, obj->wide);
    dlg_ctl_size(obj->high, obj->wide);

    x = dlg_box_x_ordinate(obj->wide);
    y = dlg_box_y_ordinate(obj->high);
    thigh = obj->high - (2 * MARGIN);

    obj->obj.win = dlg_new_window(obj->high, obj->wide, y, x);

    dlg_draw_box2(obj->obj.win,
		  0, 0,
		  obj->high, obj->wide,
		  dialog_attr,
		  border_attr,
		  border2_attr);
    dlg_draw_title(obj->obj.win, title);
    dlg_draw_helpline(obj->obj.win, FALSE);

    if (obj->prompt[0] != '\0') {
	int y2, x2;

	dlg_attrset(obj->obj.win, dialog_attr);
	dlg_print_autowrap(obj->obj.win, obj->prompt, obj->high, obj->wide);
	getyx(obj->obj.win, y2, x2);
	(void) x2;
	++y2;
	wmove(obj->obj.win, y2, MARGIN);
	for (i = 0; i < getmaxx(obj->obj.win) - 2 * MARGIN; i++)
	    (void) waddch(obj->obj.win, dlg_boxchar(ACS_HLINE));
	y += y2;
	thigh -= y2;
    }

    /* Create window for text region, used for scrolling text */
    obj->text = dlg_sub_window(obj->obj.win,
			       thigh,
			       obj->wide - (2 * MARGIN),
			       y + MARGIN,
			       x + MARGIN);

    (void) wrefresh(obj->obj.win);

    (void) wmove(obj->obj.win, getmaxy(obj->text), (MARGIN + 1));
    (void) wnoutrefresh(obj->obj.win);

    dlg_attr_clear(obj->text, getmaxy(obj->text), getmaxx(obj->text), dialog_attr);
}