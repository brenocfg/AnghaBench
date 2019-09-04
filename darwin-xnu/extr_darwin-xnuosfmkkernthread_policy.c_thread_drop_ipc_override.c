#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
struct task_pend_token {int dummy; } ;
typedef  int /*<<< orphan*/  spl_t ;
struct TYPE_7__ {scalar_t__ ipc_overrides; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_POLICY_ATTRIBUTE ; 
 int /*<<< orphan*/  TASK_POLICY_QOS_IPC_OVERRIDE ; 
 int /*<<< orphan*/  THREAD_QOS_UNSPECIFIED ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  proc_set_thread_policy_spinlocked (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct task_pend_token*) ; 
 int /*<<< orphan*/  splsched () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_policy_update_complete_unlocked (TYPE_1__*,struct task_pend_token*) ; 
 int /*<<< orphan*/  thread_unlock (TYPE_1__*) ; 

void
thread_drop_ipc_override(thread_t thread)
{
	struct task_pend_token pend_token = {};

	spl_t s = splsched();
	thread_lock(thread);

	assert(thread->ipc_overrides > 0);

	if (--thread->ipc_overrides == 0) {
		/*
		 * There are no more overrides for this thread, so we should
		 * clear out the saturated override value
		 */

		proc_set_thread_policy_spinlocked(thread, TASK_POLICY_ATTRIBUTE,
		                                  TASK_POLICY_QOS_IPC_OVERRIDE, THREAD_QOS_UNSPECIFIED,
		                                  0, &pend_token);
	}

	thread_unlock(thread);
	splx(s);

	thread_policy_update_complete_unlocked(thread, &pend_token);
}