#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* thread_t ;
struct task_pend_token {int dummy; } ;
typedef  int /*<<< orphan*/  sched_mode_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  integer_t ;
struct TYPE_10__ {scalar_t__ thrp_qos; } ;
struct TYPE_11__ {TYPE_1__ requested_policy; int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_POLICY_STATIC ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  KERN_TERMINATED ; 
 scalar_t__ THREAD_QOS_UNSPECIFIED ; 
 int /*<<< orphan*/  convert_policy_to_sched_mode (int /*<<< orphan*/ ) ; 
 scalar_t__ thread_is_static_param (TYPE_2__*) ; 
 int /*<<< orphan*/  thread_mtx_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  thread_mtx_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  thread_policy_update_complete_unlocked (TYPE_2__*,struct task_pend_token*) ; 
 int /*<<< orphan*/  thread_remove_qos_policy_locked (TYPE_2__*,struct task_pend_token*) ; 
 int /*<<< orphan*/  thread_set_mode_and_absolute_pri_internal (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct task_pend_token*) ; 

kern_return_t
thread_set_mode_and_absolute_pri(thread_t   thread,
                                 integer_t  policy,
                                 integer_t  priority)
{
	kern_return_t kr = KERN_SUCCESS;
	struct task_pend_token pend_token = {};

	sched_mode_t mode = convert_policy_to_sched_mode(policy);

	thread_mtx_lock(thread);

	if (!thread->active) {
		kr = KERN_TERMINATED;
		goto unlock;
	}

	if (thread_is_static_param(thread)) {
		kr = KERN_POLICY_STATIC;
		goto unlock;
	}

	/* Setting legacy policies on threads kills the current QoS */
	if (thread->requested_policy.thrp_qos != THREAD_QOS_UNSPECIFIED)
		thread_remove_qos_policy_locked(thread, &pend_token);

	kr = thread_set_mode_and_absolute_pri_internal(thread, mode, priority, &pend_token);

unlock:
	thread_mtx_unlock(thread);

	thread_policy_update_complete_unlocked(thread, &pend_token);

	return (kr);
}