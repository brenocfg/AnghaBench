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
 int ANTIC_break_ypos ; 
 int /*<<< orphan*/  get_dec (int*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void monitor_bline(void)
{
	get_dec(&ANTIC_break_ypos);
	if (ANTIC_break_ypos >= 1008 && ANTIC_break_ypos <= 1247)
		printf("Blinking scanline %d\n", ANTIC_break_ypos - 1000);
#ifdef MONITOR_BREAK
	else if (ANTIC_break_ypos >= 0 && ANTIC_break_ypos <= 311)
		printf("Breakpoint set at scanline %d\n", ANTIC_break_ypos);
#endif
	else
		printf("BLINE disabled\n");
}