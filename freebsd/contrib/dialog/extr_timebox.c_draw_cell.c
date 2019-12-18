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
struct TYPE_3__ {int /*<<< orphan*/  value; int /*<<< orphan*/  window; scalar_t__ width; scalar_t__ height; scalar_t__ x; scalar_t__ y; int /*<<< orphan*/  parent; } ;
typedef  TYPE_1__ BOX ;

/* Variables and functions */
 int MARGIN ; 
 int /*<<< orphan*/  dlg_attrset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlg_draw_box (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  item_attr ; 
 int /*<<< orphan*/  menubox_border2_attr ; 
 int /*<<< orphan*/  menubox_border_attr ; 
 int /*<<< orphan*/  werase (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wprintw (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
draw_cell(BOX * data)
{
    werase(data->window);
    dlg_draw_box(data->parent,
		 data->y - MARGIN, data->x - MARGIN,
		 data->height + (2 * MARGIN), data->width + (2 * MARGIN),
		 menubox_border_attr, menubox_border2_attr);

    dlg_attrset(data->window, item_attr);
    wprintw(data->window, "%02d", data->value);
    return 0;
}