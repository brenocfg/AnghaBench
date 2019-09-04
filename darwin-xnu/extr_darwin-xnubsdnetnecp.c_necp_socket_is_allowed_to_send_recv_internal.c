#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int32_t ;
struct sockaddr {int dummy; } ;
struct rtentry {int dummy; } ;
struct necp_socket_info {int /*<<< orphan*/  application_id; } ;
struct TYPE_11__ {scalar_t__ tunnel_interface_index; } ;
struct necp_kernel_socket_policy {scalar_t__ result; scalar_t__ id; TYPE_1__ result_parameter; } ;
struct TYPE_13__ {scalar_t__ tunnel_interface_index; } ;
struct TYPE_14__ {scalar_t__ route_rule_id; scalar_t__ result; TYPE_3__ result_parameter; } ;
struct TYPE_15__ {scalar_t__ policy_id; scalar_t__ policy_gencount; scalar_t__ skip_policy_id; scalar_t__ flowhash; TYPE_4__ results; } ;
struct TYPE_12__ {struct rtentry* ro_rt; } ;
struct inpcb {int inp_flags2; int /*<<< orphan*/  inp_socket; TYPE_5__ inp_policyresult; TYPE_2__ inp_route; } ;
typedef  int /*<<< orphan*/  netagent_ids ;
struct TYPE_16__ {scalar_t__ identifier; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_6__ necp_kernel_policy_service ;
typedef  scalar_t__ necp_kernel_policy_result ;
typedef  scalar_t__ necp_kernel_policy_id ;
typedef  TYPE_7__* ifnet_t ;
struct TYPE_17__ {scalar_t__ if_index; } ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ IFRTYPE_FUNCTIONAL_UNKNOWN ; 
 int INP2_WANT_APP_POLICY ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  NECPLOG (int /*<<< orphan*/ ,char*,scalar_t__,int) ; 
 scalar_t__ NECP_KERNEL_POLICY_ID_NONE ; 
 scalar_t__ NECP_KERNEL_POLICY_ID_NO_MATCH ; 
 scalar_t__ NECP_KERNEL_POLICY_RESULT_DROP ; 
 scalar_t__ NECP_KERNEL_POLICY_RESULT_IP_TUNNEL ; 
 scalar_t__ NECP_KERNEL_POLICY_RESULT_NO_TRIGGER_SCOPED ; 
 scalar_t__ NECP_KERNEL_POLICY_RESULT_SOCKET_DIVERT ; 
 scalar_t__ NECP_KERNEL_POLICY_RESULT_TRIGGER_SCOPED ; 
 int NECP_MAX_NETAGENTS ; 
 scalar_t__ NECP_NULL_SERVICE_ID ; 
 size_t NECP_SOCKET_MAP_APP_ID_TO_BUCKET (int /*<<< orphan*/ ) ; 
 int SO_FILT_HINT_IFDENIED ; 
 int SO_FILT_HINT_LOCKED ; 
 int TRUE ; 
 int /*<<< orphan*/  current_proc () ; 
 int /*<<< orphan*/  lck_rw_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_lock_shared (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (scalar_t__**,int /*<<< orphan*/ ,int) ; 
 int necp_debug ; 
 scalar_t__ necp_drop_all_order ; 
 int /*<<< orphan*/  necp_kernel_policy_lock ; 
 scalar_t__ necp_kernel_socket_policies_count ; 
 scalar_t__ necp_kernel_socket_policies_gencount ; 
 int /*<<< orphan*/ * necp_kernel_socket_policies_map ; 
 scalar_t__ necp_kernel_socket_policies_non_app_count ; 
 int /*<<< orphan*/  necp_netagents_allow_traffic (scalar_t__*,int) ; 
 int /*<<< orphan*/  necp_route_is_allowed (struct rtentry*,TYPE_7__*,scalar_t__,scalar_t__*) ; 
 scalar_t__ necp_socket_bypass (struct sockaddr*,struct sockaddr*,struct inpcb*) ; 
 scalar_t__ necp_socket_calc_flowhash_locked (struct necp_socket_info*) ; 
 int /*<<< orphan*/  necp_socket_fillout_info_locked (struct inpcb*,struct sockaddr*,struct sockaddr*,int /*<<< orphan*/ ,struct necp_socket_info*) ; 
 struct necp_kernel_socket_policy* necp_socket_find_policy_match_with_info_locked (int /*<<< orphan*/ ,struct necp_socket_info*,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*,TYPE_6__*,scalar_t__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ necp_socket_is_connected (struct inpcb*) ; 
 int /*<<< orphan*/  soevent (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
necp_socket_is_allowed_to_send_recv_internal(struct inpcb *inp, struct sockaddr *override_local_addr, struct sockaddr *override_remote_addr, ifnet_t interface, necp_kernel_policy_id *return_policy_id, u_int32_t *return_route_rule_id, necp_kernel_policy_id *return_skip_policy_id)
{
	u_int32_t verifyifindex = interface ? interface->if_index : 0;
	bool allowed_to_receive = TRUE;
	struct necp_socket_info info;
	u_int32_t flowhash = 0;
	necp_kernel_policy_result service_action = 0;
	necp_kernel_policy_service service = { 0, 0 };
	u_int32_t route_rule_id = 0;
	struct rtentry *route = NULL;
	u_int32_t interface_type_denied = IFRTYPE_FUNCTIONAL_UNKNOWN;

	u_int32_t netagent_ids[NECP_MAX_NETAGENTS];
	memset(&netagent_ids, 0, sizeof(netagent_ids));

	if (return_policy_id) {
		*return_policy_id = NECP_KERNEL_POLICY_ID_NONE;
	}
	if (return_skip_policy_id) {
		*return_skip_policy_id = NECP_KERNEL_POLICY_ID_NONE;
	}
	if (return_route_rule_id) {
		*return_route_rule_id = 0;
	}

	if (inp == NULL) {
		goto done;
	}

	route = inp->inp_route.ro_rt;

	// Don't lock. Possible race condition, but we don't want the performance hit.
	if (necp_kernel_socket_policies_count == 0 ||
		(!(inp->inp_flags2 & INP2_WANT_APP_POLICY) && necp_kernel_socket_policies_non_app_count == 0)) {
		if (necp_drop_all_order > 0) {
			if (necp_socket_bypass(override_local_addr, override_remote_addr, inp)) {
				allowed_to_receive = TRUE;
			} else {
				allowed_to_receive = FALSE;
			}
		}
		goto done;
	}

	// If this socket is connected, or we are not taking addresses into account, try to reuse last result
	if ((necp_socket_is_connected(inp) || (override_local_addr == NULL && override_remote_addr == NULL)) && inp->inp_policyresult.policy_id != NECP_KERNEL_POLICY_ID_NONE) {
		bool policies_have_changed = FALSE;
		bool route_allowed = TRUE;

		if (inp->inp_policyresult.policy_gencount != necp_kernel_socket_policies_gencount) {
			policies_have_changed = TRUE;
		} else {
			if (inp->inp_policyresult.results.route_rule_id != 0) {
				lck_rw_lock_shared(&necp_kernel_policy_lock);
				if (!necp_route_is_allowed(route, interface, inp->inp_policyresult.results.route_rule_id, &interface_type_denied)) {
					route_allowed = FALSE;
				}
				lck_rw_done(&necp_kernel_policy_lock);
			}
		}

		if (!policies_have_changed) {
			if (!route_allowed ||
				inp->inp_policyresult.results.result == NECP_KERNEL_POLICY_RESULT_DROP ||
				inp->inp_policyresult.results.result == NECP_KERNEL_POLICY_RESULT_SOCKET_DIVERT ||
				(inp->inp_policyresult.results.result == NECP_KERNEL_POLICY_RESULT_IP_TUNNEL && interface &&
				inp->inp_policyresult.results.result_parameter.tunnel_interface_index != verifyifindex)) {
					allowed_to_receive = FALSE;
				} else {
					if (return_policy_id) {
						*return_policy_id = inp->inp_policyresult.policy_id;
					}
					if (return_skip_policy_id) {
						*return_skip_policy_id = inp->inp_policyresult.skip_policy_id;
					}
					if (return_route_rule_id) {
						*return_route_rule_id = inp->inp_policyresult.results.route_rule_id;
					}
				}
			goto done;
		}
	}

	// Check for loopback exception
	if (necp_socket_bypass(override_local_addr, override_remote_addr, inp)) {
		allowed_to_receive = TRUE;
		goto done;
	}

	// Actually calculate policy result
	lck_rw_lock_shared(&necp_kernel_policy_lock);
	necp_socket_fillout_info_locked(inp, override_local_addr, override_remote_addr, 0, &info);

	flowhash = necp_socket_calc_flowhash_locked(&info);
	if (inp->inp_policyresult.policy_id != NECP_KERNEL_POLICY_ID_NONE &&
		inp->inp_policyresult.policy_gencount == necp_kernel_socket_policies_gencount &&
		inp->inp_policyresult.flowhash == flowhash) {
		if (inp->inp_policyresult.results.result == NECP_KERNEL_POLICY_RESULT_DROP ||
			inp->inp_policyresult.results.result == NECP_KERNEL_POLICY_RESULT_SOCKET_DIVERT ||
			(inp->inp_policyresult.results.result == NECP_KERNEL_POLICY_RESULT_IP_TUNNEL && interface &&
			inp->inp_policyresult.results.result_parameter.tunnel_interface_index != verifyifindex) ||
			(inp->inp_policyresult.results.route_rule_id != 0 &&
			 !necp_route_is_allowed(route, interface, inp->inp_policyresult.results.route_rule_id, &interface_type_denied))) {
			allowed_to_receive = FALSE;
		} else {
			if (return_policy_id) {
				*return_policy_id = inp->inp_policyresult.policy_id;
			}
			if (return_route_rule_id) {
				*return_route_rule_id = inp->inp_policyresult.results.route_rule_id;
			}
		}
		lck_rw_done(&necp_kernel_policy_lock);
		goto done;
	}

	struct necp_kernel_socket_policy *matched_policy = necp_socket_find_policy_match_with_info_locked(necp_kernel_socket_policies_map[NECP_SOCKET_MAP_APP_ID_TO_BUCKET(info.application_id)], &info, NULL, &route_rule_id, &service_action, &service, netagent_ids, NULL, NECP_MAX_NETAGENTS, NULL, 0, current_proc(), return_skip_policy_id);
	if (matched_policy != NULL) {
		if (matched_policy->result == NECP_KERNEL_POLICY_RESULT_DROP ||
			matched_policy->result == NECP_KERNEL_POLICY_RESULT_SOCKET_DIVERT ||
			(matched_policy->result == NECP_KERNEL_POLICY_RESULT_IP_TUNNEL && interface &&
			matched_policy->result_parameter.tunnel_interface_index != verifyifindex) ||
			((service_action == NECP_KERNEL_POLICY_RESULT_TRIGGER_SCOPED ||
			  service_action == NECP_KERNEL_POLICY_RESULT_NO_TRIGGER_SCOPED) &&
			 service.identifier != 0 && service.identifier != NECP_NULL_SERVICE_ID) ||
			(route_rule_id != 0 &&
			 !necp_route_is_allowed(route, interface, route_rule_id, &interface_type_denied)) ||
			!necp_netagents_allow_traffic(netagent_ids, NECP_MAX_NETAGENTS)) {
			allowed_to_receive = FALSE;
		} else {
			if (return_policy_id) {
				*return_policy_id = matched_policy->id;
			}
			if (return_route_rule_id) {
				*return_route_rule_id = route_rule_id;
			}
		}
		lck_rw_done(&necp_kernel_policy_lock);

		if (necp_debug > 1 && matched_policy->id != inp->inp_policyresult.policy_id) {
			NECPLOG(LOG_DEBUG, "Socket Send/Recv Policy: Policy %d Allowed %d", return_policy_id ? *return_policy_id : 0, allowed_to_receive);
		}
		goto done;
	} else if (necp_drop_all_order > 0) {
		allowed_to_receive = FALSE;
	} else {
		if (return_policy_id) {
			*return_policy_id = NECP_KERNEL_POLICY_ID_NO_MATCH;
		}
		if (return_route_rule_id) {
			*return_route_rule_id = route_rule_id;
		}
	}

	lck_rw_done(&necp_kernel_policy_lock);

done:
	if (!allowed_to_receive && interface_type_denied != IFRTYPE_FUNCTIONAL_UNKNOWN) {
		soevent(inp->inp_socket, (SO_FILT_HINT_LOCKED | SO_FILT_HINT_IFDENIED));
	}

	return (allowed_to_receive);
}