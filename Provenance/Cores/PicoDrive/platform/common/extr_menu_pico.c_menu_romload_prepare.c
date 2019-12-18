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
 int /*<<< orphan*/  PicoCDLoadProgressCB ; 
 int /*<<< orphan*/  PicoCartLoadProgressCB ; 
 scalar_t__ cdload_called ; 
 int /*<<< orphan*/  cdload_progress_cb ; 
 int /*<<< orphan*/  load_progress_cb ; 
 int me_sfont_h ; 
 int /*<<< orphan*/  menu_draw_begin (int,int) ; 
 int /*<<< orphan*/  menu_draw_end () ; 
 int /*<<< orphan*/  smalltext_out16 (int,int,char const*,int) ; 
 int strlen (char const*) ; 

void menu_romload_prepare(const char *rom_name)
{
	const char *p = rom_name + strlen(rom_name);
	int i;

	while (p > rom_name && *p != '/')
		p--;

	/* fill all buffers, callbacks won't update in full */
	for (i = 0; i < 3; i++) {
		menu_draw_begin(1, 1);
		smalltext_out16(1, 1, "Loading", 0xffff);
		smalltext_out16(1, me_sfont_h, p, 0xffff);
		menu_draw_end();
	}

	PicoCartLoadProgressCB = load_progress_cb;
	PicoCDLoadProgressCB = cdload_progress_cb;
	cdload_called = 0;
}