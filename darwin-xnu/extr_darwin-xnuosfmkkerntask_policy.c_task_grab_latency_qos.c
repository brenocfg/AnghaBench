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
typedef  int /*<<< orphan*/  task_t ;
typedef  int /*<<< orphan*/  integer_t ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_POLICY_LATENCY_QOS ; 
 int /*<<< orphan*/  proc_get_effective_task_policy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qos_latency_policy_package (int /*<<< orphan*/ ) ; 

integer_t
task_grab_latency_qos(task_t task)
{
	return qos_latency_policy_package(proc_get_effective_task_policy(task, TASK_POLICY_LATENCY_QOS));
}