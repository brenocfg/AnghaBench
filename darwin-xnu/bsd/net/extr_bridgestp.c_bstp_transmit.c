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
struct bstp_state {scalar_t__ bs_running; scalar_t__ bs_txholdcount; } ;
struct TYPE_2__ {scalar_t__ active; } ;
struct bstp_port {scalar_t__ bp_txcount; scalar_t__ bp_protover; int bp_role; int /*<<< orphan*/  bp_flags; int /*<<< orphan*/  bp_desg_htime; TYPE_1__ bp_hello_timer; scalar_t__ bp_tc_ack; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSTP_PORT_NEWINFO ; 
 scalar_t__ BSTP_PROTO_RSTP ; 
#define  BSTP_ROLE_DESIGNATED 129 
#define  BSTP_ROLE_ROOT 128 
 int /*<<< orphan*/  bstp_hello_timer_expiry (struct bstp_state*,struct bstp_port*) ; 
 int /*<<< orphan*/  bstp_timer_start (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bstp_transmit_bpdu (struct bstp_state*,struct bstp_port*) ; 
 int /*<<< orphan*/  bstp_transmit_tcn (struct bstp_state*,struct bstp_port*) ; 

__attribute__((used)) static void
bstp_transmit(struct bstp_state *bs, struct bstp_port *bp)
{
	if (bs->bs_running == 0)
		return;

	/*
	 * a PDU can only be sent if we have tx quota left and the
	 * hello timer is running.
	 */
	if (bp->bp_hello_timer.active == 0) {
		/* Test if it needs to be reset */
		bstp_hello_timer_expiry(bs, bp);
		return;
	}
	if (bp->bp_txcount > bs->bs_txholdcount)
		/* Ran out of karma */
		return;

	if (bp->bp_protover == BSTP_PROTO_RSTP) {
		bstp_transmit_bpdu(bs, bp);
		bp->bp_tc_ack = 0;
	} else { /* STP */
		switch (bp->bp_role) {
			case BSTP_ROLE_DESIGNATED:
				bstp_transmit_bpdu(bs, bp);
				bp->bp_tc_ack = 0;
				break;

			case BSTP_ROLE_ROOT:
				bstp_transmit_tcn(bs, bp);
				break;
		}
	}
	bstp_timer_start(&bp->bp_hello_timer, bp->bp_desg_htime);
	bp->bp_flags &= ~BSTP_PORT_NEWINFO;
}