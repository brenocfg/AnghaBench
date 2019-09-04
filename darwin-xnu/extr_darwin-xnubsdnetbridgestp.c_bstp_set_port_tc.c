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
struct bstp_state {int /*<<< orphan*/  bs_last_tc_time; } ;
struct bstp_port {int bp_tcstate; int bp_fdbflush; int bp_tc_ack; TYPE_1__* bp_ifp; int /*<<< orphan*/  bp_rcvdtca; int /*<<< orphan*/  bp_tc_timer; int /*<<< orphan*/  bp_tc_prop; int /*<<< orphan*/  bp_rtagetask; int /*<<< orphan*/  bp_role; int /*<<< orphan*/  bp_rcvdtcn; int /*<<< orphan*/  bp_rcvdtc; int /*<<< orphan*/  bp_flags; struct bstp_state* bp_bs; } ;
struct TYPE_2__ {int /*<<< orphan*/  if_xname; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSTP_PORT_NEWINFO ; 
 int /*<<< orphan*/  BSTP_ROLE_DESIGNATED ; 
#define  BSTP_TCSTATE_ACK 135 
#define  BSTP_TCSTATE_ACTIVE 134 
#define  BSTP_TCSTATE_DETECTED 133 
#define  BSTP_TCSTATE_INACTIVE 132 
#define  BSTP_TCSTATE_LEARNING 131 
#define  BSTP_TCSTATE_PROPAG 130 
#define  BSTP_TCSTATE_TC 129 
#define  BSTP_TCSTATE_TCN 128 
 int /*<<< orphan*/  DPRINTF (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bstp_set_other_tcprop (struct bstp_port*) ; 
 int /*<<< orphan*/  bstp_set_timer_tc (struct bstp_port*) ; 
 int /*<<< orphan*/  bstp_task_enqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bstp_timer_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bstp_transmit (struct bstp_state*,struct bstp_port*) ; 
 int /*<<< orphan*/  getmicrotime (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bstp_set_port_tc(struct bstp_port *bp, int state)
{
	struct bstp_state *bs = bp->bp_bs;

	bp->bp_tcstate = state;

	/* initialise the new state */
	switch (bp->bp_tcstate) {
		case BSTP_TCSTATE_ACTIVE:
			DPRINTF("%s -> TC_ACTIVE\n", bp->bp_ifp->if_xname);
			/* nothing to do */
			break;

		case BSTP_TCSTATE_INACTIVE:
			bstp_timer_stop(&bp->bp_tc_timer);
			/* flush routes on the parent bridge */
			bp->bp_fdbflush = 1;
			bstp_task_enqueue(&bp->bp_rtagetask);
			bp->bp_tc_ack = 0;
			DPRINTF("%s -> TC_INACTIVE\n", bp->bp_ifp->if_xname);
			break;

		case BSTP_TCSTATE_LEARNING:
			bp->bp_rcvdtc = 0;
			bp->bp_rcvdtcn = 0;
			bp->bp_rcvdtca = 0;
			bp->bp_tc_prop = 0;
			DPRINTF("%s -> TC_LEARNING\n", bp->bp_ifp->if_xname);
			break;

		case BSTP_TCSTATE_DETECTED:
			bstp_set_timer_tc(bp);
			bstp_set_other_tcprop(bp);
			/* send out notification */
			bp->bp_flags |= BSTP_PORT_NEWINFO;
			bstp_transmit(bs, bp);
			/* reviewed for getmicrotime usage */
			getmicrotime(&bs->bs_last_tc_time);
			DPRINTF("%s -> TC_DETECTED\n", bp->bp_ifp->if_xname);
			bp->bp_tcstate = BSTP_TCSTATE_ACTIVE; /* UCT */
			break;

		case BSTP_TCSTATE_TCN:
			bstp_set_timer_tc(bp);
			DPRINTF("%s -> TC_TCN\n", bp->bp_ifp->if_xname);
			/* fall through */
		case BSTP_TCSTATE_TC:
			bp->bp_rcvdtc = 0;
			bp->bp_rcvdtcn = 0;
			if (bp->bp_role == BSTP_ROLE_DESIGNATED)
				bp->bp_tc_ack = 1;

			bstp_set_other_tcprop(bp);
			DPRINTF("%s -> TC_TC\n", bp->bp_ifp->if_xname);
			bp->bp_tcstate = BSTP_TCSTATE_ACTIVE; /* UCT */
			break;

		case BSTP_TCSTATE_PROPAG:
			/* flush routes on the parent bridge */
			bp->bp_fdbflush = 1;
			bstp_task_enqueue(&bp->bp_rtagetask);
			bp->bp_tc_prop = 0;
			bstp_set_timer_tc(bp);
			DPRINTF("%s -> TC_PROPAG\n", bp->bp_ifp->if_xname);
			bp->bp_tcstate = BSTP_TCSTATE_ACTIVE; /* UCT */
			break;

		case BSTP_TCSTATE_ACK:
			bstp_timer_stop(&bp->bp_tc_timer);
			bp->bp_rcvdtca = 0;
			DPRINTF("%s -> TC_ACK\n", bp->bp_ifp->if_xname);
			bp->bp_tcstate = BSTP_TCSTATE_ACTIVE; /* UCT */
			break;
	}
}