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
struct necp_kernel_ip_output_policy {scalar_t__ result; scalar_t__ session_order; scalar_t__ order; TYPE_1__ result_parameter; } ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ NECP_KERNEL_POLICY_RESULT_SKIP ; 
 int TRUE ; 

__attribute__((used)) static inline bool
necp_kernel_ip_output_policy_results_overlap(struct necp_kernel_ip_output_policy *upper_policy, struct necp_kernel_ip_output_policy *lower_policy)
{
	if (upper_policy->result == NECP_KERNEL_POLICY_RESULT_SKIP) {
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

	// All other IP Output policy results (drop, tunnel, hard pass) currently overlap
	return (TRUE);
}