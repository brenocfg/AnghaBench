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
typedef  union necp_sockaddr_union {int dummy; } necp_sockaddr_union ;
typedef  scalar_t__ u_int32_t ;
typedef  int /*<<< orphan*/  u_int16_t ;
struct TYPE_2__ {scalar_t__ skip_policy_order; } ;
struct necp_kernel_ip_output_policy {scalar_t__ session_order; scalar_t__ order; scalar_t__ result; TYPE_1__ result_parameter; } ;
typedef  int /*<<< orphan*/  necp_kernel_policy_id ;

/* Variables and functions */
 size_t NECP_IP_OUTPUT_MAP_ID_TO_BUCKET (int /*<<< orphan*/ ) ; 
 scalar_t__ NECP_KERNEL_POLICY_RESULT_SKIP ; 
 scalar_t__ necp_drop_all_order ; 
 scalar_t__ necp_ip_output_check_policy (struct necp_kernel_ip_output_policy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,union necp_sockaddr_union*,union necp_sockaddr_union*) ; 
 struct necp_kernel_ip_output_policy*** necp_kernel_ip_output_policies_map ; 

__attribute__((used)) static inline struct necp_kernel_ip_output_policy *
necp_ip_output_find_policy_match_locked(necp_kernel_policy_id socket_policy_id, necp_kernel_policy_id socket_skip_policy_id, u_int32_t bound_interface_index, u_int32_t last_interface_index, u_int16_t protocol, union necp_sockaddr_union *local_addr, union necp_sockaddr_union *remote_addr)
{
	u_int32_t skip_order = 0;
	u_int32_t skip_session_order = 0;
	int i;
	struct necp_kernel_ip_output_policy *matched_policy = NULL;
	struct necp_kernel_ip_output_policy **policy_search_array = necp_kernel_ip_output_policies_map[NECP_IP_OUTPUT_MAP_ID_TO_BUCKET(socket_policy_id)];
	if (policy_search_array != NULL) {
		for (i = 0; policy_search_array[i] != NULL; i++) {
			if (necp_drop_all_order != 0 && policy_search_array[i]->session_order >= necp_drop_all_order) {
				// We've hit a drop all rule
				break;
			}
			if (skip_session_order && policy_search_array[i]->session_order >= skip_session_order) {
				// Done skipping
				skip_order = 0;
				skip_session_order = 0;
			}
			if (skip_order) {
				if (policy_search_array[i]->order < skip_order) {
					// Skip this policy
					continue;
				} else {
					// Done skipping
					skip_order = 0;
					skip_session_order = 0;
				}
			} else if (skip_session_order) {
				// Skip this policy
				continue;
			}
			if (necp_ip_output_check_policy(policy_search_array[i], socket_policy_id, socket_skip_policy_id, bound_interface_index, last_interface_index, protocol, local_addr, remote_addr)) {
				// Passed all tests, found a match
				matched_policy = policy_search_array[i];

				if (policy_search_array[i]->result == NECP_KERNEL_POLICY_RESULT_SKIP) {
					skip_order = policy_search_array[i]->result_parameter.skip_policy_order;
					skip_session_order = policy_search_array[i]->session_order + 1;
					continue;
				}

				break;
			}
		}
	}

	return (matched_policy);
}