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

void machine_halt(void)
{
	/*
	 * Enter Stop mode. The 32 kHz oscillator will keep running so
	 * the RTC will keep the time properly and the system will
	 * boot quickly.
	 */
	asm volatile("sleep 3\n\t"
		     "sub pc, -2");
}