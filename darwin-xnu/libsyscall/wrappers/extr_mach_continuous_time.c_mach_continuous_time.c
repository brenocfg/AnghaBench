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
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ _mach_continuous_hwclock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _mach_continuous_time (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

uint64_t
mach_continuous_time(void)
{
	uint64_t cont_time;
	if (_mach_continuous_hwclock(&cont_time) != KERN_SUCCESS)
		_mach_continuous_time(NULL, &cont_time);
	return cont_time;
}