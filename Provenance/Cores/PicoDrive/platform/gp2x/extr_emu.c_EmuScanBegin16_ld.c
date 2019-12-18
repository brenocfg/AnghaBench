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
 char* DrawLineDest ; 
 int emu_scan_begin (unsigned int) ; 
 scalar_t__ g_screen_ptr ; 
 int gp2x_current_bpp ; 
 unsigned int ld_counter ; 

__attribute__((used)) static int EmuScanBegin16_ld(unsigned int num)
{
	if ((signed int)(ld_counter - num) > 100)
		ld_counter = 0;

	if (emu_scan_begin)
		return emu_scan_begin(ld_counter);
	else
		DrawLineDest = (char *)g_screen_ptr + 320 * ld_counter * gp2x_current_bpp / 8;

	return 0;
}