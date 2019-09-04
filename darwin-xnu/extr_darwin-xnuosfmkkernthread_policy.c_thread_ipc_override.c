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
typedef  scalar_t__ uint32_t ;
typedef  TYPE_2__* thread_t ;
struct task_pend_token {scalar_t__ tpt_update_sockets; } ;
typedef  int /*<<< orphan*/  spl_t ;
typedef  int boolean_t ;
struct TYPE_8__ {scalar_t__ thrp_qos_ipc_override; } ;
struct TYPE_9__ {int ipc_overrides; TYPE_1__ requested_policy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_POLICY_ATTRIBUTE ; 
 int /*<<< orphan*/  TASK_POLICY_QOS_IPC_OVERRIDE ; 
 scalar_t__ THREAD_QOS_LAST ; 
 scalar_t__ THREAD_QOS_UNSPECIFIED ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  proc_set_thread_policy_spinlocked (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,struct task_pend_token*) ; 
 int /*<<< orphan*/  splsched () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  thread_policy_update_complete_unlocked (TYPE_2__*,struct task_pend_token*) ; 
 int /*<<< orphan*/  thread_unlock (TYPE_2__*) ; 

__attribute__((used)) static void
thread_ipc_override(thread_t    thread,
                    uint32_t    qos_override,
                    boolean_t   is_new_override)
{
	struct task_pend_token pend_token = {};
	boolean_t needs_update;

	spl_t s = splsched();
	thread_lock(thread);

	uint32_t old_override = thread->requested_policy.thrp_qos_ipc_override;

	assert(qos_override > THREAD_QOS_UNSPECIFIED);
	assert(qos_override < THREAD_QOS_LAST);

	if (is_new_override) {
		if (thread->ipc_overrides++ == 0) {
			/* This add is the first override for this thread */
			assert(old_override == THREAD_QOS_UNSPECIFIED);
		} else {
			/* There are already other overrides in effect for this thread */
			assert(old_override > THREAD_QOS_UNSPECIFIED);
		}
	} else {
		/* There must be at least one override (the previous add call) in effect */
		assert(thread->ipc_overrides > 0);
		assert(old_override > THREAD_QOS_UNSPECIFIED);
	}

	/*
	 * We can't allow lowering if there are several IPC overrides because
	 * the caller can't possibly know the whole truth
	 */
	if (thread->ipc_overrides == 1) {
		needs_update = qos_override != old_override;
	} else {
		needs_update = qos_override > old_override;
	}

	if (needs_update) {
		proc_set_thread_policy_spinlocked(thread, TASK_POLICY_ATTRIBUTE,
		                                  TASK_POLICY_QOS_IPC_OVERRIDE,
		                                  qos_override, 0, &pend_token);
		assert(pend_token.tpt_update_sockets == 0);
	}

	thread_unlock(thread);
	splx(s);

	thread_policy_update_complete_unlocked(thread, &pend_token);
}