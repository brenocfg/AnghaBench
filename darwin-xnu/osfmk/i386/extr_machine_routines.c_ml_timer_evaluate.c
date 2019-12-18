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
 int /*<<< orphan*/  ASYNC ; 
 int /*<<< orphan*/  CPUMASK_ALL ; 
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int DECR_TIMER_RESCAN ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ mach_absolute_time () ; 
 int /*<<< orphan*/  ml_timer_eager_evaluation_max ; 
 int /*<<< orphan*/  ml_timer_eager_evaluations ; 
 int /*<<< orphan*/  ml_timer_evaluation_in_progress ; 
 int /*<<< orphan*/  ml_timer_evaluation_slock ; 
 int /*<<< orphan*/  mp_cpus_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_call_delayed_timer_rescan_all () ; 
 int /*<<< orphan*/  timer_queue_expire_rescan ; 

void ml_timer_evaluate(void) {
	KERNEL_DEBUG_CONSTANT(DECR_TIMER_RESCAN|DBG_FUNC_START, 0, 0, 0, 0, 0);

	uint64_t te_end, te_start = mach_absolute_time();
	simple_lock(&ml_timer_evaluation_slock);
	ml_timer_evaluation_in_progress = TRUE;
	thread_call_delayed_timer_rescan_all();
	mp_cpus_call(CPUMASK_ALL, ASYNC, timer_queue_expire_rescan, NULL);
	ml_timer_evaluation_in_progress = FALSE;
	ml_timer_eager_evaluations++;
	te_end = mach_absolute_time();
	ml_timer_eager_evaluation_max = MAX(ml_timer_eager_evaluation_max, (te_end - te_start));
	simple_unlock(&ml_timer_evaluation_slock);

	KERNEL_DEBUG_CONSTANT(DECR_TIMER_RESCAN|DBG_FUNC_END, 0, 0, 0, 0, 0);
}