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
typedef  int /*<<< orphan*/  thread_qos_t ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_POLICY_ATTRIBUTE ; 
 int /*<<< orphan*/  TASK_POLICY_QOS_AND_RELPRIO ; 
 int /*<<< orphan*/  proc_get_thread_policy_locked (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

thread_qos_t
thread_get_requested_qos(thread_t thread, int *relpri)
{
	int relprio_value = 0;
	thread_qos_t qos;

	qos = proc_get_thread_policy_locked(thread, TASK_POLICY_ATTRIBUTE,
			TASK_POLICY_QOS_AND_RELPRIO, &relprio_value);
	if (relpri) *relpri = -relprio_value;
	return qos;
}