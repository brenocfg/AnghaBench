#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
typedef  int /*<<< orphan*/  thread_qos_t ;
struct task_pend_token {int tpt_force_recompute_pri; } ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_10__ {int base_pri; int user_promotion_basepri; } ;

/* Variables and functions */
 int DBG_FUNC_NONE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KDEBUG_TRACE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT_IST (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAXPRI_THROTTLE ; 
 int /*<<< orphan*/  MAXPRI_USER ; 
 int MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_POLICY_ATTRIBUTE ; 
 int /*<<< orphan*/  TASK_POLICY_QOS_PROMOTE ; 
 int /*<<< orphan*/  THREAD_QOS_UNSPECIFIED ; 
 int /*<<< orphan*/  THREAD_USER_PROMOTION_CHANGE ; 
 int /*<<< orphan*/  TRUE ; 
 int TURNSTILE_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TURNSTILE_PRIORITY_OPERATIONS ; 
 int /*<<< orphan*/  proc_set_thread_policy_spinlocked (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct task_pend_token*) ; 
 int /*<<< orphan*/  thread_get_inheritor_turnstile_priority (TYPE_1__*) ; 
 scalar_t__ thread_get_waiting_turnstile (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_policy_update_complete_unlocked (TYPE_1__*,struct task_pend_token*) ; 
 int /*<<< orphan*/  thread_tid (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_user_promotion_qos_for_pri (int) ; 

boolean_t
thread_recompute_user_promotion_locked(thread_t thread)
{
	boolean_t needs_update = FALSE;
	struct task_pend_token pend_token = {};
	int user_promotion_basepri = MIN(thread_get_inheritor_turnstile_priority(thread), MAXPRI_USER);
	int old_base_pri = thread->base_pri;
	thread_qos_t qos_promotion;

	/* Check if user promotion has changed */
	if (thread->user_promotion_basepri == user_promotion_basepri) {
		return needs_update;
	} else {
		KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
			(TURNSTILE_CODE(TURNSTILE_PRIORITY_OPERATIONS, (THREAD_USER_PROMOTION_CHANGE))) | DBG_FUNC_NONE,
			thread_tid(thread),
			user_promotion_basepri,
			thread->user_promotion_basepri,
			0, 0);
	}

	/* Update the user promotion base pri */
	thread->user_promotion_basepri = user_promotion_basepri;
	pend_token.tpt_force_recompute_pri = 1;

	if (user_promotion_basepri <= MAXPRI_THROTTLE) {
		qos_promotion = THREAD_QOS_UNSPECIFIED;
	} else {
		qos_promotion = thread_user_promotion_qos_for_pri(user_promotion_basepri);
	}

	proc_set_thread_policy_spinlocked(thread, TASK_POLICY_ATTRIBUTE,
			TASK_POLICY_QOS_PROMOTE, qos_promotion, 0, &pend_token);

	if (thread_get_waiting_turnstile(thread) &&
	    thread->base_pri != old_base_pri) {
		needs_update = TRUE;
	}

	thread_unlock(thread);

	thread_policy_update_complete_unlocked(thread, &pend_token);

	thread_lock(thread);

	return needs_update;
}