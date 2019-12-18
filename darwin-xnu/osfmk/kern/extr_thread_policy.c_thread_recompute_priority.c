#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* thread_t ;
typedef  int integer_t ;
struct TYPE_8__ {int* qos_pri; } ;
struct TYPE_6__ {int thep_qos; int thep_qos_ui_is_urgent; int thep_qos_relprio; scalar_t__ thep_terminated; } ;
struct TYPE_7__ {scalar_t__ sched_mode; int importance; int task_priority; int max_priority; scalar_t__ saved_mode; int sched_flags; TYPE_1__ effective_policy; int /*<<< orphan*/  user_promotion_basepri; scalar_t__ policy_reset; } ;

/* Variables and functions */
 int BASEPRI_DEFAULT ; 
 int BASEPRI_RTQUEUES ; 
 int DEPRESSPRI ; 
 int MAX (int,int /*<<< orphan*/ ) ; 
 int MAXPRI ; 
 int MAXPRI_THROTTLE ; 
 int MINPRI ; 
 int THREAD_QOS_LAST ; 
 int THREAD_QOS_MIN_TIER_IMPORTANCE ; 
 int THREAD_QOS_UNSPECIFIED ; 
 int THREAD_QOS_USER_INTERACTIVE ; 
 scalar_t__ TH_MODE_REALTIME ; 
 int TH_SFLAG_FAILSAFE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sched_set_thread_base_priority (TYPE_2__*,int) ; 
 TYPE_4__ thread_qos_policy_params ; 
 int thread_qos_scaled_relative_priority (int,int) ; 

void
thread_recompute_priority(
	thread_t		thread)
{
	integer_t		priority;

	if (thread->policy_reset)
		return;

	if (thread->sched_mode == TH_MODE_REALTIME) {
		sched_set_thread_base_priority(thread, BASEPRI_RTQUEUES);
		return;
	} else if (thread->effective_policy.thep_qos != THREAD_QOS_UNSPECIFIED) {
		int qos = thread->effective_policy.thep_qos;
		int qos_ui_is_urgent = thread->effective_policy.thep_qos_ui_is_urgent;
		int qos_relprio = -(thread->effective_policy.thep_qos_relprio); /* stored in task policy inverted */
		int qos_scaled_relprio;

		assert(qos >= 0 && qos < THREAD_QOS_LAST);
		assert(qos_relprio <= 0 && qos_relprio >= THREAD_QOS_MIN_TIER_IMPORTANCE);

		priority = thread_qos_policy_params.qos_pri[qos];
		qos_scaled_relprio = thread_qos_scaled_relative_priority(qos, qos_relprio);

		if (qos == THREAD_QOS_USER_INTERACTIVE && qos_ui_is_urgent == 1) {
			/* Bump priority 46 to 47 when in a frontmost app */
			qos_scaled_relprio += 1;
		}

		/* TODO: factor in renice priority here? */

		priority += qos_scaled_relprio;
	} else {
		if (thread->importance > MAXPRI)
			priority = MAXPRI;
		else if (thread->importance < -MAXPRI)
			priority = -MAXPRI;
		else
			priority = thread->importance;

		priority += thread->task_priority;
	}

	priority = MAX(priority, thread->user_promotion_basepri);

	/*
	 * Clamp priority back into the allowed range for this task.
	 *  The initial priority value could be out of this range due to:
	 *      Task clamped to BG or Utility (max-pri is 4, or 20)
	 *      Task is user task (max-pri is 63)
	 *      Task is kernel task (max-pri is 95)
	 * Note that thread->importance is user-settable to any integer
	 * via THREAD_PRECEDENCE_POLICY.
	 */
	if (priority > thread->max_priority)
		priority = thread->max_priority;
	else if (priority < MINPRI)
		priority = MINPRI;

	if (thread->saved_mode == TH_MODE_REALTIME &&
	    thread->sched_flags & TH_SFLAG_FAILSAFE)
		priority = DEPRESSPRI;

	if (thread->effective_policy.thep_terminated == TRUE) {
		/*
		 * We temporarily want to override the expected priority to
		 * ensure that the thread exits in a timely manner.
		 * Note that this is allowed to exceed thread->max_priority
		 * so that the thread is no longer clamped to background
		 * during the final exit phase.
		 */
		if (priority < thread->task_priority)
			priority = thread->task_priority;
		if (priority < BASEPRI_DEFAULT)
			priority = BASEPRI_DEFAULT;
	}

#if CONFIG_EMBEDDED
	/* No one can have a base priority less than MAXPRI_THROTTLE */
	if (priority < MAXPRI_THROTTLE)
		priority = MAXPRI_THROTTLE;
#endif /* CONFIG_EMBEDDED */

	sched_set_thread_base_priority(thread, priority);
}