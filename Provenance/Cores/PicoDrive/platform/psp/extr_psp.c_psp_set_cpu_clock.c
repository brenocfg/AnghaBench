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
 int /*<<< orphan*/  lprintf (char*,int) ; 
 int scePowerSetClockFrequency (int,int,int) ; 

int psp_set_cpu_clock(int clock)
{
	int ret = scePowerSetClockFrequency(clock, clock, clock/2);
	if (ret != 0) lprintf("failed to set clock: %i\n", ret);

	return ret;
}