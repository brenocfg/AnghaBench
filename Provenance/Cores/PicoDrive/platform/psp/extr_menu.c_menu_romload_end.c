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
 int /*<<< orphan*/  PicoCartLoadProgressCB ; 
 int lcdr_line ; 
 int /*<<< orphan*/  smalltext_out16 (int,int,char*,int) ; 

void menu_romload_end(void)
{
	PicoCartLoadProgressCB = PicoCDLoadProgressCB = NULL;
	smalltext_out16(1, ++lcdr_line*10, "Starting emulation...", 0xffff);
}