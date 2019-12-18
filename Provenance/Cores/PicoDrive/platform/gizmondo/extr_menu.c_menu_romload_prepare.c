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
 int /*<<< orphan*/  PicoCartLoadProgressCB ; 
 int /*<<< orphan*/  load_progress_cb ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  menu_draw_begin (int) ; 
 int /*<<< orphan*/  menu_draw_end () ; 
 int /*<<< orphan*/  menu_screen ; 
 int /*<<< orphan*/  rom_loaded ; 
 int /*<<< orphan*/  smalltext_out16 (int,int,char*,int) ; 
 int /*<<< orphan*/  smalltext_out16_lim (int,int,char const*,int,int) ; 
 int strlen (char const*) ; 

void menu_romload_prepare(const char *rom_name)
{
	const char *p = rom_name + strlen(rom_name);
	while (p > rom_name && *p != '/') p--;

	if (!rom_loaded)
		memset(menu_screen, 0, 321*240*2);
	menu_draw_begin(1);

	smalltext_out16(1, 1, "Loading", 0xffff);
	smalltext_out16_lim(1, 10, p, 0xffff, 53);
	menu_draw_end();
	PicoCartLoadProgressCB = load_progress_cb;
}