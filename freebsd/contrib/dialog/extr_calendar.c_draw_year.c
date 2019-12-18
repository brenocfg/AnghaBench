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
struct tm {int tm_year; } ;
struct TYPE_3__ {int /*<<< orphan*/  window; scalar_t__ width; scalar_t__ height; scalar_t__ x; scalar_t__ y; int /*<<< orphan*/  parent; } ;
typedef  TYPE_1__ BOX ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  dialog_attr ; 
 int /*<<< orphan*/  dlg_attrset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlg_draw_box2 (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  item_attr ; 
 int /*<<< orphan*/  menubox_attr ; 
 int /*<<< orphan*/  menubox_border2_attr ; 
 int /*<<< orphan*/  menubox_border_attr ; 
 int /*<<< orphan*/  mvwprintw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
draw_year(BOX * data, struct tm *current)
{
    int year = current->tm_year + 1900;

    dlg_attrset(data->parent, dialog_attr);	/* Headline "Year" */
    (void) mvwprintw(data->parent, data->y - 2, data->x - 1, _("Year"));
    dlg_draw_box2(data->parent,
		  data->y - 1, data->x - 1,
		  data->height + 2, data->width + 2,
		  menubox_attr,
		  menubox_border_attr,
		  menubox_border2_attr);
    dlg_attrset(data->window, item_attr);	/* color the year selection */
    mvwprintw(data->window, 0, 0, "%4d", year);
    wmove(data->window, 0, 0);
    return 0;
}