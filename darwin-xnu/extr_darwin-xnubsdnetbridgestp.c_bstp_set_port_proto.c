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
struct bstp_state {int /*<<< orphan*/  bs_migration_delay; } ;
struct bstp_port {int bp_path_cost; int bp_protover; int /*<<< orphan*/  bp_flags; int /*<<< orphan*/  bp_migrate_delay_timer; int /*<<< orphan*/  bp_operedge; struct bstp_state* bp_bs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSTP_PORT_CANMIGRATE ; 
#define  BSTP_PROTO_RSTP 129 
#define  BSTP_PROTO_STP 128 
 int /*<<< orphan*/  DPRINTF (char*,int) ; 
 int /*<<< orphan*/  bstp_timer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bstp_timer_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bstp_set_port_proto(struct bstp_port *bp, int proto)
{
	struct bstp_state *bs = bp->bp_bs;

	/* supported protocol versions */
	switch (proto) {
		case BSTP_PROTO_STP:
			/* we can downgrade protocols only */
			bstp_timer_stop(&bp->bp_migrate_delay_timer);
			/* clear unsupported features */
			bp->bp_operedge = 0;
			/* STP compat mode only uses 16 bits of the 32 */
			if (bp->bp_path_cost > 65535)
				bp->bp_path_cost = 65535;
			break;

		case BSTP_PROTO_RSTP:
			bstp_timer_start(&bp->bp_migrate_delay_timer,
			    bs->bs_migration_delay);
			break;

		default:
			DPRINTF("Unsupported STP version %d\n", proto);
			return;
	}

	bp->bp_protover = proto;
	bp->bp_flags &= ~BSTP_PORT_CANMIGRATE;
}