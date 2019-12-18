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
 int /*<<< orphan*/  menu_draw_begin () ; 
 int /*<<< orphan*/  menu_draw_end () ; 
 int /*<<< orphan*/  menu_prepare_bg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rom_loaded ; 

__attribute__((used)) static void menu_gfx_prepare(void)
{
	menu_prepare_bg(rom_loaded, 1);

	menu_draw_begin();
	menu_draw_end();
}