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
struct bstp_port {int bp_tcstate; TYPE_1__* bp_ifp; int /*<<< orphan*/  bp_operedge; int /*<<< orphan*/  bp_state; int /*<<< orphan*/  bp_role; int /*<<< orphan*/  bp_tc_prop; int /*<<< orphan*/  bp_rcvdtca; int /*<<< orphan*/  bp_rcvdtcn; int /*<<< orphan*/  bp_rcvdtc; int /*<<< orphan*/  bp_fdbflush; } ;
struct TYPE_2__ {int /*<<< orphan*/  if_xname; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSTP_IFSTATE_DISCARDING ; 
 int /*<<< orphan*/  BSTP_IFSTATE_FORWARDING ; 
 int /*<<< orphan*/  BSTP_IFSTATE_LEARNING ; 
 int /*<<< orphan*/  BSTP_ROLE_DESIGNATED ; 
 int /*<<< orphan*/  BSTP_ROLE_ROOT ; 
#define  BSTP_TCSTATE_ACK 135 
#define  BSTP_TCSTATE_ACTIVE 134 
#define  BSTP_TCSTATE_DETECTED 133 
#define  BSTP_TCSTATE_INACTIVE 132 
#define  BSTP_TCSTATE_LEARNING 131 
#define  BSTP_TCSTATE_PROPAG 130 
#define  BSTP_TCSTATE_TC 129 
#define  BSTP_TCSTATE_TCN 128 
 int /*<<< orphan*/  DPRINTF (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bstp_set_port_tc (struct bstp_port*,int const) ; 

__attribute__((used)) static void
bstp_update_tc(struct bstp_port *bp)
{
	switch (bp->bp_tcstate) {
		case BSTP_TCSTATE_ACTIVE:
			if ((bp->bp_role != BSTP_ROLE_DESIGNATED &&
			    bp->bp_role != BSTP_ROLE_ROOT) || bp->bp_operedge)
				bstp_set_port_tc(bp, BSTP_TCSTATE_LEARNING);

			if (bp->bp_rcvdtcn)
				bstp_set_port_tc(bp, BSTP_TCSTATE_TCN);
			if (bp->bp_rcvdtc)
				bstp_set_port_tc(bp, BSTP_TCSTATE_TC);

			if (bp->bp_tc_prop && !bp->bp_operedge)
				bstp_set_port_tc(bp, BSTP_TCSTATE_PROPAG);

			if (bp->bp_rcvdtca)
				bstp_set_port_tc(bp, BSTP_TCSTATE_ACK);
			break;

		case BSTP_TCSTATE_INACTIVE:
			if ((bp->bp_state == BSTP_IFSTATE_LEARNING ||
			    bp->bp_state == BSTP_IFSTATE_FORWARDING) &&
			    bp->bp_fdbflush == 0)
				bstp_set_port_tc(bp, BSTP_TCSTATE_LEARNING);
			break;

		case BSTP_TCSTATE_LEARNING:
			if (bp->bp_rcvdtc || bp->bp_rcvdtcn || bp->bp_rcvdtca ||
			    bp->bp_tc_prop)
				bstp_set_port_tc(bp, BSTP_TCSTATE_LEARNING);
			else if (bp->bp_role != BSTP_ROLE_DESIGNATED &&
				 bp->bp_role != BSTP_ROLE_ROOT &&
				 bp->bp_state == BSTP_IFSTATE_DISCARDING)
				bstp_set_port_tc(bp, BSTP_TCSTATE_INACTIVE);

			if ((bp->bp_role == BSTP_ROLE_DESIGNATED ||
			    bp->bp_role == BSTP_ROLE_ROOT) &&
			    bp->bp_state == BSTP_IFSTATE_FORWARDING &&
			    !bp->bp_operedge)
				bstp_set_port_tc(bp, BSTP_TCSTATE_DETECTED);
			break;

		/* these are transient states and go straight back to ACTIVE */
		case BSTP_TCSTATE_DETECTED:
		case BSTP_TCSTATE_TCN:
		case BSTP_TCSTATE_TC:
		case BSTP_TCSTATE_PROPAG:
		case BSTP_TCSTATE_ACK:
			DPRINTF("Invalid TC state for %s\n",
			    bp->bp_ifp->if_xname);
			break;
	}

}