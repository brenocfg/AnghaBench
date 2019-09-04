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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  thread_t ;
struct task_pend_token {scalar_t__ tpt_update_sockets; } ;
typedef  int /*<<< orphan*/  spl_t ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_POLICY_ATTRIBUTE ; 
 int /*<<< orphan*/  TASK_POLICY_QOS_AND_RELPRIO ; 
 int /*<<< orphan*/  TASK_POLICY_QOS_WORKQ_OVERRIDE ; 
 scalar_t__ THREAD_QOS_LAST ; 
 scalar_t__ THREAD_QOS_UNSPECIFIED ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  proc_set_thread_policy_spinlocked (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,struct task_pend_token*) ; 
 int /*<<< orphan*/  splsched () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_policy_update_complete_unlocked (int /*<<< orphan*/ ,struct task_pend_token*) ; 
 int /*<<< orphan*/  thread_unlock (int /*<<< orphan*/ ) ; 

void
thread_reset_workq_qos(thread_t thread, uint32_t qos)
{
	struct task_pend_token pend_token = {};

	assert(qos < THREAD_QOS_LAST);

	spl_t s = splsched();
	thread_lock(thread);

	proc_set_thread_policy_spinlocked(thread, TASK_POLICY_ATTRIBUTE,
			TASK_POLICY_QOS_AND_RELPRIO, qos, 0, &pend_token);
	proc_set_thread_policy_spinlocked(thread, TASK_POLICY_ATTRIBUTE,
			TASK_POLICY_QOS_WORKQ_OVERRIDE, THREAD_QOS_UNSPECIFIED, 0,
			&pend_token);

	assert(pend_token.tpt_update_sockets == 0);

	thread_unlock(thread);
	splx(s);

	thread_policy_update_complete_unlocked(thread, &pend_token);
}