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
 int /*<<< orphan*/  ctrlopt_entries ; 
 int /*<<< orphan*/  ctrlopt_entry_count ; 
 int /*<<< orphan*/  me_draw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  menu_draw_begin (int) ; 
 int /*<<< orphan*/  menu_draw_end () ; 
 int /*<<< orphan*/  menu_draw_selection (int,int,int) ; 

__attribute__((used)) static void draw_kc_sel(int menu_sel)
{
	int tl_x = 25+40, tl_y = 60, y;

	y = tl_y;
	menu_draw_begin(1);
	menu_draw_selection(tl_x - 16, tl_y + menu_sel*10, 138);

	me_draw(ctrlopt_entries, ctrlopt_entry_count, tl_x, tl_y, NULL, NULL);

	menu_draw_end();
}