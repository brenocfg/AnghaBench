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
struct TYPE_3__ {scalar_t__ win; int offset; int length; int choice; int /*<<< orphan*/  par; scalar_t__* data; } ;
typedef  TYPE_1__ LIST ;

/* Variables and functions */
 int /*<<< orphan*/  dlg_attr_clear (scalar_t__,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlg_attrset (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlg_draw_scrollbar (int /*<<< orphan*/ ,long,long,long,long,int,scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ getmaxx (scalar_t__) ; 
 int getmaxy (scalar_t__) ; 
 int /*<<< orphan*/  getparyx (scalar_t__,int,int) ; 
 int /*<<< orphan*/  item_attr ; 
 int /*<<< orphan*/  item_selected_attr ; 
 int /*<<< orphan*/  menubox_border2_attr ; 
 int /*<<< orphan*/  menubox_border_attr ; 
 int /*<<< orphan*/  waddstr (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  wmove (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wnoutrefresh (scalar_t__) ; 

__attribute__((used)) static void
display_list(LIST * list)
{
    int n;
    int x;
    int y;
    int top;
    int bottom;

    if (list->win != 0) {
	dlg_attr_clear(list->win, getmaxy(list->win), getmaxx(list->win), item_attr);
	for (n = list->offset; n < list->length && list->data[n]; n++) {
	    y = n - list->offset;
	    if (y >= getmaxy(list->win))
		break;
	    (void) wmove(list->win, y, 0);
	    if (n == list->choice)
		dlg_attrset(list->win, item_selected_attr);
	    (void) waddstr(list->win, list->data[n]);
	    dlg_attrset(list->win, item_attr);
	}
	dlg_attrset(list->win, item_attr);

	getparyx(list->win, y, x);

	top = y - 1;
	bottom = y + getmaxy(list->win);
	dlg_draw_scrollbar(list->par,
			   (long) list->offset,
			   (long) list->offset,
			   (long) (list->offset + getmaxy(list->win)),
			   (long) (list->length),
			   x + 1,
			   x + getmaxx(list->win),
			   top,
			   bottom,
			   menubox_border2_attr,
			   menubox_border_attr);

	(void) wmove(list->win, list->choice - list->offset, 0);
	(void) wnoutrefresh(list->win);
    }
}