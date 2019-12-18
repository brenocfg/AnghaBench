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
struct bstp_state {scalar_t__ bs_root_fdelay; scalar_t__ bs_root_max_age; } ;
struct TYPE_2__ {scalar_t__ active; } ;
struct bstp_port {int bp_protover; TYPE_1__ bp_tc_timer; int /*<<< orphan*/  bp_flags; scalar_t__ bp_desg_htime; struct bstp_state* bp_bs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSTP_PORT_NEWINFO ; 
#define  BSTP_PROTO_RSTP 129 
#define  BSTP_PROTO_STP 128 
 scalar_t__ BSTP_TICK_VAL ; 
 int /*<<< orphan*/  bstp_timer_start (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static void
bstp_set_timer_tc(struct bstp_port *bp)
{
	struct bstp_state *bs = bp->bp_bs;

	if (bp->bp_tc_timer.active)
		return;

	switch (bp->bp_protover) {
		case BSTP_PROTO_RSTP:
			bstp_timer_start(&bp->bp_tc_timer,
			    bp->bp_desg_htime + BSTP_TICK_VAL);
			bp->bp_flags |= BSTP_PORT_NEWINFO;
			break;

		case BSTP_PROTO_STP:
			bstp_timer_start(&bp->bp_tc_timer,
			    bs->bs_root_max_age + bs->bs_root_fdelay);
			break;
	}
}