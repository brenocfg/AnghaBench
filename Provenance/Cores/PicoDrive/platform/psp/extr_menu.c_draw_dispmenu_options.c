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

/* Variables and functions */
 int /*<<< orphan*/  OPT3_ENTRY_COUNT ; 
 int /*<<< orphan*/  me_draw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  menu_draw_begin () ; 
 int /*<<< orphan*/  menu_draw_end () ; 
 int /*<<< orphan*/  menu_draw_selection (int,int,int) ; 
 int /*<<< orphan*/  menu_opt3_cust_draw ; 
 int /*<<< orphan*/  opt3_entries ; 

__attribute__((used)) static void draw_dispmenu_options(int menu_sel)
{
	int tl_x = 80, tl_y = 16+50;

	menu_draw_begin();

	menu_draw_selection(tl_x - 16, tl_y + menu_sel*10, 316);

	me_draw(opt3_entries, OPT3_ENTRY_COUNT, tl_x, tl_y, menu_opt3_cust_draw, NULL);

	menu_draw_end();
}