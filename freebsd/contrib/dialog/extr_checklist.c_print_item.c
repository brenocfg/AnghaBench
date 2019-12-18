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
struct TYPE_7__ {int check_x; int use_width; scalar_t__ checkflag; int item_x; } ;
struct TYPE_6__ {char* name; char* text; size_t state; int /*<<< orphan*/  help; } ;
typedef  TYPE_1__ DIALOG_LISTITEM ;
typedef  TYPE_2__ ALL_DATA ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ FLAG_CHECK ; 
 int TRUE ; 
 int /*<<< orphan*/  check_attr ; 
 int /*<<< orphan*/  check_selected_attr ; 
 TYPE_5__ dialog_vars ; 
 int /*<<< orphan*/  dlg_attrset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlg_get_attrs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlg_item_help (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlg_print_listitem (int /*<<< orphan*/ *,char const*,int,int,int) ; 
 int getmaxx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  menubox_attr ; 
 int /*<<< orphan*/  waddch (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  wprintw (int /*<<< orphan*/ *,char*,char const) ; 

__attribute__((used)) static void
print_item(ALL_DATA * data,
	   WINDOW *win,
	   DIALOG_LISTITEM * item,
	   const char *states,
	   int choice,
	   int selected)
{
    chtype save = dlg_get_attrs(win);
    int i;
    bool both = (!dialog_vars.no_tags && !dialog_vars.no_items);
    bool first = TRUE;
    int climit = (getmaxx(win) - data->check_x + 1);
    const char *show = (dialog_vars.no_items
			? item->name
			: item->text);

    /* Clear 'residue' of last item */
    dlg_attrset(win, menubox_attr);
    (void) wmove(win, choice, 0);
    for (i = 0; i < data->use_width; i++)
	(void) waddch(win, ' ');

    (void) wmove(win, choice, data->check_x);
    dlg_attrset(win, selected ? check_selected_attr : check_attr);
    (void) wprintw(win,
		   (data->checkflag == FLAG_CHECK) ? "[%c]" : "(%c)",
		   states[item->state]);
    dlg_attrset(win, menubox_attr);
    (void) waddch(win, ' ');

    if (both) {
	dlg_print_listitem(win, item->name, climit, first, selected);
	first = FALSE;
    }

    (void) wmove(win, choice, data->item_x);
    dlg_print_listitem(win, show, climit, first, selected);

    if (selected) {
	dlg_item_help(item->help);
    }
    dlg_attrset(win, save);
}