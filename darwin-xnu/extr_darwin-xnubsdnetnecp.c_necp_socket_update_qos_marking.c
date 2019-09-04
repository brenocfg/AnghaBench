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
typedef  scalar_t__ u_int32_t ;
struct rtentry {struct ifnet* rt_ifp; } ;
struct necp_aggregate_route_rule {scalar_t__* rule_ids; } ;
struct TYPE_4__ {scalar_t__ qos_marking_gencount; } ;
struct TYPE_5__ {TYPE_1__ results; } ;
struct inpcb {TYPE_3__* inp_socket; TYPE_2__ inp_policyresult; } ;
struct ifnet {int dummy; } ;
struct TYPE_6__ {int so_flags1; } ;

/* Variables and functions */
 int FALSE ; 
 int MAX_AGGREGATE_ROUTE_RULES ; 
 scalar_t__ ROUTE_RULE_IS_AGGREGATE (scalar_t__) ; 
 int SOF1_QOSMARKING_ALLOWED ; 
 int SOF1_QOSMARKING_POLICY_OVERRIDE ; 
 int TRUE ; 
 int /*<<< orphan*/  lck_rw_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_lock_shared (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  necp_kernel_policy_lock ; 
 scalar_t__ necp_kernel_socket_policies_gencount ; 
 struct necp_aggregate_route_rule* necp_lookup_aggregate_route_rule_locked (scalar_t__) ; 
 int necp_update_qos_marking (struct ifnet*,scalar_t__) ; 
 scalar_t__ net_qos_policy_restricted ; 

void
necp_socket_update_qos_marking(struct inpcb *inp, struct rtentry *route, struct ifnet *interface, u_int32_t route_rule_id)
{
	bool qos_marking = FALSE;
	struct ifnet *ifp = interface = NULL;

	if (net_qos_policy_restricted == 0) {
		return;
	}
	if (inp->inp_socket == NULL) {
		return;
	}
	if ((inp->inp_socket->so_flags1 & SOF1_QOSMARKING_POLICY_OVERRIDE)) {
		return;
	}
	/*
	 * This is racy but we do not need the performance hit of taking necp_kernel_policy_lock
	 */
	if (inp->inp_policyresult.results.qos_marking_gencount == necp_kernel_socket_policies_gencount) {
		return;
	}

	lck_rw_lock_shared(&necp_kernel_policy_lock);

	if (ifp == NULL && route != NULL) {
		ifp = route->rt_ifp;
	}
	/*
	 * By default, until we have a interface, do not mark and reevaluate the Qos marking policy
	 */
	if (ifp == NULL || route_rule_id == 0) {
		qos_marking = FALSE;
		goto done;
	}

	if (ROUTE_RULE_IS_AGGREGATE(route_rule_id)) {
		struct necp_aggregate_route_rule *aggregate_route_rule = necp_lookup_aggregate_route_rule_locked(route_rule_id);
		if (aggregate_route_rule != NULL) {
			int index = 0;
			for (index = 0; index < MAX_AGGREGATE_ROUTE_RULES; index++) {
				u_int32_t sub_route_rule_id = aggregate_route_rule->rule_ids[index];
				if (sub_route_rule_id == 0) {
					break;
				}
				qos_marking = necp_update_qos_marking(ifp, sub_route_rule_id);
				if (qos_marking == TRUE) {
					break;
				}
			}
		}
	} else {
		qos_marking = necp_update_qos_marking(ifp, route_rule_id);
	}
	/*
	 * Now that we have an interface we remember the gencount
	 */
	inp->inp_policyresult.results.qos_marking_gencount = necp_kernel_socket_policies_gencount;

done:
	lck_rw_done(&necp_kernel_policy_lock);

	if (qos_marking == TRUE) {
		inp->inp_socket->so_flags1 |= SOF1_QOSMARKING_ALLOWED;
	} else {
		inp->inp_socket->so_flags1 &= ~SOF1_QOSMARKING_ALLOWED;
	}
}