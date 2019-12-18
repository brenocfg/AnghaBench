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
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  NSEC_PER_SEC ; 
 int /*<<< orphan*/  THREAD_CALL_DELAY_LEEWAY ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  clock_interval_to_absolutetime_interval (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clock_interval_to_deadline (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inpcb_fast_thread_call ; 
 scalar_t__ inpcb_fast_timer_on ; 
 scalar_t__ inpcb_garbage_collecting ; 
 int /*<<< orphan*/  inpcb_thread_call ; 
 scalar_t__ inpcb_ticking ; 
 int /*<<< orphan*/  inpcb_timeout_lock ; 
 int inpcb_timeout_run ; 
 int /*<<< orphan*/  lck_mtx_convert_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_call_enter_delayed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_call_enter_delayed_with_leeway (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_inpcb_sched_timeout(unsigned int offset)
{
	uint64_t deadline, leeway;

	clock_interval_to_deadline(1, NSEC_PER_SEC, &deadline);
	LCK_MTX_ASSERT(&inpcb_timeout_lock, LCK_MTX_ASSERT_OWNED);
	if (inpcb_timeout_run == 0 &&
	    (inpcb_garbage_collecting || inpcb_ticking)) {
		lck_mtx_convert_spin(&inpcb_timeout_lock);
		inpcb_timeout_run++;
		if (offset == 0) {
			inpcb_fast_timer_on = TRUE;
			thread_call_enter_delayed(inpcb_thread_call,
			    deadline);
		} else {
			inpcb_fast_timer_on = FALSE;
			clock_interval_to_absolutetime_interval(offset,
			    NSEC_PER_SEC, &leeway);
			thread_call_enter_delayed_with_leeway(
			    inpcb_thread_call, NULL, deadline, leeway,
			    THREAD_CALL_DELAY_LEEWAY);
		}
	} else if (inpcb_timeout_run == 1 &&
	    offset == 0 && !inpcb_fast_timer_on) {
		/*
		 * Since the request was for a fast timer but the
		 * scheduled timer is a lazy timer, try to schedule
		 * another instance of fast timer also.
		 */
		lck_mtx_convert_spin(&inpcb_timeout_lock);
		inpcb_timeout_run++;
		inpcb_fast_timer_on = TRUE;
		thread_call_enter_delayed(inpcb_fast_thread_call, deadline);
	}
}