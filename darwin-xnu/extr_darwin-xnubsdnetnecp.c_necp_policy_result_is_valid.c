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
typedef  int /*<<< orphan*/  uuid_t ;
typedef  int u_int8_t ;
typedef  int u_int32_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  NECPLOG (int /*<<< orphan*/ ,char*,int,int) ; 
#define  NECP_POLICY_RESULT_DROP 142 
#define  NECP_POLICY_RESULT_IP_TUNNEL 141 
#define  NECP_POLICY_RESULT_NETAGENT_SCOPED 140 
#define  NECP_POLICY_RESULT_NO_TRIGGER_SCOPED 139 
#define  NECP_POLICY_RESULT_PASS 138 
#define  NECP_POLICY_RESULT_ROUTE_RULES 137 
#define  NECP_POLICY_RESULT_SCOPED_DIRECT 136 
#define  NECP_POLICY_RESULT_SKIP 135 
#define  NECP_POLICY_RESULT_SOCKET_DIVERT 134 
#define  NECP_POLICY_RESULT_SOCKET_FILTER 133 
#define  NECP_POLICY_RESULT_SOCKET_SCOPED 132 
#define  NECP_POLICY_RESULT_TRIGGER 131 
#define  NECP_POLICY_RESULT_TRIGGER_IF_NEEDED 130 
#define  NECP_POLICY_RESULT_TRIGGER_SCOPED 129 
#define  NECP_POLICY_RESULT_USE_NETAGENT 128 
 int TRUE ; 
 scalar_t__ necp_debug ; 
 int necp_policy_result_get_parameter_length_from_buffer (int*,int) ; 
 int necp_policy_result_get_type_from_buffer (int*,int) ; 

__attribute__((used)) static bool
necp_policy_result_is_valid(u_int8_t *buffer, u_int32_t length)
{
	bool validated = FALSE;
	u_int8_t type = necp_policy_result_get_type_from_buffer(buffer, length);
	u_int32_t parameter_length = necp_policy_result_get_parameter_length_from_buffer(buffer, length);
	switch (type) {
		case NECP_POLICY_RESULT_PASS:
		case NECP_POLICY_RESULT_DROP:
		case NECP_POLICY_RESULT_ROUTE_RULES:
		case NECP_POLICY_RESULT_SCOPED_DIRECT: {
			validated = TRUE;
			break;
		}
		case NECP_POLICY_RESULT_SKIP:
		case NECP_POLICY_RESULT_SOCKET_DIVERT:
		case NECP_POLICY_RESULT_SOCKET_FILTER: {
			if (parameter_length >= sizeof(u_int32_t)) {
				validated = TRUE;
			}
			break;
		}
		case NECP_POLICY_RESULT_IP_TUNNEL: {
			if (parameter_length > sizeof(u_int32_t)) {
				validated = TRUE;
			}
			break;
		}
		case NECP_POLICY_RESULT_SOCKET_SCOPED: {
			if (parameter_length > 0) {
				validated = TRUE;
			}
			break;
		}
		case NECP_POLICY_RESULT_TRIGGER:
		case NECP_POLICY_RESULT_TRIGGER_IF_NEEDED:
		case NECP_POLICY_RESULT_TRIGGER_SCOPED:
		case NECP_POLICY_RESULT_NO_TRIGGER_SCOPED:
		case NECP_POLICY_RESULT_USE_NETAGENT:
		case NECP_POLICY_RESULT_NETAGENT_SCOPED:{
			if (parameter_length >= sizeof(uuid_t)) {
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
		NECPLOG(LOG_DEBUG, "Policy result type %d, valid %d", type, validated);
	}

	return (validated);
}