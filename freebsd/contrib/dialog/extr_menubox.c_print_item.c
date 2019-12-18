#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  chtype ;
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_8__ {scalar_t__ no_items; int /*<<< orphan*/  no_tags; } ;
struct TYPE_7__ {int item_x; int tag_x; int menu_width; } ;
struct TYPE_6__ {char* name; char* text; int /*<<< orphan*/  help; } ;
typedef  int const Mode ;
typedef  TYPE_1__ DIALOG_LISTITEM ;
typedef  TYPE_2__ ALL_DATA ;

/* Variables and functions */
#define  Editing 130 
 int FALSE ; 
 int GUTTER ; 
 int INPUT_ROWS ; 
 int ItemToRow (int) ; 
#define  Selected 129 
 int TRUE ; 
#define  Unselected 128 
 int /*<<< orphan*/  dialog_attr ; 
 TYPE_5__ dialog_vars ; 
 int /*<<< orphan*/  dlg_attrset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlg_draw_box (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlg_get_attrs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlg_item_help (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlg_print_listitem (int /*<<< orphan*/ *,char const*,int,int,int const) ; 
 int /*<<< orphan*/  item_attr ; 
 int /*<<< orphan*/  item_selected_attr ; 
 int /*<<< orphan*/  menubox_attr ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  wprintw (int /*<<< orphan*/ *,char*,int,char*) ; 

__attribute__((used)) static void
print_item(ALL_DATA * data,
	   WINDOW *win,
	   DIALOG_LISTITEM * item,
	   int choice,
	   Mode selected,
	   bool is_inputmenu)
{
    chtype save = dlg_get_attrs(win);
    int n;
    int climit = (data->item_x - data->tag_x - GUTTER);
    int my_width = data->menu_width;
    int my_x = data->item_x;
    int my_y = ItemToRow(choice);
    bool both = (!dialog_vars.no_tags && !dialog_vars.no_items);
    bool first = TRUE;
    chtype bordchar;
    const char *show = (dialog_vars.no_items
			? item->name
			: item->text);

    switch (selected) {
    default:
    case Unselected:
	bordchar = item_attr;
	break;
    case Selected:
	bordchar = item_selected_attr;
	break;
    case Editing:
	bordchar = dialog_attr;
	break;
    }

    /* Clear 'residue' of last item and mark current current item */
    if (is_inputmenu) {
	dlg_attrset(win, (selected != Unselected) ? item_selected_attr : item_attr);
	for (n = my_y - 1; n < my_y + INPUT_ROWS - 1; n++) {
	    wmove(win, n, 0);
	    wprintw(win, "%*s", my_width, " ");
	}
    } else {
	dlg_attrset(win, menubox_attr);
	wmove(win, my_y, 0);
	wprintw(win, "%*s", my_width, " ");
    }

    /* highlight first char of the tag to be special */
    if (both) {
	(void) wmove(win, my_y, data->tag_x);
	dlg_print_listitem(win, item->name, climit, first, selected);
	first = FALSE;
    }

    /* Draw the input field box (only for inputmenu) */
    (void) wmove(win, my_y, my_x);
    if (is_inputmenu) {
	my_width -= 1;
	dlg_draw_box(win, my_y - 1, my_x, INPUT_ROWS, my_width - my_x - data->tag_x,
		     bordchar,
		     bordchar);
	my_width -= 1;
	++my_x;
    }

    /* print actual item */
    wmove(win, my_y, my_x);
    dlg_print_listitem(win, show, my_width - my_x, first, selected);

    if (selected) {
	dlg_item_help(item->help);
    }
    dlg_attrset(win, save);
}