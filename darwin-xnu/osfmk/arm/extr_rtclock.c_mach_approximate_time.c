#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  TYPE_1__* processor_t ;
struct TYPE_3__ {int /*<<< orphan*/  last_dispatch; } ;

/* Variables and functions */
 TYPE_1__* current_processor () ; 
 int /*<<< orphan*/  disable_preemption () ; 
 int /*<<< orphan*/  enable_preemption () ; 
 int /*<<< orphan*/  ml_get_timebase () ; 

uint64_t
mach_approximate_time(void)
{
#if __ARM_TIME__ || __ARM_TIME_TIMEBASE_ONLY__ || __arm64__
	/* Hardware supports a fast timestamp, so grab it without asserting monotonicity */
	return ml_get_timebase();
#else
	processor_t processor;
	uint64_t    approx_time;

	disable_preemption();
	processor = current_processor();
	approx_time = processor->last_dispatch;
	enable_preemption();

	return approx_time;
#endif
}