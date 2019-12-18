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
typedef  int /*<<< orphan*/  event_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  THREAD_CONTINUE_NULL ; 
 int /*<<< orphan*/  THREAD_UNINT ; 
 int /*<<< orphan*/  TIMEOUT_URGENCY_LEEWAY ; 
 int /*<<< orphan*/  assert_wait_deadline (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  assert_wait_deadline_with_leeway (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ clock_delay_until ; 
 scalar_t__ get_preemption_level () ; 
 int /*<<< orphan*/  machine_delay_until (scalar_t__,scalar_t__) ; 
 scalar_t__ ml_delay_should_spin (scalar_t__) ; 
 scalar_t__ ml_get_interrupts_enabled () ; 
 int /*<<< orphan*/  thread_block (int /*<<< orphan*/ ) ; 

void
_clock_delay_until_deadline_with_leeway(
	uint64_t		interval,
	uint64_t		deadline,
	uint64_t		leeway)
{

	if (interval == 0)
		return;

	if (	ml_delay_should_spin(interval)	||
			get_preemption_level() != 0				||
			ml_get_interrupts_enabled() == FALSE	) {
		machine_delay_until(interval, deadline);
	} else {
		/*
		 * For now, assume a leeway request of 0 means the client does not want a leeway
		 * value. We may want to change this interpretation in the future.
		 */

		if (leeway) {
			assert_wait_deadline_with_leeway((event_t)clock_delay_until, THREAD_UNINT, TIMEOUT_URGENCY_LEEWAY, deadline, leeway);
		} else {
			assert_wait_deadline((event_t)clock_delay_until, THREAD_UNINT, deadline);
		}

		thread_block(THREAD_CONTINUE_NULL);
	}
}