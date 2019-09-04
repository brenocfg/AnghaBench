#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  union sockaddr_in_4_6 {int dummy; } sockaddr_in_4_6 ;
typedef  scalar_t__ u_int8_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct necp_client_parsed_parameters {int flags; } ;
struct TYPE_8__ {scalar_t__ sa_family; } ;
struct TYPE_12__ {TYPE_1__ sa; } ;
struct TYPE_9__ {scalar_t__ sa_family; } ;
struct TYPE_11__ {TYPE_2__ sa; } ;
struct necp_client_flow {TYPE_5__ remote_addr; TYPE_4__ local_addr; } ;
struct necp_client {TYPE_3__* current_route; scalar_t__ parameters_length; int /*<<< orphan*/  parameters; } ;
struct TYPE_13__ {int if_eflags; } ;
struct TYPE_10__ {TYPE_6__* rt_ifp; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int EINVAL ; 
 int ENOENT ; 
 int IFEF_ECN_DISABLE ; 
 int IFEF_ECN_ENABLE ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  NECPLOG (int /*<<< orphan*/ ,char*,int) ; 
 int NECP_CLIENT_PARAMETER_FLAG_ECN_DISABLE ; 
 int NECP_CLIENT_PARAMETER_FLAG_ECN_ENABLE ; 
 int NECP_CLIENT_PARAMETER_FLAG_LISTENER ; 
 int NECP_CLIENT_PARAMETER_FLAG_TFO_ENABLE ; 
 int /*<<< orphan*/  NECP_CLIENT_RESULT_FLAG_ECN_ENABLED ; 
 int /*<<< orphan*/  NECP_CLIENT_RESULT_FLAG_FAST_OPEN_BLOCKED ; 
 int /*<<< orphan*/  NECP_CLIENT_ROUTE_LOCK (struct necp_client*) ; 
 int /*<<< orphan*/  NECP_CLIENT_ROUTE_UNLOCK (struct necp_client*) ; 
 int necp_client_parse_parameters (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct necp_client_parsed_parameters*) ; 
 int tcp_ecn_inbound ; 
 int tcp_ecn_outbound ; 
 scalar_t__ tcp_heuristic_do_ecn_with_address (TYPE_6__*,union sockaddr_in_4_6*) ; 
 int /*<<< orphan*/  tcp_heuristic_do_tfo_with_address (TYPE_6__*,union sockaddr_in_4_6*,union sockaddr_in_4_6*,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static int
necp_client_check_tcp_heuristics(struct necp_client *client, struct necp_client_flow *flow, u_int32_t *flags, u_int8_t *tfo_cookie, u_int8_t *tfo_cookie_len)
{
	struct necp_client_parsed_parameters parsed_parameters;
	int error = 0;

	error = necp_client_parse_parameters(client->parameters,
					    (u_int32_t)client->parameters_length,
					    &parsed_parameters);
	if (error) {
		NECPLOG(LOG_ERR, "necp_client_parse_parameters error (%d)", error);
		return (error);
	}

	if ((flow->remote_addr.sa.sa_family != AF_INET &&
		 flow->remote_addr.sa.sa_family != AF_INET6) ||
		(flow->local_addr.sa.sa_family != AF_INET &&
		 flow->local_addr.sa.sa_family != AF_INET6)) {
		return (EINVAL);
	}

	NECP_CLIENT_ROUTE_LOCK(client);

	if (client->current_route == NULL) {
	    error = ENOENT;
	    goto do_unlock;
	}

	bool check_ecn = false;
	do {
		if ((parsed_parameters.flags & NECP_CLIENT_PARAMETER_FLAG_ECN_ENABLE) ==
			NECP_CLIENT_PARAMETER_FLAG_ECN_ENABLE) {
			check_ecn = true;
			break;
		}

		if ((parsed_parameters.flags & NECP_CLIENT_PARAMETER_FLAG_ECN_DISABLE) ==
			NECP_CLIENT_PARAMETER_FLAG_ECN_DISABLE) {
			break;
		}

		if (client->current_route != NULL) {
			if (client->current_route->rt_ifp->if_eflags & IFEF_ECN_ENABLE) {
				check_ecn = true;
				break;
			}
			if (client->current_route->rt_ifp->if_eflags & IFEF_ECN_DISABLE) {
				break;
			}
		}

		bool inbound = ((parsed_parameters.flags & NECP_CLIENT_PARAMETER_FLAG_LISTENER) == 0);
		if ((inbound && tcp_ecn_inbound == 1) ||
			(!inbound && tcp_ecn_outbound == 1)) {
			check_ecn = true;
		}
	} while (false);

	if (check_ecn) {
		if (tcp_heuristic_do_ecn_with_address(client->current_route->rt_ifp,
							(union sockaddr_in_4_6 *)&flow->local_addr)) {
			*flags |= NECP_CLIENT_RESULT_FLAG_ECN_ENABLED;
		}
	}

	if ((parsed_parameters.flags & NECP_CLIENT_PARAMETER_FLAG_TFO_ENABLE) ==
		NECP_CLIENT_PARAMETER_FLAG_TFO_ENABLE) {

		if (!tcp_heuristic_do_tfo_with_address(client->current_route->rt_ifp,
							(union sockaddr_in_4_6 *)&flow->local_addr,
							(union sockaddr_in_4_6 *)&flow->remote_addr,
							tfo_cookie, tfo_cookie_len)) {
			*flags |= NECP_CLIENT_RESULT_FLAG_FAST_OPEN_BLOCKED;
			*tfo_cookie_len = 0;
		}
	} else {
		*flags |= NECP_CLIENT_RESULT_FLAG_FAST_OPEN_BLOCKED;
		*tfo_cookie_len = 0;
	}
do_unlock:
	NECP_CLIENT_ROUTE_UNLOCK(client);

	return (error);
}