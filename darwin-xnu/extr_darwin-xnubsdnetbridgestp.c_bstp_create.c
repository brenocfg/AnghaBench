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
struct ifnet {int dummy; } ;
struct bstp_state {int /*<<< orphan*/  bs_protover; } ;
struct bstp_port {int bp_flags; int /*<<< orphan*/  bp_path_cost; int /*<<< orphan*/  bp_infois; int /*<<< orphan*/  bp_rtagetask; int /*<<< orphan*/  bp_statetask; int /*<<< orphan*/  bp_priority; struct bstp_state* bp_bs; struct ifnet* bp_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSTP_DEFAULT_PORT_PRIORITY ; 
 int /*<<< orphan*/  BSTP_IFSTATE_DISCARDING ; 
 int /*<<< orphan*/  BSTP_INFO_DISABLED ; 
 int /*<<< orphan*/  BSTP_LOCK (struct bstp_state*) ; 
 int BSTP_PORT_AUTOEDGE ; 
 int BSTP_PORT_AUTOPTP ; 
 int /*<<< orphan*/  BSTP_ROLE_DISABLED ; 
 int /*<<< orphan*/  BSTP_TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct bstp_port*) ; 
 int /*<<< orphan*/  BSTP_TCSTATE_INACTIVE ; 
 int /*<<< orphan*/  BSTP_UNLOCK (struct bstp_state*) ; 
 int /*<<< orphan*/  bstp_calc_path_cost (struct bstp_port*) ; 
 int /*<<< orphan*/  bstp_notify_rtage ; 
 int /*<<< orphan*/  bstp_notify_state ; 
 int /*<<< orphan*/  bstp_set_port_proto (struct bstp_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bstp_set_port_role (struct bstp_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bstp_set_port_state (struct bstp_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bstp_set_port_tc (struct bstp_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct bstp_port*,int) ; 

int
bstp_create(struct bstp_state *bs, struct bstp_port *bp, struct ifnet *ifp)
{
	bzero(bp, sizeof(struct bstp_port));

	BSTP_LOCK(bs);
	bp->bp_ifp = ifp;
	bp->bp_bs = bs;
	bp->bp_priority = BSTP_DEFAULT_PORT_PRIORITY;
	BSTP_TASK_INIT(&bp->bp_statetask, bstp_notify_state, bp);
	BSTP_TASK_INIT(&bp->bp_rtagetask, bstp_notify_rtage, bp);

	/* Init state */
	bp->bp_infois = BSTP_INFO_DISABLED;
	bp->bp_flags = BSTP_PORT_AUTOEDGE|BSTP_PORT_AUTOPTP;
	bstp_set_port_state(bp, BSTP_IFSTATE_DISCARDING);
	bstp_set_port_proto(bp, bs->bs_protover);
	bstp_set_port_role(bp, BSTP_ROLE_DISABLED);
	bstp_set_port_tc(bp, BSTP_TCSTATE_INACTIVE);
	bp->bp_path_cost = bstp_calc_path_cost(bp);
	BSTP_UNLOCK(bs);
	return (0);
}