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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  _clock_delay_until_deadline (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  clock_interval_to_absolutetime_interval (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ mach_absolute_time () ; 

void
delay_for_interval(
	uint32_t		interval,
	uint32_t		scale_factor)
{
	uint64_t		abstime;

	clock_interval_to_absolutetime_interval(interval, scale_factor, &abstime);

	_clock_delay_until_deadline(abstime, mach_absolute_time() + abstime);
}