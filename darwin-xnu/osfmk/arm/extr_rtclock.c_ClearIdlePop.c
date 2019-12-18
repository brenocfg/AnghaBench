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
struct TYPE_3__ {int cpu_idle_pop; int /*<<< orphan*/  rtcPop; } ;
typedef  TYPE_1__ cpu_data_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 TYPE_1__* getCpuDatap () ; 
 scalar_t__ ml_get_timer_pending () ; 
 int /*<<< orphan*/  setPop (int /*<<< orphan*/ ) ; 

void
ClearIdlePop(
             boolean_t wfi)
{
#if !__arm64__
#pragma unused(wfi)
#endif
	cpu_data_t * cdp;

	cdp = getCpuDatap();
	cdp->cpu_idle_pop = 0x0ULL;

#if __arm64__
	/*
	 * Don't update the HW timer if there's a pending
	 * interrupt (we can lose interrupt assertion);
	 * we want to take the interrupt right now and update
	 * the deadline from the handler).
	 *
	 * ARM64_TODO: consider this more carefully.
	 */
	if (!(wfi && ml_get_timer_pending()))
#endif
	{
		setPop(cdp->rtcPop);
	}
}