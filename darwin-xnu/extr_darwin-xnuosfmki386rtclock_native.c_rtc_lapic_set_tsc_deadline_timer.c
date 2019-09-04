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

/* Variables and functions */
 int DBG_FUNC_NONE ; 
 int DECR_SET_TSC_DEADLINE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT (int,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ deadline_to_decrementer (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  lapic_get_tsc_deadline_timer () ; 
 int /*<<< orphan*/  lapic_set_tsc_deadline_timer (scalar_t__) ; 
 scalar_t__ rdtsc64 () ; 
 scalar_t__ tmrCvt (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tscFCvtn2t ; 

__attribute__((used)) static uint64_t
rtc_lapic_set_tsc_deadline_timer(uint64_t deadline, uint64_t now)
{
	uint64_t delta;
	uint64_t delta_tsc;
	uint64_t tsc = rdtsc64();
	uint64_t set = 0;

	if (deadline > 0) {
		/*
		 * Convert to TSC
		 */
		delta = deadline_to_decrementer(deadline, now);
		set = now + delta;
		delta_tsc = tmrCvt(delta, tscFCvtn2t);
		lapic_set_tsc_deadline_timer(tsc + delta_tsc);
	} else {
		lapic_set_tsc_deadline_timer(0);
	}
	
	KERNEL_DEBUG_CONSTANT(
		DECR_SET_TSC_DEADLINE | DBG_FUNC_NONE,
		now, deadline,
		tsc, lapic_get_tsc_deadline_timer(),
		0);

	return set;
}