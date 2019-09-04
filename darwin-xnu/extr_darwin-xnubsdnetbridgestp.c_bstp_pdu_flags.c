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
struct TYPE_2__ {scalar_t__ active; } ;
struct bstp_port {int bp_state; int bp_role; int bp_protover; scalar_t__ bp_tc_ack; TYPE_1__ bp_tc_timer; scalar_t__ bp_agree; scalar_t__ bp_proposing; } ;

/* Variables and functions */
#define  BSTP_IFSTATE_FORWARDING 135 
#define  BSTP_IFSTATE_LEARNING 134 
 int BSTP_PDU_F_A ; 
 int BSTP_PDU_F_ALT ; 
 int BSTP_PDU_F_DESG ; 
 int BSTP_PDU_F_F ; 
 int BSTP_PDU_F_L ; 
 int BSTP_PDU_F_P ; 
 int BSTP_PDU_F_ROOT ; 
 int BSTP_PDU_F_TC ; 
 int BSTP_PDU_F_TCA ; 
 int BSTP_PDU_PRSHIFT ; 
 int BSTP_PDU_RSTPMASK ; 
 int BSTP_PDU_STPMASK ; 
#define  BSTP_PROTO_RSTP 133 
#define  BSTP_PROTO_STP 132 
#define  BSTP_ROLE_ALTERNATE 131 
#define  BSTP_ROLE_BACKUP 130 
#define  BSTP_ROLE_DESIGNATED 129 
#define  BSTP_ROLE_ROOT 128 

__attribute__((used)) static int
bstp_pdu_flags(struct bstp_port *bp)
{
	int flags = 0;

	if (bp->bp_proposing && bp->bp_state != BSTP_IFSTATE_FORWARDING)
		flags |= BSTP_PDU_F_P;

	if (bp->bp_agree)
		flags |= BSTP_PDU_F_A;

	if (bp->bp_tc_timer.active)
		flags |= BSTP_PDU_F_TC;

	if (bp->bp_tc_ack)
		flags |= BSTP_PDU_F_TCA;

	switch (bp->bp_state) {
		case BSTP_IFSTATE_LEARNING:
			flags |= BSTP_PDU_F_L;
			break;

		case BSTP_IFSTATE_FORWARDING:
			flags |= (BSTP_PDU_F_L | BSTP_PDU_F_F);
			break;
	}

	switch (bp->bp_role) {
		case BSTP_ROLE_ROOT:
			flags |=
				(BSTP_PDU_F_ROOT << BSTP_PDU_PRSHIFT);
			break;

		case BSTP_ROLE_ALTERNATE:
		case BSTP_ROLE_BACKUP:	/* fall through */
			flags |=
				(BSTP_PDU_F_ALT << BSTP_PDU_PRSHIFT);
			break;

		case BSTP_ROLE_DESIGNATED:
			flags |=
				(BSTP_PDU_F_DESG << BSTP_PDU_PRSHIFT);
			break;
	}

	/* Strip off unused flags in either mode */
	switch (bp->bp_protover) {
		case BSTP_PROTO_STP:
			flags &= BSTP_PDU_STPMASK;
			break;
		case BSTP_PROTO_RSTP:
			flags &= BSTP_PDU_RSTPMASK;
			break;
	}
	return (flags);
}