#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uuid_t ;
typedef  int /*<<< orphan*/  uid_t ;
typedef  scalar_t__ u_int8_t ;
typedef  int u_int32_t ;
typedef  int /*<<< orphan*/  u_int16_t ;
struct necp_policy_condition_tc_range {int dummy; } ;
struct necp_policy_condition_agent_type {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  sa; } ;
struct TYPE_5__ {int /*<<< orphan*/  sa; } ;
struct necp_policy_condition_addr_range {TYPE_3__ end_address; TYPE_2__ start_address; } ;
struct TYPE_4__ {int /*<<< orphan*/  sa; } ;
struct necp_policy_condition_addr {TYPE_1__ address; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  NECPLOG (int /*<<< orphan*/ ,char*,scalar_t__,int) ; 
#define  NECP_POLICY_CONDITION_ACCOUNT 144 
#define  NECP_POLICY_CONDITION_AGENT_TYPE 143 
#define  NECP_POLICY_CONDITION_ALL_INTERFACES 142 
#define  NECP_POLICY_CONDITION_APPLICATION 141 
#define  NECP_POLICY_CONDITION_BOUND_INTERFACE 140 
#define  NECP_POLICY_CONDITION_DEFAULT 139 
#define  NECP_POLICY_CONDITION_DOMAIN 138 
#define  NECP_POLICY_CONDITION_ENTITLEMENT 137 
 scalar_t__ NECP_POLICY_CONDITION_FLAGS_NEGATIVE ; 
#define  NECP_POLICY_CONDITION_IP_PROTOCOL 136 
#define  NECP_POLICY_CONDITION_LOCAL_ADDR 135 
#define  NECP_POLICY_CONDITION_LOCAL_ADDR_RANGE 134 
#define  NECP_POLICY_CONDITION_PID 133 
#define  NECP_POLICY_CONDITION_REAL_APPLICATION 132 
#define  NECP_POLICY_CONDITION_REMOTE_ADDR 131 
#define  NECP_POLICY_CONDITION_REMOTE_ADDR_RANGE 130 
#define  NECP_POLICY_CONDITION_TRAFFIC_CLASS 129 
#define  NECP_POLICY_CONDITION_UID 128 
 scalar_t__ NECP_POLICY_RESULT_NETAGENT_SCOPED ; 
 scalar_t__ NECP_POLICY_RESULT_NO_TRIGGER_SCOPED ; 
 scalar_t__ NECP_POLICY_RESULT_ROUTE_RULES ; 
 scalar_t__ NECP_POLICY_RESULT_SCOPED_DIRECT ; 
 scalar_t__ NECP_POLICY_RESULT_SOCKET_DIVERT ; 
 scalar_t__ NECP_POLICY_RESULT_SOCKET_FILTER ; 
 scalar_t__ NECP_POLICY_RESULT_SOCKET_SCOPED ; 
 scalar_t__ NECP_POLICY_RESULT_TRIGGER ; 
 scalar_t__ NECP_POLICY_RESULT_TRIGGER_IF_NEEDED ; 
 scalar_t__ NECP_POLICY_RESULT_TRIGGER_SCOPED ; 
 scalar_t__ NECP_POLICY_RESULT_USE_NETAGENT ; 
 int TRUE ; 
 int /*<<< orphan*/  necp_address_is_valid (int /*<<< orphan*/ *) ; 
 scalar_t__ necp_debug ; 
 scalar_t__ necp_policy_condition_get_flags_from_buffer (scalar_t__*,int) ; 
 scalar_t__ necp_policy_condition_get_type_from_buffer (scalar_t__*,int) ; 
 int necp_policy_condition_get_value_length_from_buffer (scalar_t__*,int) ; 
 scalar_t__* necp_policy_condition_get_value_pointer_from_buffer (scalar_t__*,int) ; 
 int /*<<< orphan*/  uuid_is_null (scalar_t__*) ; 

__attribute__((used)) static bool
necp_policy_condition_is_valid(u_int8_t *buffer, u_int32_t length, u_int8_t policy_result_type)
{
	bool validated = FALSE;
	bool result_cannot_have_ip_layer = (policy_result_type == NECP_POLICY_RESULT_SOCKET_DIVERT ||
										policy_result_type == NECP_POLICY_RESULT_SOCKET_FILTER ||
										policy_result_type == NECP_POLICY_RESULT_TRIGGER ||
										policy_result_type == NECP_POLICY_RESULT_TRIGGER_IF_NEEDED ||
										policy_result_type == NECP_POLICY_RESULT_TRIGGER_SCOPED ||
										policy_result_type == NECP_POLICY_RESULT_NO_TRIGGER_SCOPED ||
										policy_result_type == NECP_POLICY_RESULT_SOCKET_SCOPED ||
										policy_result_type == NECP_POLICY_RESULT_ROUTE_RULES ||
										policy_result_type == NECP_POLICY_RESULT_USE_NETAGENT ||
										policy_result_type == NECP_POLICY_RESULT_NETAGENT_SCOPED ||
										policy_result_type == NECP_POLICY_RESULT_SCOPED_DIRECT) ? TRUE : FALSE;
	u_int32_t condition_length = necp_policy_condition_get_value_length_from_buffer(buffer, length);
	u_int8_t *condition_value = necp_policy_condition_get_value_pointer_from_buffer(buffer, length);
	u_int8_t type = necp_policy_condition_get_type_from_buffer(buffer, length);
	u_int8_t flags = necp_policy_condition_get_flags_from_buffer(buffer, length);
	switch (type) {
		case NECP_POLICY_CONDITION_APPLICATION:
		case NECP_POLICY_CONDITION_REAL_APPLICATION: {
			if (!(flags & NECP_POLICY_CONDITION_FLAGS_NEGATIVE) &&
				condition_length >= sizeof(uuid_t) &&
				condition_value != NULL &&
				!uuid_is_null(condition_value)) {
				validated = TRUE;
			}
			break;
		}
		case NECP_POLICY_CONDITION_DOMAIN:
		case NECP_POLICY_CONDITION_ACCOUNT:
		case NECP_POLICY_CONDITION_BOUND_INTERFACE: {
			if (condition_length > 0) {
				validated = TRUE;
			}
			break;
		}
		case NECP_POLICY_CONDITION_TRAFFIC_CLASS: {
			if (condition_length >= sizeof(struct necp_policy_condition_tc_range)) {
				validated = TRUE;
			}
			break;
		}
		case NECP_POLICY_CONDITION_DEFAULT:
		case NECP_POLICY_CONDITION_ALL_INTERFACES:
		case NECP_POLICY_CONDITION_ENTITLEMENT: {
			if (!(flags & NECP_POLICY_CONDITION_FLAGS_NEGATIVE)) {
				validated = TRUE;
			}
			break;
		}
		case NECP_POLICY_CONDITION_IP_PROTOCOL: {
			if (condition_length >= sizeof(u_int16_t)) {
				validated = TRUE;
			}
			break;
		}
		case NECP_POLICY_CONDITION_PID: {
			if (condition_length >= sizeof(pid_t) &&
				condition_value != NULL &&
				*((pid_t *)(void *)condition_value) != 0) {
				validated = TRUE;
			}
			break;
		}
		case NECP_POLICY_CONDITION_UID: {
			if (condition_length >= sizeof(uid_t)) {
				validated = TRUE;
			}
			break;
		}
		case NECP_POLICY_CONDITION_LOCAL_ADDR:
		case NECP_POLICY_CONDITION_REMOTE_ADDR: {
			if (!result_cannot_have_ip_layer && condition_length >= sizeof(struct necp_policy_condition_addr) &&
				necp_address_is_valid(&((struct necp_policy_condition_addr *)(void *)condition_value)->address.sa)) {
				validated = TRUE;
			}
			break;
		}
		case NECP_POLICY_CONDITION_LOCAL_ADDR_RANGE:
		case NECP_POLICY_CONDITION_REMOTE_ADDR_RANGE: {
			if (!result_cannot_have_ip_layer && condition_length >= sizeof(struct necp_policy_condition_addr_range) &&
				necp_address_is_valid(&((struct necp_policy_condition_addr_range *)(void *)condition_value)->start_address.sa) &&
				necp_address_is_valid(&((struct necp_policy_condition_addr_range *)(void *)condition_value)->end_address.sa)) {
				validated = TRUE;
			}
			break;
		}
		case NECP_POLICY_CONDITION_AGENT_TYPE: {
			if (!(flags & NECP_POLICY_CONDITION_FLAGS_NEGATIVE) &&
				condition_length >= sizeof(struct necp_policy_condition_agent_type)) {
				validated = TRUE;
			}
			break;
		}
		default: {
			validated = FALSE;
			break;
		}
	}

	if (necp_debug) {
		NECPLOG(LOG_DEBUG, "Policy condition type %d, valid %d", type, validated);
	}

	return (validated);
}