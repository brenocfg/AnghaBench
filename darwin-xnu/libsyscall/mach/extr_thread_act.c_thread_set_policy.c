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
typedef  int /*<<< orphan*/  thread_act_t ;
typedef  int /*<<< orphan*/  processor_set_t ;
typedef  int /*<<< orphan*/  policy_t ;
typedef  int /*<<< orphan*/  policy_limit_t ;
typedef  int /*<<< orphan*/  policy_base_t ;
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 scalar_t__ KERN_POLICY_STATIC ; 
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ _kernelrpc_thread_set_policy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _pthread_clear_qos_tsd (int /*<<< orphan*/ ) ; 

kern_return_t
thread_set_policy(thread_act_t thr_act, processor_set_t pset, policy_t policy, policy_base_t base, mach_msg_type_number_t baseCnt, policy_limit_t limit, mach_msg_type_number_t limitCnt)
{
	kern_return_t kr;

	kr = _kernelrpc_thread_set_policy(thr_act, pset, policy, base, baseCnt, limit, limitCnt);
	if (kr == KERN_SUCCESS) {
		_pthread_clear_qos_tsd(thr_act);
	} else if (kr == KERN_POLICY_STATIC) {
		kr = KERN_SUCCESS;
	}

	return kr;
}