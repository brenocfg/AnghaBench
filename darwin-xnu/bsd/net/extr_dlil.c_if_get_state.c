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
struct TYPE_2__ {int valid_bitmask; int /*<<< orphan*/  interface_availability; int /*<<< orphan*/  lqm_state; int /*<<< orphan*/  rrc_state; } ;
struct ifnet {TYPE_1__ if_interface_state; } ;
struct if_interface_state {int valid_bitmask; int /*<<< orphan*/  interface_availability; int /*<<< orphan*/  lqm_state; int /*<<< orphan*/  rrc_state; } ;

/* Variables and functions */
 int IF_INTERFACE_STATE_INTERFACE_AVAILABILITY_VALID ; 
 int IF_INTERFACE_STATE_LQM_STATE_VALID ; 
 int IF_INTERFACE_STATE_RRC_STATE_VALID ; 
 int /*<<< orphan*/  ifnet_lock_done (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_lock_shared (struct ifnet*) ; 

void
if_get_state(struct ifnet *ifp,
    struct if_interface_state *if_interface_state)
{
	ifnet_lock_shared(ifp);

	if_interface_state->valid_bitmask = 0;

	if (ifp->if_interface_state.valid_bitmask &
	    IF_INTERFACE_STATE_RRC_STATE_VALID) {
		if_interface_state->valid_bitmask |=
		    IF_INTERFACE_STATE_RRC_STATE_VALID;
		if_interface_state->rrc_state =
		    ifp->if_interface_state.rrc_state;
	}
	if (ifp->if_interface_state.valid_bitmask &
	    IF_INTERFACE_STATE_LQM_STATE_VALID) {
		if_interface_state->valid_bitmask |=
		    IF_INTERFACE_STATE_LQM_STATE_VALID;
		if_interface_state->lqm_state =
		    ifp->if_interface_state.lqm_state;
	}
	if (ifp->if_interface_state.valid_bitmask &
	    IF_INTERFACE_STATE_INTERFACE_AVAILABILITY_VALID) {
		if_interface_state->valid_bitmask |=
		    IF_INTERFACE_STATE_INTERFACE_AVAILABILITY_VALID;
		if_interface_state->interface_availability =
		    ifp->if_interface_state.interface_availability;
	}

	ifnet_lock_done(ifp);
}