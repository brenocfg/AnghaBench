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
struct kperf_timer {scalar_t__ period; int /*<<< orphan*/  tcall; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_INFO (int /*<<< orphan*/ ,scalar_t__,...) ; 
 unsigned int KPERF_SAMPLING_OFF ; 
 unsigned int KPERF_SAMPLING_SHUTDOWN ; 
 int /*<<< orphan*/  PERF_PET_END ; 
 int /*<<< orphan*/  PERF_PET_SCHED ; 
 int /*<<< orphan*/  SAMPLE_OFF ; 
 int /*<<< orphan*/  SAMPLE_SHUTDOWN ; 
 int /*<<< orphan*/  TIMER_CALL_SYS_CRITICAL ; 
 unsigned int kperf_sampling_status () ; 
 size_t kperf_timerc ; 
 struct kperf_timer* kperf_timerv ; 
 scalar_t__ mach_absolute_time () ; 
 scalar_t__ min_period_pet_abstime ; 
 size_t pet_timer_id ; 
 int /*<<< orphan*/  timer_call_enter (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

void
kperf_timer_pet_rearm(uint64_t elapsed_ticks)
{
	struct kperf_timer *timer = NULL;
	uint64_t period = 0;
	uint64_t deadline;

	/*
	 * If the pet_timer_id is invalid, it has been disabled, so this should
	 * do nothing.
	 */
	if (pet_timer_id >= kperf_timerc) {
		return;
	}

	unsigned int status = kperf_sampling_status();
	/* do not reprogram the timer if it has been shutdown or sampling is off */
	if (status == KPERF_SAMPLING_OFF) {
		BUF_INFO(PERF_PET_END, SAMPLE_OFF);
		return;
	} else if (status == KPERF_SAMPLING_SHUTDOWN) {
		BUF_INFO(PERF_PET_END, SAMPLE_SHUTDOWN);
		return;
	}

	timer = &(kperf_timerv[pet_timer_id]);

	/* if we re-programmed the timer to zero, just drop it */
	if (!timer->period) {
		return;
	}

	/* subtract the time the pet sample took being careful not to underflow */
	if (timer->period > elapsed_ticks) {
		period = timer->period - elapsed_ticks;
	}

	/* make sure we don't set the next PET sample to happen too soon */
	if (period < min_period_pet_abstime) {
		period = min_period_pet_abstime;
	}

	/* we probably took so long in the PET thread, it makes sense to take
	 * the time again.
	 */
	deadline = mach_absolute_time() + period;

	BUF_INFO(PERF_PET_SCHED, timer->period, period, elapsed_ticks, deadline);

	/* re-schedule the timer, making sure we don't apply slop */
	timer_call_enter(&timer->tcall, deadline, TIMER_CALL_SYS_CRITICAL);

	return;
}