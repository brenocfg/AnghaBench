#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  timebase_frequency_hz; } ;

/* Variables and functions */
 int /*<<< orphan*/  NSEC_PER_SEC ; 
 int /*<<< orphan*/  clock_interval_to_absolutetime_interval (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__ gPEClockFrequencyInfo ; 
 int /*<<< orphan*/  machclk_freq ; 
 int /*<<< orphan*/  machclk_per_sec ; 

__attribute__((used)) static void
init_machclk(void)
{
	/*
	 * Initialize machclk_freq using the timerbase frequency
	 * value from device specific info.
	 */
	machclk_freq = gPEClockFrequencyInfo.timebase_frequency_hz;

	clock_interval_to_absolutetime_interval(1, NSEC_PER_SEC,
	    &machclk_per_sec);
}