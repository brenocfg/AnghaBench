#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_15__ {int /*<<< orphan*/  atr; } ;
struct TYPE_14__ {int /*<<< orphan*/  atr; } ;
struct TYPE_13__ {int /*<<< orphan*/  atr; } ;
struct TYPE_12__ {int /*<<< orphan*/  atr; } ;
struct TYPE_11__ {int /*<<< orphan*/  atr; } ;
struct TYPE_10__ {int /*<<< orphan*/  atr; } ;
struct TYPE_9__ {int /*<<< orphan*/  atr; } ;
struct TYPE_16__ {TYPE_7__ item; TYPE_6__ item_selected; TYPE_5__ tag; TYPE_4__ tag_selected; TYPE_3__ check; TYPE_2__ check_selected; TYPE_1__ menubox; } ;

/* Variables and functions */
 scalar_t__ check_x ; 
 TYPE_8__ dlg ; 
 scalar_t__ item_is_tag (char) ; 
 int /*<<< orphan*/ * item_str () ; 
 int /*<<< orphan*/  item_x ; 
 int list_width ; 
 int /*<<< orphan*/  mvwaddch (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waddch (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  waddstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  wattrset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ *,int,scalar_t__) ; 
 int /*<<< orphan*/  wprintw (int /*<<< orphan*/ *,char*,char) ; 
 int /*<<< orphan*/  wrefresh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void print_item(WINDOW * win, int choice, int selected)
{
	int i;

	/* Clear 'residue' of last item */
	wattrset(win, dlg.menubox.atr);
	wmove(win, choice, 0);
	for (i = 0; i < list_width; i++)
		waddch(win, ' ');

	wmove(win, choice, check_x);
	wattrset(win, selected ? dlg.check_selected.atr
		 : dlg.check.atr);
	if (!item_is_tag(':'))
		wprintw(win, "(%c)", item_is_tag('X') ? 'X' : ' ');

	wattrset(win, selected ? dlg.tag_selected.atr : dlg.tag.atr);
	mvwaddch(win, choice, item_x, item_str()[0]);
	wattrset(win, selected ? dlg.item_selected.atr : dlg.item.atr);
	waddstr(win, (char *)item_str() + 1);
	if (selected) {
		wmove(win, choice, check_x + 1);
		wrefresh(win);
	}
}