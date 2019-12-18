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
struct net_event_data {int dummy; } ;
struct kev_dl_rrc_state {unsigned int rrc_state; } ;
struct TYPE_2__ {unsigned int rrc_state; int valid_bitmask; } ;
struct ifnet {TYPE_1__ if_interface_state; } ;

/* Variables and functions */
 int IF_INTERFACE_STATE_RRC_STATE_VALID ; 
 int /*<<< orphan*/  KEV_DL_RRC_STATE_CHANGED ; 
 int /*<<< orphan*/  KEV_DL_SUBCLASS ; 
 int /*<<< orphan*/  bzero (struct kev_dl_rrc_state*,int) ; 
 int /*<<< orphan*/  dlil_post_msg (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_event_data*,int) ; 
 int /*<<< orphan*/  ifnet_lock_done (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_lock_exclusive (struct ifnet*) ; 

__attribute__((used)) static void
if_rrc_state_update(struct ifnet *ifp, unsigned int rrc_state)
{
	struct kev_dl_rrc_state kev;

	if (rrc_state == ifp->if_interface_state.rrc_state &&
	    (ifp->if_interface_state.valid_bitmask &
	    IF_INTERFACE_STATE_RRC_STATE_VALID))
		return;

	ifp->if_interface_state.valid_bitmask |=
	    IF_INTERFACE_STATE_RRC_STATE_VALID;

	ifp->if_interface_state.rrc_state = rrc_state;

	/*
	 * Don't want to hold the lock when issuing kernel events
	 */
	ifnet_lock_done(ifp);

	bzero(&kev, sizeof(struct kev_dl_rrc_state));
	kev.rrc_state = rrc_state;

	dlil_post_msg(ifp, KEV_DL_SUBCLASS, KEV_DL_RRC_STATE_CHANGED,
	    (struct net_event_data *)&kev, sizeof(struct kev_dl_rrc_state));

	ifnet_lock_exclusive(ifp);
}