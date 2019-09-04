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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  thread_t ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 scalar_t__ MIN (scalar_t__,scalar_t__) ; 
 scalar_t__ TIMER_CALL_SYS_CRITICAL ; 
 scalar_t__ TIMER_CALL_URGENCY_MASK ; 
 scalar_t__ mach_timer_coalescing_enabled ; 
 int /*<<< orphan*/  timer_compute_leeway (int /*<<< orphan*/ ,scalar_t__,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ timer_user_idle_level ; 

uint64_t
timer_call_slop(uint64_t deadline, uint64_t now, uint32_t flags, thread_t cthread, boolean_t *pratelimited)
{
	int32_t tcs_shift = 0;
	uint64_t tcs_max_abstime = 0;
	uint64_t adjval;
	uint32_t urgency = (flags & TIMER_CALL_URGENCY_MASK);

	if (mach_timer_coalescing_enabled && 
	    (deadline > now) && (urgency != TIMER_CALL_SYS_CRITICAL)) {
		timer_compute_leeway(cthread, urgency, &tcs_shift, &tcs_max_abstime, pratelimited);
	
		if (tcs_shift >= 0)
			adjval =  MIN((deadline - now) >> tcs_shift, tcs_max_abstime);
		else
			adjval =  MIN((deadline - now) << (-tcs_shift), tcs_max_abstime);
		/* Apply adjustments derived from "user idle level" heuristic */
		adjval += (adjval * timer_user_idle_level) >> 7;
		return adjval;
 	} else {
		return 0;
	}
}