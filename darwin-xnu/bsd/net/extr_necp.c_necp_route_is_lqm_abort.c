#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int valid_bitmask; scalar_t__ lqm_state; } ;
struct ifnet {TYPE_1__ if_interface_state; } ;

/* Variables and functions */
 scalar_t__ IFNET_LQM_THRESH_ABORT ; 
 int IF_INTERFACE_STATE_LQM_STATE_VALID ; 

__attribute__((used)) static bool
necp_route_is_lqm_abort(struct ifnet *ifp, struct ifnet *delegated_ifp)
{
	if (ifp != NULL &&
		(ifp->if_interface_state.valid_bitmask & IF_INTERFACE_STATE_LQM_STATE_VALID) &&
		ifp->if_interface_state.lqm_state == IFNET_LQM_THRESH_ABORT) {
		return true;
	}
	if (delegated_ifp != NULL &&
		(delegated_ifp->if_interface_state.valid_bitmask & IF_INTERFACE_STATE_LQM_STATE_VALID) &&
		delegated_ifp->if_interface_state.lqm_state == IFNET_LQM_THRESH_ABORT) {
		return true;
	}
	return false;
}