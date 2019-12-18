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
typedef  int uint32_t ;

/* Variables and functions */
 int LAPIC_LVT_MASKED ; 
 int LAPIC_LVT_TSC_DEADLINE ; 
 int LAPIC_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LAPIC_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LVT_TIMER ; 
 int /*<<< orphan*/  MSR_IA32_TSC_DEADLINE ; 
 int /*<<< orphan*/  TIMER_INITIAL_COUNT ; 
 int /*<<< orphan*/  wrmsr64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
lapic_disable_timer(void)
{
	uint32_t	lvt_timer;

	/*
         * If we're in deadline timer mode,
	 * simply clear the deadline timer, otherwise
	 * mask the timer interrupt and clear the countdown.
         */
	lvt_timer = LAPIC_READ(LVT_TIMER);
	if (lvt_timer & LAPIC_LVT_TSC_DEADLINE) {
		wrmsr64(MSR_IA32_TSC_DEADLINE, 0);
	} else {
		LAPIC_WRITE(LVT_TIMER, lvt_timer | LAPIC_LVT_MASKED);
		LAPIC_WRITE(TIMER_INITIAL_COUNT, 0);
		lvt_timer = LAPIC_READ(LVT_TIMER);
	}
}