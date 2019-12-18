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
struct TYPE_7__ {int item_x; int check_x; } ;
struct TYPE_6__ {char* name; char* text; int /*<<< orphan*/  help; } ;
typedef  TYPE_1__ DIALOG_LISTITEM ;
typedef  TYPE_2__ ALL_DATA ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 TYPE_5__ dialog_vars ; 
 int /*<<< orphan*/  dlg_attrset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlg_get_attrs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlg_item_help (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlg_print_listitem (int /*<<< orphan*/ *,char const*,int,int,int) ; 
 int getmaxx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  menubox_attr ; 
 int /*<<< orphan*/  waddch (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void
print_item(ALL_DATA * all,
	   WINDOW *win,
	   DIALOG_LISTITEM * item,
	   int row,
	   int selected)
{
    chtype save = dlg_get_attrs(win);
    int i;
    bool both = (!dialog_vars.no_tags && !dialog_vars.no_items);
    bool first = TRUE;
    int climit = (all->item_x - all->check_x - 1);
    const char *show = (dialog_vars.no_items
			? item->name
			: item->text);

    /* Clear 'residue' of last item */
    dlg_attrset(win, menubox_attr);
    (void) wmove(win, row, 0);
    for (i = 0; i < getmaxx(win); i++)
	(void) waddch(win, ' ');

    (void) wmove(win, row, all->check_x);
    dlg_attrset(win, menubox_attr);

    if (both) {
	dlg_print_listitem(win, item->name, climit, first, selected);
	(void) waddch(win, ' ');
	first = FALSE;
    }

    (void) wmove(win, row, all->item_x);
    climit = (getmaxx(win) - all->item_x + 1);
    dlg_print_listitem(win, show, climit, first, selected);

    if (selected) {
	dlg_item_help(item->help);
    }
    dlg_attrset(win, save);
}