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
 int DBG_FUNC_NONE ; 
 int DECR_SET_APIC_DEADLINE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT (int,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LAPIC_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIMER_CURRENT_COUNT ; 
 int /*<<< orphan*/  busFCvtn2t ; 
 scalar_t__ deadline_to_decrementer (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  divide_by_1 ; 
 int /*<<< orphan*/  lapic_set_timer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lapic_set_timer_fast (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  one_shot ; 
 scalar_t__ tmrCvt (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t
rtc_lapic_set_timer(uint64_t deadline, uint64_t now)
{
	uint64_t count;
	uint64_t set = 0;

	if (deadline > 0) {
		/*
		 * Convert delta to bus ticks
		 * - time now is not relevant
		 */
		count = deadline_to_decrementer(deadline, now);
		set = now + count;
		lapic_set_timer_fast((uint32_t) tmrCvt(count, busFCvtn2t));
	} else {
		lapic_set_timer(FALSE, one_shot, divide_by_1, 0);
	}

	KERNEL_DEBUG_CONSTANT(
		DECR_SET_APIC_DEADLINE | DBG_FUNC_NONE,
		now, deadline,
		set, LAPIC_READ(TIMER_CURRENT_COUNT),
		0);

	return set;
}