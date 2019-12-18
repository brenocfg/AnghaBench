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
 int /*<<< orphan*/  draw_savestate_bg (int) ; 
 int /*<<< orphan*/  menu_draw_begin () ; 
 int /*<<< orphan*/  menu_draw_end () ; 
 int /*<<< orphan*/  menu_draw_selection (int,int,int) ; 
 int state_slot_flags ; 
 int /*<<< orphan*/  text_out16 (int,int,char*,...) ; 

__attribute__((used)) static void draw_savestate_menu(int menu_sel, int is_loading)
{
	int tl_x = 80+25, tl_y = 16+60, y, i;

	if (state_slot_flags & (1 << menu_sel))
		draw_savestate_bg(menu_sel);
	menu_draw_begin();

	text_out16(tl_x, 16+30, is_loading ? "Load state" : "Save state");

	menu_draw_selection(tl_x - 16, tl_y + menu_sel*10, 108);

	/* draw all 10 slots */
	y = tl_y;
	for (i = 0; i < 10; i++, y+=10)
	{
		text_out16(tl_x, y, "SLOT %i (%s)", i, (state_slot_flags & (1 << i)) ? "USED" : "free");
	}
	text_out16(tl_x, y, "back");

	menu_draw_end();
}