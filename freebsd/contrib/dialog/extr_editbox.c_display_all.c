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
typedef  int /*<<< orphan*/  WINDOW ;

/* Variables and functions */
 int /*<<< orphan*/  dialog_attr ; 
 int /*<<< orphan*/  display_one (int /*<<< orphan*/ *,char*,int,int,int,int) ; 
 int /*<<< orphan*/  dlg_attr_clear (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getmaxx (int /*<<< orphan*/ *) ; 
 int getmaxy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
display_all(WINDOW *win,
	    char **list,
	    int show_row,
	    int firstrow,
	    int lastrow,
	    int chr_offset)
{
    int limit = getmaxy(win);
    int row;

    dlg_attr_clear(win, getmaxy(win), getmaxx(win), dialog_attr);
    if (lastrow - firstrow >= limit)
	lastrow = firstrow + limit;
    for (row = firstrow; row < lastrow; ++row) {
	if (!display_one(win, list[row],
			 row, show_row, firstrow,
			 (row == show_row) ? chr_offset : 0))
	    break;
    }
}