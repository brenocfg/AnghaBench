#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_7__ {scalar_t__ check_x; TYPE_1__* list; } ;
struct TYPE_6__ {int top_index; scalar_t__ box_y; scalar_t__ box_x; int /*<<< orphan*/ * win; } ;
typedef  TYPE_1__ MY_DATA ;
typedef  TYPE_2__ ALL_DATA ;

/* Variables and functions */
 int KEY_MAX ; 
 scalar_t__ MIN (int,int) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  dlg_draw_scrollbar (int /*<<< orphan*/ *,long,long,long,long,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlg_mouse_setcode (int) ; 
 scalar_t__ getmaxx (int /*<<< orphan*/ *) ; 
 int getmaxy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getyx (int /*<<< orphan*/ *,int,int) ; 
 int index2row (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  menubox_border2_attr ; 
 int /*<<< orphan*/  menubox_border_attr ; 
 int /*<<< orphan*/  print_1_list (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/ * wgetparent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void
print_both(ALL_DATA * all,
	   int choice)
{
    int selected;
    int cur_y, cur_x;
    WINDOW *dialog = wgetparent(all->list[0].win);

    TRACE(("! print_both %d\n", choice));
    getyx(dialog, cur_y, cur_x);
    for (selected = 0; selected < 2; ++selected) {
	MY_DATA *data = all->list + selected;
	WINDOW *win = data->win;
	int thumb_top = index2row(all, data->top_index, selected);
	int thumb_max = index2row(all, -1, selected);
	int thumb_end = thumb_top + getmaxy(win);

	print_1_list(all, choice, selected);

	dlg_mouse_setcode(selected * KEY_MAX);
	dlg_draw_scrollbar(dialog,
			   (long) (data->top_index),
			   (long) (thumb_top),
			   (long) MIN(thumb_end, thumb_max),
			   (long) thumb_max,
			   data->box_x + all->check_x,
			   data->box_x + getmaxx(win),
			   data->box_y,
			   data->box_y + getmaxy(win) + 1,
			   menubox_border2_attr,
			   menubox_border_attr);
    }
    (void) wmove(dialog, cur_y, cur_x);
    dlg_mouse_setcode(0);
}