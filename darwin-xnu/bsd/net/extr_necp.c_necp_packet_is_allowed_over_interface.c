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
typedef  scalar_t__ u_int32_t ;
struct mbuf {int dummy; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int TRUE ; 
 int /*<<< orphan*/  lck_rw_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_lock_shared (int /*<<< orphan*/ *) ; 
 scalar_t__ necp_get_route_rule_id_from_packet (struct mbuf*) ; 
 int /*<<< orphan*/  necp_kernel_policy_lock ; 
 int necp_route_is_allowed (int /*<<< orphan*/ *,struct ifnet*,scalar_t__,int /*<<< orphan*/ *) ; 

bool
necp_packet_is_allowed_over_interface(struct mbuf *packet, struct ifnet *interface)
{
	bool is_allowed = TRUE;
	u_int32_t route_rule_id = necp_get_route_rule_id_from_packet(packet);
	if (route_rule_id != 0 &&
		interface != NULL) {
		lck_rw_lock_shared(&necp_kernel_policy_lock);
		is_allowed = necp_route_is_allowed(NULL, interface, necp_get_route_rule_id_from_packet(packet), NULL);
		lck_rw_done(&necp_kernel_policy_lock);
	}
	return (is_allowed);
}