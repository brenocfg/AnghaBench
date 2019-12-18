#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int menu_height; int menu_width; int box_x; scalar_t__ box_y; int /*<<< orphan*/  item_no; int /*<<< orphan*/  dialog; int /*<<< orphan*/  menu; int /*<<< orphan*/ * items; } ;
typedef  TYPE_1__ ALL_DATA ;

/* Variables and functions */
 int INPUT_ROWS ; 
 int /*<<< orphan*/  Selected ; 
 int /*<<< orphan*/  Unselected ; 
 int /*<<< orphan*/  dlg_attrset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlg_draw_scrollbar (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int,int,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menubox_attr ; 
 int /*<<< orphan*/  menubox_border2_attr ; 
 int /*<<< orphan*/  menubox_border_attr ; 
 int /*<<< orphan*/  print_item (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  waddch (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wnoutrefresh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_menu(ALL_DATA * data, int choice, int scrollamt, int max_choice, bool is_inputmenu)
{
    int i;

    for (i = 0; i < max_choice; i++) {
	print_item(data,
		   data->menu,
		   &data->items[i + scrollamt],
		   i,
		   (i == choice) ? Selected : Unselected,
		   is_inputmenu);
    }

    /* Clean bottom lines */
    if (is_inputmenu) {
	int spare_lines, x_count;
	spare_lines = data->menu_height % INPUT_ROWS;
	dlg_attrset(data->menu, menubox_attr);
	for (; spare_lines; spare_lines--) {
	    wmove(data->menu, data->menu_height - spare_lines, 0);
	    for (x_count = 0; x_count < data->menu_width;
		 x_count++) {
		waddch(data->menu, ' ');
	    }
	}
    }

    (void) wnoutrefresh(data->menu);

    dlg_draw_scrollbar(data->dialog,
		       scrollamt,
		       scrollamt,
		       scrollamt + max_choice,
		       data->item_no,
		       data->box_x,
		       data->box_x + data->menu_width,
		       data->box_y,
		       data->box_y + data->menu_height + 1,
		       menubox_border2_attr,
		       menubox_border_attr);
}