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
typedef  int /*<<< orphan*/  thread_policy_t ;
typedef  int /*<<< orphan*/  thread_policy_flavor_t ;
typedef  int /*<<< orphan*/  thread_act_t ;
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 scalar_t__ KERN_POLICY_STATIC ; 
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ _kernelrpc_thread_policy_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _pthread_clear_qos_tsd (int /*<<< orphan*/ ) ; 

kern_return_t
thread_policy_set(thread_act_t thread, thread_policy_flavor_t flavor, thread_policy_t policy_info, mach_msg_type_number_t policy_infoCnt)
{
	kern_return_t kr;

	kr = _kernelrpc_thread_policy_set(thread, flavor, policy_info, policy_infoCnt);
	if (kr == KERN_SUCCESS) {
		_pthread_clear_qos_tsd(thread);
	} else if (kr == KERN_POLICY_STATIC) {
		kr = KERN_SUCCESS;
	}

	return kr;
}