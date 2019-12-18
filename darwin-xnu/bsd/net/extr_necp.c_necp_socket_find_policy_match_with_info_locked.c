#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  scalar_t__ u_int32_t ;
struct substring {int /*<<< orphan*/  length; int /*<<< orphan*/  string; } ;
struct necp_socket_info {int /*<<< orphan*/  protocol; int /*<<< orphan*/  bound_interface_index; int /*<<< orphan*/  real_application_id; int /*<<< orphan*/  application_id; int /*<<< orphan*/  remote_addr; int /*<<< orphan*/  local_addr; int /*<<< orphan*/  traffic_class; int /*<<< orphan*/  uid; int /*<<< orphan*/  pid; int /*<<< orphan*/  account_id; int /*<<< orphan*/  cred_result; scalar_t__ domain; } ;
struct TYPE_5__ {char* identifier; scalar_t__ data; } ;
struct TYPE_6__ {scalar_t__ route_rule_id; scalar_t__ netagent_id; scalar_t__ skip_policy_order; TYPE_1__ service; int /*<<< orphan*/  filter_control_unit; } ;
struct necp_kernel_socket_policy {scalar_t__ session_order; scalar_t__ order; scalar_t__ result; int /*<<< orphan*/  id; TYPE_2__ result_parameter; } ;
struct necp_client_parameter_netagent_type {int dummy; } ;
typedef  int /*<<< orphan*/  proc_t ;
struct TYPE_7__ {char* identifier; scalar_t__ data; } ;
typedef  TYPE_3__ necp_kernel_policy_service ;
typedef  scalar_t__ necp_kernel_policy_result ;
typedef  int /*<<< orphan*/  necp_kernel_policy_id ;
typedef  int /*<<< orphan*/  necp_kernel_policy_filter ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG ; 
 int MAX_AGGREGATE_ROUTE_RULES ; 
 int /*<<< orphan*/  NECPLOG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ NECP_AGENT_USE_FLAG_SCOPE ; 
 scalar_t__ NECP_KERNEL_POLICY_RESULT_NETAGENT_SCOPED ; 
 scalar_t__ NECP_KERNEL_POLICY_RESULT_ROUTE_RULES ; 
 scalar_t__ NECP_KERNEL_POLICY_RESULT_SKIP ; 
 scalar_t__ NECP_KERNEL_POLICY_RESULT_SOCKET_FILTER ; 
 scalar_t__ NECP_KERNEL_POLICY_RESULT_USE_NETAGENT ; 
 int /*<<< orphan*/  necp_count_dots (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ necp_create_aggregate_route_rule (scalar_t__*) ; 
 int necp_debug ; 
 scalar_t__ necp_drop_all_order ; 
 scalar_t__ necp_kernel_socket_result_is_trigger_service_type (struct necp_kernel_socket_policy*) ; 
 scalar_t__ necp_socket_check_policy (struct necp_kernel_socket_policy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct substring,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct necp_client_parameter_netagent_type*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct substring necp_trim_dots_and_stars (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (scalar_t__) ; 

__attribute__((used)) static inline struct necp_kernel_socket_policy *
necp_socket_find_policy_match_with_info_locked(struct necp_kernel_socket_policy **policy_search_array, struct necp_socket_info *info,
											   necp_kernel_policy_filter *return_filter, u_int32_t *return_route_rule_id,
											   necp_kernel_policy_result *return_service_action, necp_kernel_policy_service *return_service,
											   u_int32_t *return_netagent_array, u_int32_t *return_netagent_use_flags_array, size_t netagent_array_count,
											   struct necp_client_parameter_netagent_type *required_agent_types,
											   u_int32_t num_required_agent_types, proc_t proc, necp_kernel_policy_id *skip_policy_id)
{
	struct necp_kernel_socket_policy *matched_policy = NULL;
	u_int32_t skip_order = 0;
	u_int32_t skip_session_order = 0;
	u_int32_t route_rule_id_array[MAX_AGGREGATE_ROUTE_RULES];
	size_t route_rule_id_count = 0;
	int i;
	size_t netagent_cursor = 0;

	// Pre-process domain for quick matching
	struct substring domain_substring = necp_trim_dots_and_stars(info->domain, info->domain ? strlen(info->domain) : 0);
	u_int8_t domain_dot_count = necp_count_dots(domain_substring.string, domain_substring.length);

	if (return_filter) {
		*return_filter = 0;
	}

	if (return_route_rule_id) {
		*return_route_rule_id = 0;
	}

	if (return_service_action) {
		*return_service_action = 0;
	}

	if (return_service) {
		return_service->identifier = 0;
		return_service->data = 0;
	}

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
			if (necp_socket_check_policy(policy_search_array[i], info->application_id, info->real_application_id, info->cred_result, info->account_id, domain_substring, domain_dot_count, info->pid, info->uid, info->bound_interface_index, info->traffic_class, info->protocol, &info->local_addr, &info->remote_addr, required_agent_types, num_required_agent_types, proc)) {
				if (policy_search_array[i]->result == NECP_KERNEL_POLICY_RESULT_SOCKET_FILTER) {
					if (return_filter && *return_filter == 0) {
						*return_filter = policy_search_array[i]->result_parameter.filter_control_unit;
						if (necp_debug > 1) {
							NECPLOG(LOG_DEBUG, "Socket Policy: (Application %d Real Application %d BoundInterface %d Proto %d) Filter %d", info->application_id, info->real_application_id, info->bound_interface_index, info->protocol, policy_search_array[i]->result_parameter.filter_control_unit);
						}
					}
					continue;
				} else if (policy_search_array[i]->result == NECP_KERNEL_POLICY_RESULT_ROUTE_RULES) {
					if (return_route_rule_id && route_rule_id_count < MAX_AGGREGATE_ROUTE_RULES) {
						route_rule_id_array[route_rule_id_count++] = policy_search_array[i]->result_parameter.route_rule_id;
						if (necp_debug > 1) {
							NECPLOG(LOG_DEBUG, "Socket Policy: (Application %d Real Application %d BoundInterface %d Proto %d) Route Rule %d", info->application_id, info->real_application_id, info->bound_interface_index, info->protocol, policy_search_array[i]->result_parameter.route_rule_id);
						}
					}
					continue;
				} else if (necp_kernel_socket_result_is_trigger_service_type(policy_search_array[i])) {
					if (return_service_action && *return_service_action == 0) {
						*return_service_action = policy_search_array[i]->result;
						if (necp_debug > 1) {
							NECPLOG(LOG_DEBUG, "Socket Policy: (Application %d Real Application %d BoundInterface %d Proto %d) Service Action %d", info->application_id, info->real_application_id, info->bound_interface_index, info->protocol, policy_search_array[i]->result);
						}
					}
					if (return_service && return_service->identifier == 0) {
						return_service->identifier = policy_search_array[i]->result_parameter.service.identifier;
						return_service->data = policy_search_array[i]->result_parameter.service.data;
						if (necp_debug > 1) {
							NECPLOG(LOG_DEBUG, "Socket Policy: (Application %d Real Application %d BoundInterface %d Proto %d) Service ID %d Data %d", info->application_id, info->real_application_id, info->bound_interface_index, info->protocol, policy_search_array[i]->result_parameter.service.identifier, policy_search_array[i]->result_parameter.service.data);
						}
					}
					continue;
				} else if (policy_search_array[i]->result == NECP_KERNEL_POLICY_RESULT_USE_NETAGENT ||
						   policy_search_array[i]->result == NECP_KERNEL_POLICY_RESULT_NETAGENT_SCOPED) {
					if (return_netagent_array != NULL &&
						netagent_cursor < netagent_array_count) {
						return_netagent_array[netagent_cursor] = policy_search_array[i]->result_parameter.netagent_id;
						if (return_netagent_use_flags_array != NULL &&
							policy_search_array[i]->result == NECP_KERNEL_POLICY_RESULT_NETAGENT_SCOPED) {
							return_netagent_use_flags_array[netagent_cursor] |= NECP_AGENT_USE_FLAG_SCOPE;
						}
						netagent_cursor++;
						if (necp_debug > 1) {
							NECPLOG(LOG_DEBUG, "Socket Policy: (Application %d Real Application %d BoundInterface %d Proto %d) %s Netagent %d",
									info->application_id, info->real_application_id, info->bound_interface_index, info->protocol,
									policy_search_array[i]->result == NECP_KERNEL_POLICY_RESULT_USE_NETAGENT ? "Use" : "Scope",
									policy_search_array[i]->result_parameter.netagent_id);
						}
					}
					continue;
				}

				// Matched policy is a skip. Do skip and continue.
				if (policy_search_array[i]->result == NECP_KERNEL_POLICY_RESULT_SKIP) {
					skip_order = policy_search_array[i]->result_parameter.skip_policy_order;
					skip_session_order = policy_search_array[i]->session_order + 1;
					if (skip_policy_id) {
						*skip_policy_id = policy_search_array[i]->id;
					}
					continue;
				}

				// Passed all tests, found a match
				matched_policy = policy_search_array[i];
				break;
			}
		}
	}

	if (route_rule_id_count == 1) {
		*return_route_rule_id = route_rule_id_array[0];
	} else if (route_rule_id_count > 1) {
		*return_route_rule_id = necp_create_aggregate_route_rule(route_rule_id_array);
	}
	return (matched_policy);
}