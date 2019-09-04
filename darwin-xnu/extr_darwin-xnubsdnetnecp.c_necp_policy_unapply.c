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
struct necp_session_policy {scalar_t__ applied_route_rules_id; scalar_t__* kernel_socket_policies; scalar_t__* kernel_ip_output_policies; int applied; int /*<<< orphan*/ * applied_account; int /*<<< orphan*/  applied_result_uuid; int /*<<< orphan*/  applied_real_app_uuid; int /*<<< orphan*/  applied_app_uuid; } ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_RW_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_RW_ASSERT_EXCLUSIVE ; 
 int MAX_KERNEL_IP_OUTPUT_POLICIES ; 
 int MAX_KERNEL_SOCKET_POLICIES ; 
 int /*<<< orphan*/  M_NECP ; 
 int TRUE ; 
 int /*<<< orphan*/  necp_account_id_list ; 
 int /*<<< orphan*/  necp_kernel_ip_output_policy_delete (scalar_t__) ; 
 int /*<<< orphan*/  necp_kernel_policy_lock ; 
 int /*<<< orphan*/  necp_kernel_socket_policy_delete (scalar_t__) ; 
 int /*<<< orphan*/  necp_num_uuid_app_id_mappings ; 
 int /*<<< orphan*/  necp_remove_route_rule (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  necp_remove_string_to_id_mapping (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ necp_remove_uuid_app_id_mapping (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  necp_remove_uuid_service_id_mapping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  necp_route_rules ; 
 int necp_uuid_app_id_mappings_dirty ; 
 int /*<<< orphan*/  uuid_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uuid_is_null (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
necp_policy_unapply(struct necp_session_policy *policy)
{
	int i = 0;
	if (policy == NULL) {
		return (FALSE);
	}

	LCK_RW_ASSERT(&necp_kernel_policy_lock, LCK_RW_ASSERT_EXCLUSIVE);

	// Release local uuid mappings
	if (!uuid_is_null(policy->applied_app_uuid)) {
		bool removed_mapping = FALSE;
		if (necp_remove_uuid_app_id_mapping(policy->applied_app_uuid, &removed_mapping, TRUE) && removed_mapping) {
			necp_uuid_app_id_mappings_dirty = TRUE;
			necp_num_uuid_app_id_mappings--;
		}
		uuid_clear(policy->applied_app_uuid);
	}
	if (!uuid_is_null(policy->applied_real_app_uuid)) {
		necp_remove_uuid_app_id_mapping(policy->applied_real_app_uuid, NULL, FALSE);
		uuid_clear(policy->applied_real_app_uuid);
	}
	if (!uuid_is_null(policy->applied_result_uuid)) {
		necp_remove_uuid_service_id_mapping(policy->applied_result_uuid);
		uuid_clear(policy->applied_result_uuid);
	}

	// Release string mappings
	if (policy->applied_account != NULL) {
		necp_remove_string_to_id_mapping(&necp_account_id_list, policy->applied_account);
		FREE(policy->applied_account, M_NECP);
		policy->applied_account = NULL;
	}

	// Release route rule
	if (policy->applied_route_rules_id != 0) {
		necp_remove_route_rule(&necp_route_rules, policy->applied_route_rules_id);
		policy->applied_route_rules_id = 0;
	}

	// Remove socket policies
	for (i = 0; i < MAX_KERNEL_SOCKET_POLICIES; i++) {
		if (policy->kernel_socket_policies[i] != 0) {
			necp_kernel_socket_policy_delete(policy->kernel_socket_policies[i]);
			policy->kernel_socket_policies[i] = 0;
		}
	}

	// Remove IP output policies
	for (i = 0; i < MAX_KERNEL_IP_OUTPUT_POLICIES; i++) {
		if (policy->kernel_ip_output_policies[i] != 0) {
			necp_kernel_ip_output_policy_delete(policy->kernel_ip_output_policies[i]);
			policy->kernel_ip_output_policies[i] = 0;
		}
	}

	policy->applied = FALSE;

	return (TRUE);
}