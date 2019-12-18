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
struct bstp_state {scalar_t__ bs_allsynced; } ;
struct bstp_port {int /*<<< orphan*/  bp_flags; int /*<<< orphan*/  bp_infois; int /*<<< orphan*/  bp_desg_htime; int /*<<< orphan*/  bp_port_htime; int /*<<< orphan*/  bp_desg_fdelay; int /*<<< orphan*/  bp_port_fdelay; int /*<<< orphan*/  bp_desg_max_age; int /*<<< orphan*/  bp_port_max_age; int /*<<< orphan*/  bp_desg_msg_age; int /*<<< orphan*/  bp_port_msg_age; int /*<<< orphan*/  bp_desg_pv; int /*<<< orphan*/  bp_port_pv; scalar_t__ bp_synced; scalar_t__ bp_agreed; scalar_t__ bp_proposed; scalar_t__ bp_proposing; struct bstp_state* bp_bs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSTP_INFO_MINE ; 
 int /*<<< orphan*/  BSTP_PORT_NEWINFO ; 
 int /*<<< orphan*/  bstp_pdu_bettersame (struct bstp_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bstp_update_info(struct bstp_port *bp)
{
	struct bstp_state *bs = bp->bp_bs;

	bp->bp_proposing = 0;
	bp->bp_proposed = 0;

	if (bp->bp_agreed && !bstp_pdu_bettersame(bp, BSTP_INFO_MINE))
		bp->bp_agreed = 0;

	if (bp->bp_synced && !bp->bp_agreed) {
		bp->bp_synced = 0;
		bs->bs_allsynced = 0;
	}

	/* copy the designated pv to the port */
	bp->bp_port_pv = bp->bp_desg_pv;
	bp->bp_port_msg_age = bp->bp_desg_msg_age;
	bp->bp_port_max_age = bp->bp_desg_max_age;
	bp->bp_port_fdelay = bp->bp_desg_fdelay;
	bp->bp_port_htime = bp->bp_desg_htime;
	bp->bp_infois = BSTP_INFO_MINE;

	/* Set transmit flag but do not immediately send */
	bp->bp_flags |= BSTP_PORT_NEWINFO;
}