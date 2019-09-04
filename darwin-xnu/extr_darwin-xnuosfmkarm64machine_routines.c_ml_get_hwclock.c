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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */

uint64_t ml_get_hwclock()
{
	uint64_t timebase;

	// ISB required by ARMV7C.b section B8.1.2 & ARMv8 section D6.1.2
	// "Reads of CNTPCT[_EL0] can occur speculatively and out of order relative
	// to other instructions executed on the same processor."
	__asm__ volatile("isb\n"
			 "mrs %0, CNTPCT_EL0"
			 : "=r"(timebase));

	return timebase;
}