#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
typedef  TYPE_2__* task_pend_token_t ;
typedef  int /*<<< orphan*/  spl_t ;
typedef  scalar_t__ sched_mode_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  scalar_t__ integer_t ;
struct TYPE_9__ {int tpt_update_thread_sfi; } ;
struct TYPE_8__ {scalar_t__ sched_mode; scalar_t__ saved_mode; scalar_t__ max_priority; scalar_t__ task_priority; scalar_t__ importance; scalar_t__ policy_reset; } ;

/* Variables and functions */
 scalar_t__ BASEPRI_DEFAULT ; 
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 scalar_t__ MINPRI ; 
 scalar_t__ MINPRI_KERNEL ; 
 scalar_t__ MINPRI_RESERVED ; 
 scalar_t__ TH_MODE_REALTIME ; 
 int /*<<< orphan*/  splsched () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_set_user_sched_mode_and_recompute_pri (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  thread_unlock (TYPE_1__*) ; 

__attribute__((used)) static kern_return_t
thread_set_mode_and_absolute_pri_internal(thread_t              thread,
                                          sched_mode_t          mode,
                                          integer_t             priority,
                                          task_pend_token_t     pend_token)
{
	kern_return_t kr = KERN_SUCCESS;

	spl_t s = splsched();
	thread_lock(thread);

	/* This path isn't allowed to change a thread out of realtime. */
	if ((thread->sched_mode == TH_MODE_REALTIME) ||
	    (thread->saved_mode == TH_MODE_REALTIME)) {
		kr = KERN_FAILURE;
		goto unlock;
	}

	if (thread->policy_reset) {
		kr = KERN_SUCCESS;
		goto unlock;
	}

	sched_mode_t old_mode = thread->sched_mode;

	/*
	 * Reverse engineer and apply the correct importance value
	 * from the requested absolute priority value.
	 *
	 * TODO: Store the absolute priority value instead
	 */

	if (priority >= thread->max_priority)
		priority = thread->max_priority - thread->task_priority;
	else if (priority >= MINPRI_KERNEL)
		priority -=  MINPRI_KERNEL;
	else if (priority >= MINPRI_RESERVED)
		priority -=  MINPRI_RESERVED;
	else
		priority -= BASEPRI_DEFAULT;

	priority += thread->task_priority;

	if (priority > thread->max_priority)
		priority = thread->max_priority;
	else if (priority < MINPRI)
		priority = MINPRI;

	thread->importance = priority - thread->task_priority;

	thread_set_user_sched_mode_and_recompute_pri(thread, mode);

	if (mode != old_mode)
		pend_token->tpt_update_thread_sfi = 1;

unlock:
	thread_unlock(thread);
	splx(s);

	return kr;
}