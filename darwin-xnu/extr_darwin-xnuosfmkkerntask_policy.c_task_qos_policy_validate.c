#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  task_throughput_qos_t ;
typedef  TYPE_1__* task_qos_policy_t ;
typedef  int /*<<< orphan*/  task_latency_qos_t ;
typedef  scalar_t__ mach_msg_type_number_t ;
typedef  scalar_t__ kern_return_t ;
struct TYPE_3__ {int /*<<< orphan*/  task_throughput_qos_tier; int /*<<< orphan*/  task_latency_qos_tier; } ;

/* Variables and functions */
 scalar_t__ KERN_INVALID_ARGUMENT ; 
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ TASK_QOS_POLICY_COUNT ; 
 scalar_t__ qos_latency_policy_validate (int /*<<< orphan*/ ) ; 
 scalar_t__ qos_throughput_policy_validate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static kern_return_t
task_qos_policy_validate(task_qos_policy_t qosinfo, mach_msg_type_number_t count) {
	if (count < TASK_QOS_POLICY_COUNT)
		return KERN_INVALID_ARGUMENT;

	task_latency_qos_t ltier = qosinfo->task_latency_qos_tier;
	task_throughput_qos_t ttier = qosinfo->task_throughput_qos_tier;

	kern_return_t kr = qos_latency_policy_validate(ltier);

	if (kr != KERN_SUCCESS)
		return kr;

	kr = qos_throughput_policy_validate(ttier);

	return kr;
}