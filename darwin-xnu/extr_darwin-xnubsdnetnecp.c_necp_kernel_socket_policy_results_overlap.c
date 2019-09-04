#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ skip_policy_order; } ;
struct necp_kernel_socket_policy {scalar_t__ result; scalar_t__ session_order; scalar_t__ order; TYPE_1__ result_parameter; } ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ NECP_KERNEL_POLICY_RESULT_DROP ; 
 scalar_t__ NECP_KERNEL_POLICY_RESULT_NETAGENT_SCOPED ; 
 scalar_t__ NECP_KERNEL_POLICY_RESULT_ROUTE_RULES ; 
 scalar_t__ NECP_KERNEL_POLICY_RESULT_SKIP ; 
 scalar_t__ NECP_KERNEL_POLICY_RESULT_SOCKET_FILTER ; 
 scalar_t__ NECP_KERNEL_POLICY_RESULT_USE_NETAGENT ; 
 int TRUE ; 
 int necp_kernel_socket_result_is_trigger_service_type (struct necp_kernel_socket_policy*) ; 

__attribute__((used)) static inline bool
necp_kernel_socket_policy_results_overlap(struct necp_kernel_socket_policy *upper_policy, struct necp_kernel_socket_policy *lower_policy)
{
	if (upper_policy->result == NECP_KERNEL_POLICY_RESULT_DROP) {
		// Drop always cancels out lower policies
		return (TRUE);
	} else if (upper_policy->result == NECP_KERNEL_POLICY_RESULT_SOCKET_FILTER ||
			   upper_policy->result == NECP_KERNEL_POLICY_RESULT_ROUTE_RULES ||
			   upper_policy->result == NECP_KERNEL_POLICY_RESULT_USE_NETAGENT ||
			   upper_policy->result == NECP_KERNEL_POLICY_RESULT_NETAGENT_SCOPED) {
		// Filters and route rules never cancel out lower policies
		return (FALSE);
	} else if (necp_kernel_socket_result_is_trigger_service_type(upper_policy)) {
		// Trigger/Scoping policies can overlap one another, but not other results
		return (necp_kernel_socket_result_is_trigger_service_type(lower_policy));
	} else if (upper_policy->result == NECP_KERNEL_POLICY_RESULT_SKIP) {
		if (upper_policy->session_order != lower_policy->session_order) {
			// A skip cannot override a policy of a different session
			return (FALSE);
		} else {
			if (upper_policy->result_parameter.skip_policy_order == 0 ||
				lower_policy->order >= upper_policy->result_parameter.skip_policy_order) {
				// This policy is beyond the skip
				return (FALSE);
			} else {
				// This policy is inside the skip
				return (TRUE);
			}
		}
	}

	// A hard pass, flow divert, tunnel, or scope will currently block out lower policies
	return (TRUE);
}