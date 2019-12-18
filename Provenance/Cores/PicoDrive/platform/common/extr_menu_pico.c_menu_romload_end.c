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
 int /*<<< orphan*/ * PicoCDLoadProgressCB ; 
 int /*<<< orphan*/ * PicoCartLoadProgressCB ; 
 scalar_t__ cdload_called ; 
 int me_sfont_h ; 
 int /*<<< orphan*/  menu_draw_begin (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  menu_draw_end () ; 
 int /*<<< orphan*/  smalltext_out16 (int,int,char*,int) ; 

void menu_romload_end(void)
{
	PicoCartLoadProgressCB = NULL;
	PicoCDLoadProgressCB = NULL;

	menu_draw_begin(0, 1);
	smalltext_out16(1, (cdload_called ? 6 : 3) * me_sfont_h,
		"Starting emulation...", 0xffff);
	menu_draw_end();
}