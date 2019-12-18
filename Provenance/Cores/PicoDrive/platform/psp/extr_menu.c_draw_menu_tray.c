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
 char* menuErrorMsg ; 
 int /*<<< orphan*/  menu_draw_begin () ; 
 int /*<<< orphan*/  menu_draw_end () ; 
 int /*<<< orphan*/  text_out16 (int,int,char*) ; 

__attribute__((used)) static void draw_menu_tray(int menu_sel)
{
	int tl_x = 70, tl_y = 90, y;

	menu_draw_begin();

	text_out16(tl_x, 20, "The unit is about to");
	text_out16(tl_x, 30, "close the CD tray.");

	y = tl_y;
	text_out16(tl_x, y,       "Load new CD image");
	text_out16(tl_x, (y+=10), "Insert nothing");

	// draw cursor
	text_out16(tl_x - 16, tl_y + menu_sel*10, ">");
	// error
	if (menuErrorMsg[0]) text_out16(5, 226, menuErrorMsg);
	menu_draw_end();
}