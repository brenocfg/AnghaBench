#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int32_t ;
struct TYPE_7__ {scalar_t__ necp_skip_policy_id; int /*<<< orphan*/  necp_app_id; scalar_t__ necp_route_rule_id; scalar_t__ necp_last_interface_index; scalar_t__ necp_policy_id; } ;
struct TYPE_8__ {TYPE_3__ necp_mtag; } ;
struct mbuf {int m_flags; TYPE_4__ m_pkthdr; } ;
struct TYPE_5__ {scalar_t__ result; scalar_t__ route_rule_id; } ;
struct TYPE_6__ {int /*<<< orphan*/  app_id; TYPE_1__ results; scalar_t__ policy_id; } ;
struct inpcb {TYPE_2__ inp_policyresult; } ;
typedef  scalar_t__ necp_kernel_policy_id ;

/* Variables and functions */
 int EINVAL ; 
 int M_PKTHDR ; 
 scalar_t__ NECP_KERNEL_POLICY_ID_NONE ; 
 scalar_t__ NECP_KERNEL_POLICY_RESULT_IP_TUNNEL ; 
 scalar_t__ NECP_KERNEL_POLICY_RESULT_PASS ; 

int
necp_mark_packet_from_socket(struct mbuf *packet, struct inpcb *inp, necp_kernel_policy_id policy_id, u_int32_t route_rule_id,
							 necp_kernel_policy_id skip_policy_id)
{
	if (packet == NULL || inp == NULL || !(packet->m_flags & M_PKTHDR)) {
		return (EINVAL);
	}

	// Mark ID for Pass and IP Tunnel
	if (policy_id != NECP_KERNEL_POLICY_ID_NONE) {
		packet->m_pkthdr.necp_mtag.necp_policy_id = policy_id;
	} else if (inp->inp_policyresult.results.result == NECP_KERNEL_POLICY_RESULT_PASS ||
		inp->inp_policyresult.results.result == NECP_KERNEL_POLICY_RESULT_IP_TUNNEL) {
		packet->m_pkthdr.necp_mtag.necp_policy_id = inp->inp_policyresult.policy_id;
	} else {
		packet->m_pkthdr.necp_mtag.necp_policy_id = NECP_KERNEL_POLICY_ID_NONE;
	}
	packet->m_pkthdr.necp_mtag.necp_last_interface_index = 0;
	if (route_rule_id != 0) {
		packet->m_pkthdr.necp_mtag.necp_route_rule_id = route_rule_id;
	} else {
		packet->m_pkthdr.necp_mtag.necp_route_rule_id = inp->inp_policyresult.results.route_rule_id;
	}
	packet->m_pkthdr.necp_mtag.necp_app_id = inp->inp_policyresult.app_id;

	if (skip_policy_id != NECP_KERNEL_POLICY_ID_NONE) {
		packet->m_pkthdr.necp_mtag.necp_skip_policy_id = skip_policy_id;
	}

	return (0);
}