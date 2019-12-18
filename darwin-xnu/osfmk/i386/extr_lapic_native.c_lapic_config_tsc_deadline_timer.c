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
 int /*<<< orphan*/  DBG (char*) ; 
 int LAPIC_LVT_MASKED ; 
 int LAPIC_LVT_PERIODIC ; 
 int LAPIC_LVT_TSC_DEADLINE ; 
 int LAPIC_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LAPIC_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LVT_TIMER ; 
 scalar_t__ lapic_get_tsc_deadline_timer () ; 
 int /*<<< orphan*/  lapic_set_tsc_deadline_timer (scalar_t__) ; 
 int /*<<< orphan*/  mp_disable_preemption () ; 
 int /*<<< orphan*/  mp_enable_preemption () ; 
 scalar_t__ rdtsc64 () ; 

void
lapic_config_tsc_deadline_timer(void)
{
	uint32_t	timer_vector;

	DBG("lapic_config_tsc_deadline_timer()\n");
	mp_disable_preemption();
	timer_vector = LAPIC_READ(LVT_TIMER);
	timer_vector &= ~(LAPIC_LVT_MASKED |
			  LAPIC_LVT_PERIODIC);
	timer_vector |= LAPIC_LVT_TSC_DEADLINE;
	LAPIC_WRITE(LVT_TIMER, timer_vector);

	/* Serialize writes per Intel OSWG */
	do {
		lapic_set_tsc_deadline_timer(rdtsc64() + (1ULL<<32));
	} while (lapic_get_tsc_deadline_timer() == 0);
	lapic_set_tsc_deadline_timer(0);

	mp_enable_preemption();
	DBG("lapic_config_tsc_deadline_timer() done\n");
}