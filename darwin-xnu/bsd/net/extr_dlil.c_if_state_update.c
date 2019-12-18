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
typedef  scalar_t__ u_short ;
struct TYPE_2__ {int valid_bitmask; scalar_t__ interface_availability; } ;
struct ifnet {scalar_t__ if_type; scalar_t__ if_index; TYPE_1__ if_interface_state; } ;
struct if_interface_state {int valid_bitmask; scalar_t__ interface_availability; int /*<<< orphan*/  rrc_state; int /*<<< orphan*/  lqm_state; } ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOTSUP ; 
 int /*<<< orphan*/  IFNET_LQM_MAX ; 
 int /*<<< orphan*/  IFNET_LQM_MIN ; 
 scalar_t__ IFT_CELLULAR ; 
 int IF_INTERFACE_STATE_INTERFACE_AVAILABILITY_VALID ; 
 scalar_t__ IF_INTERFACE_STATE_INTERFACE_AVAILABLE ; 
 int IF_INTERFACE_STATE_LQM_STATE_VALID ; 
 int /*<<< orphan*/  IF_INTERFACE_STATE_RRC_STATE_CONNECTED ; 
 int /*<<< orphan*/  IF_INTERFACE_STATE_RRC_STATE_IDLE ; 
 int IF_INTERFACE_STATE_RRC_STATE_VALID ; 
 int /*<<< orphan*/  if_lqm_update (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_rrc_state_update (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifnet_lock_done (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_lock_exclusive (struct ifnet*) ; 
 int /*<<< orphan*/  tcp_interface_send_probe (scalar_t__) ; 

errno_t
if_state_update(struct ifnet *ifp,
    struct if_interface_state *if_interface_state)
{
	u_short if_index_available = 0;

	ifnet_lock_exclusive(ifp);

	if ((ifp->if_type != IFT_CELLULAR) &&
	    (if_interface_state->valid_bitmask &
	    IF_INTERFACE_STATE_RRC_STATE_VALID)) {
		ifnet_lock_done(ifp);
		return (ENOTSUP);
	}
	if ((if_interface_state->valid_bitmask &
	    IF_INTERFACE_STATE_LQM_STATE_VALID) &&
	    (if_interface_state->lqm_state < IFNET_LQM_MIN ||
	    if_interface_state->lqm_state > IFNET_LQM_MAX)) {
		ifnet_lock_done(ifp);
		return (EINVAL);
	}
	if ((if_interface_state->valid_bitmask &
	    IF_INTERFACE_STATE_RRC_STATE_VALID) &&
	    if_interface_state->rrc_state !=
	    IF_INTERFACE_STATE_RRC_STATE_IDLE &&
	    if_interface_state->rrc_state !=
	    IF_INTERFACE_STATE_RRC_STATE_CONNECTED) {
		ifnet_lock_done(ifp);
		return (EINVAL);
	}

	if (if_interface_state->valid_bitmask &
	    IF_INTERFACE_STATE_LQM_STATE_VALID) {
		if_lqm_update(ifp, if_interface_state->lqm_state, 1);
	}
	if (if_interface_state->valid_bitmask &
	    IF_INTERFACE_STATE_RRC_STATE_VALID) {
		if_rrc_state_update(ifp, if_interface_state->rrc_state);
	}
	if (if_interface_state->valid_bitmask &
	    IF_INTERFACE_STATE_INTERFACE_AVAILABILITY_VALID) {
		ifp->if_interface_state.valid_bitmask |=
		    IF_INTERFACE_STATE_INTERFACE_AVAILABILITY_VALID;
		ifp->if_interface_state.interface_availability =
		    if_interface_state->interface_availability;

		if (ifp->if_interface_state.interface_availability ==
		    IF_INTERFACE_STATE_INTERFACE_AVAILABLE) {
			if_index_available = ifp->if_index;
		}
	}
	ifnet_lock_done(ifp);

	/*
	 * Check if the TCP connections going on this interface should be
	 * forced to send probe packets instead of waiting for TCP timers
	 * to fire. This will be done when there is an explicit
	 * notification that the interface became available.
	 */
	if (if_index_available > 0)
		tcp_interface_send_probe(if_index_available);

	return (0);
}