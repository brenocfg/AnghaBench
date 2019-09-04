#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* thread_t ;
struct TYPE_11__ {scalar_t__ qos_tier; int /*<<< orphan*/  tier_importance; } ;
typedef  TYPE_3__ thread_qos_policy_data_t ;
typedef  int /*<<< orphan*/  thread_policy_t ;
typedef  scalar_t__ thread_policy_flavor_t ;
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  scalar_t__ kern_return_t ;
struct TYPE_9__ {scalar_t__ thrp_qos; int /*<<< orphan*/  thrp_qos_relprio; } ;
struct TYPE_10__ {TYPE_1__ requested_policy; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ KERN_INVALID_ARGUMENT ; 
 scalar_t__ KERN_POLICY_STATIC ; 
 scalar_t__ KERN_SUCCESS ; 
 TYPE_2__* THREAD_NULL ; 
 scalar_t__ THREAD_QOS_POLICY ; 
 int /*<<< orphan*/  THREAD_QOS_POLICY_COUNT ; 
 scalar_t__ THREAD_QOS_UNSPECIFIED ; 
 scalar_t__ allow_qos_policy_set ; 
 scalar_t__ thread_is_static_param (TYPE_2__*) ; 
 scalar_t__ thread_policy_set_internal (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ thread_remove_qos_policy (TYPE_2__*) ; 

kern_return_t
thread_policy_set(
	thread_t				thread,
	thread_policy_flavor_t	flavor,
	thread_policy_t			policy_info,
	mach_msg_type_number_t	count)
{
	thread_qos_policy_data_t req_qos;
	kern_return_t kr;
	
	req_qos.qos_tier = THREAD_QOS_UNSPECIFIED;

	if (thread == THREAD_NULL)
		return (KERN_INVALID_ARGUMENT);

	if (allow_qos_policy_set == FALSE) {
		if (thread_is_static_param(thread))
			return (KERN_POLICY_STATIC);

		if (flavor == THREAD_QOS_POLICY)
			return (KERN_INVALID_ARGUMENT);
	}

	/* Threads without static_param set reset their QoS when other policies are applied. */
	if (thread->requested_policy.thrp_qos != THREAD_QOS_UNSPECIFIED) {
		/* Store the existing tier, if we fail this call it is used to reset back. */
		req_qos.qos_tier = thread->requested_policy.thrp_qos;
		req_qos.tier_importance = thread->requested_policy.thrp_qos_relprio;

		kr = thread_remove_qos_policy(thread);
		if (kr != KERN_SUCCESS) {
			return kr;
		}
	}

	kr = thread_policy_set_internal(thread, flavor, policy_info, count);

	/* Return KERN_QOS_REMOVED instead of KERN_SUCCESS if we succeeded. */
	if (req_qos.qos_tier != THREAD_QOS_UNSPECIFIED) {
		if (kr != KERN_SUCCESS) {
			/* Reset back to our original tier as the set failed. */
			(void)thread_policy_set_internal(thread, THREAD_QOS_POLICY, (thread_policy_t)&req_qos, THREAD_QOS_POLICY_COUNT);
		}
	}

	return kr;
}