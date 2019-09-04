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
typedef  int /*<<< orphan*/  thread_t ;
struct uthread {int /*<<< orphan*/  uu_thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_POLICY_ATTRIBUTE ; 
 int /*<<< orphan*/  TASK_POLICY_QOS ; 
 int THREAD_QOS_UNSPECIFIED ; 
 int THREAD_QOS_USER_INTERACTIVE ; 
 int /*<<< orphan*/  current_thread () ; 
 int proc_get_thread_policy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int proc_usynch_get_requested_thread_qos(struct uthread *uth)
{
	thread_t	thread = uth ? uth->uu_thread : current_thread();
	int			requested_qos;

	requested_qos = proc_get_thread_policy(thread, TASK_POLICY_ATTRIBUTE, TASK_POLICY_QOS);

	/*
	 * For the purposes of userspace synchronization, it doesn't make sense to
	 * place an override of UNSPECIFIED on another thread, if the current thread
	 * doesn't have any QoS set. In these cases, upgrade to
	 * THREAD_QOS_USER_INTERACTIVE.
	 */
	if (requested_qos == THREAD_QOS_UNSPECIFIED) {
		requested_qos = THREAD_QOS_USER_INTERACTIVE;
	}

	return requested_qos;
}