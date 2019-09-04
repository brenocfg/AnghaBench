#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int32_t ;
typedef  size_t u_int ;
struct ip6_hdr {int dummy; } ;
struct TYPE_10__ {size_t tunnel_interface_index; } ;
struct TYPE_11__ {scalar_t__ result; TYPE_2__ result_parameter; } ;
struct TYPE_12__ {TYPE_3__ results; } ;
struct inpcb {int inp_flags; TYPE_4__ inp_policyresult; TYPE_1__* inp_boundifp; } ;
typedef  TYPE_7__* ifnet_t ;
struct TYPE_14__ {TYPE_5__* ifp; } ;
struct TYPE_15__ {scalar_t__ if_mtu; int /*<<< orphan*/  if_name; TYPE_6__ if_delegated; } ;
struct TYPE_13__ {scalar_t__ if_mtu; } ;
struct TYPE_9__ {size_t if_index; } ;

/* Variables and functions */
 int INP_BOUND_IF ; 
 scalar_t__ NECP_KERNEL_POLICY_RESULT_IP_TUNNEL ; 
 scalar_t__ esp_hdrsiz (int /*<<< orphan*/ *) ; 
 TYPE_7__** ifindex2ifnet ; 
 int /*<<< orphan*/  ifnet_head_done () ; 
 int /*<<< orphan*/  ifnet_head_lock_shared () ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

u_int32_t
necp_socket_get_effective_mtu(struct inpcb *inp, u_int32_t current_mtu)
{
	if (inp == NULL) {
		return (current_mtu);
	}

	if (inp->inp_policyresult.results.result == NECP_KERNEL_POLICY_RESULT_IP_TUNNEL &&
		(inp->inp_flags & INP_BOUND_IF) &&
		inp->inp_boundifp) {

		u_int bound_interface_index = inp->inp_boundifp->if_index;
		u_int tunnel_interface_index = inp->inp_policyresult.results.result_parameter.tunnel_interface_index;

		// The result is IP Tunnel, and is rescoping from one interface to another. Recalculate MTU.
		if (bound_interface_index != tunnel_interface_index) {
			ifnet_t tunnel_interface = NULL;

			ifnet_head_lock_shared();
			tunnel_interface = ifindex2ifnet[tunnel_interface_index];
			ifnet_head_done();

			if (tunnel_interface != NULL) {
				u_int32_t direct_tunnel_mtu = tunnel_interface->if_mtu;
				u_int32_t delegate_tunnel_mtu = (tunnel_interface->if_delegated.ifp != NULL) ? tunnel_interface->if_delegated.ifp->if_mtu : 0;
				if (delegate_tunnel_mtu != 0 &&
					strncmp(tunnel_interface->if_name, "ipsec", strlen("ipsec")) == 0) {
						// For ipsec interfaces, calculate the overhead from the delegate interface
						u_int32_t tunnel_overhead = (u_int32_t)(esp_hdrsiz(NULL) + sizeof(struct ip6_hdr));
						if (delegate_tunnel_mtu > tunnel_overhead) {
							delegate_tunnel_mtu -= tunnel_overhead;
						}

						if (delegate_tunnel_mtu < direct_tunnel_mtu) {
							// If the (delegate - overhead) < direct, return (delegate - overhead)
							return (delegate_tunnel_mtu);
						} else {
							// Otherwise return direct
							return (direct_tunnel_mtu);
						}
				} else {
					// For non-ipsec interfaces, just return the tunnel MTU
					return (direct_tunnel_mtu);
				}
			}
		}
	}

	// By default, just return the MTU passed in
	return (current_mtu);
}