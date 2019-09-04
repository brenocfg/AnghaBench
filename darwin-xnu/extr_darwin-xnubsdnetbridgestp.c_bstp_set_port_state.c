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
struct bstp_port {int bp_state; int /*<<< orphan*/  bp_statetask; int /*<<< orphan*/  bp_forward_transitions; int /*<<< orphan*/  bp_forward_delay_timer; TYPE_1__* bp_ifp; int /*<<< orphan*/  bp_desg_fdelay; int /*<<< orphan*/  bp_desg_htime; int /*<<< orphan*/  bp_protover; } ;
struct TYPE_2__ {int /*<<< orphan*/  if_xname; } ;

/* Variables and functions */
#define  BSTP_IFSTATE_DISCARDING 130 
#define  BSTP_IFSTATE_FORWARDING 129 
#define  BSTP_IFSTATE_LEARNING 128 
 int /*<<< orphan*/  BSTP_PROTO_RSTP ; 
 int /*<<< orphan*/  DPRINTF (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bstp_task_enqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bstp_timer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bstp_timer_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bstp_set_port_state(struct bstp_port *bp, int state)
{
	if (bp->bp_state == state)
		return;

	bp->bp_state = state;

	switch (bp->bp_state) {
		case BSTP_IFSTATE_DISCARDING:
			DPRINTF("state changed to DISCARDING on %s\n",
			    bp->bp_ifp->if_xname);
			break;

		case BSTP_IFSTATE_LEARNING:
			DPRINTF("state changed to LEARNING on %s\n",
			    bp->bp_ifp->if_xname);

			bstp_timer_start(&bp->bp_forward_delay_timer,
			    bp->bp_protover == BSTP_PROTO_RSTP ?
			    bp->bp_desg_htime : bp->bp_desg_fdelay);
			break;

		case BSTP_IFSTATE_FORWARDING:
			DPRINTF("state changed to FORWARDING on %s\n",
			    bp->bp_ifp->if_xname);

			bstp_timer_stop(&bp->bp_forward_delay_timer);
			/* Record that we enabled forwarding */
			bp->bp_forward_transitions++;
			break;
	}

	/* notify the parent bridge */
	bstp_task_enqueue(&bp->bp_statetask);
}