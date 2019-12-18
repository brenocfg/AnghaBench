#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct bstp_state {int /*<<< orphan*/  bs_allsynced; } ;
struct TYPE_8__ {int /*<<< orphan*/  active; } ;
struct TYPE_7__ {int /*<<< orphan*/  active; } ;
struct TYPE_6__ {int /*<<< orphan*/  active; } ;
struct bstp_port {int bp_role; int bp_synced; int bp_agree; int bp_flags; int const bp_state; int bp_proposing; TYPE_1__* bp_ifp; int /*<<< orphan*/  bp_desg_fdelay; int /*<<< orphan*/  bp_desg_htime; int /*<<< orphan*/  bp_protover; TYPE_4__ bp_forward_delay_timer; int /*<<< orphan*/  bp_operedge; TYPE_3__ bp_recent_root_timer; int /*<<< orphan*/  bp_reroot; int /*<<< orphan*/  bp_sync; int /*<<< orphan*/  bp_agreed; int /*<<< orphan*/  bp_desg_max_age; int /*<<< orphan*/  bp_ptp_link; TYPE_4__ bp_edge_delay_timer; TYPE_2__ bp_recent_backup_timer; int /*<<< orphan*/  bp_proposed; } ;
struct TYPE_5__ {int /*<<< orphan*/  if_xname; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSTP_DEFAULT_MIGRATE_DELAY ; 
#define  BSTP_IFSTATE_DISCARDING 134 
 int const BSTP_IFSTATE_FORWARDING ; 
#define  BSTP_IFSTATE_LEARNING 133 
 int BSTP_PORT_DISPUTED ; 
 int BSTP_PORT_NEWINFO ; 
 int /*<<< orphan*/  BSTP_PROTO_RSTP ; 
#define  BSTP_ROLE_ALTERNATE 132 
#define  BSTP_ROLE_BACKUP 131 
#define  BSTP_ROLE_DESIGNATED 130 
#define  BSTP_ROLE_DISABLED 129 
#define  BSTP_ROLE_ROOT 128 
 int /*<<< orphan*/  DPRINTF (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bstp_rerooted (struct bstp_state*,struct bstp_port*) ; 
 int /*<<< orphan*/  bstp_set_all_reroot (struct bstp_state*) ; 
 int /*<<< orphan*/  bstp_set_all_sync (struct bstp_state*) ; 
 int /*<<< orphan*/  bstp_set_port_state (struct bstp_port*,int const) ; 
 int /*<<< orphan*/  bstp_timer_start (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bstp_timer_stop (TYPE_3__*) ; 
 int /*<<< orphan*/  bstp_transmit (struct bstp_state*,struct bstp_port*) ; 

__attribute__((used)) static void
bstp_update_roles(struct bstp_state *bs, struct bstp_port *bp)
{
	switch (bp->bp_role) {
	case BSTP_ROLE_DISABLED:
		/* Clear any flags if set */
		if (bp->bp_sync || !bp->bp_synced || bp->bp_reroot) {
			bp->bp_sync = 0;
			bp->bp_synced = 1;
			bp->bp_reroot = 0;
		}
		break;

	case BSTP_ROLE_ALTERNATE:
	case BSTP_ROLE_BACKUP:
		if ((bs->bs_allsynced && !bp->bp_agree) ||
		    (bp->bp_proposed && bp->bp_agree)) {
			bp->bp_proposed = 0;
			bp->bp_agree = 1;
			bp->bp_flags |= BSTP_PORT_NEWINFO;
			DPRINTF("%s -> ALTERNATE_AGREED\n",
			    bp->bp_ifp->if_xname);
		}

		if (bp->bp_proposed && !bp->bp_agree) {
			bstp_set_all_sync(bs);
			bp->bp_proposed = 0;
			DPRINTF("%s -> ALTERNATE_PROPOSED\n",
			    bp->bp_ifp->if_xname);
		}

		/* Clear any flags if set */
		if (bp->bp_sync || !bp->bp_synced || bp->bp_reroot) {
			bp->bp_sync = 0;
			bp->bp_synced = 1;
			bp->bp_reroot = 0;
			DPRINTF("%s -> ALTERNATE_PORT\n", bp->bp_ifp->if_xname);
		}
		break;

	case BSTP_ROLE_ROOT:
		if (bp->bp_state != BSTP_IFSTATE_FORWARDING && !bp->bp_reroot) {
			bstp_set_all_reroot(bs);
			DPRINTF("%s -> ROOT_REROOT\n", bp->bp_ifp->if_xname);
		}

		if ((bs->bs_allsynced && !bp->bp_agree) ||
		    (bp->bp_proposed && bp->bp_agree)) {
			bp->bp_proposed = 0;
			bp->bp_sync = 0;
			bp->bp_agree = 1;
			bp->bp_flags |= BSTP_PORT_NEWINFO;
			DPRINTF("%s -> ROOT_AGREED\n", bp->bp_ifp->if_xname);
		}

		if (bp->bp_proposed && !bp->bp_agree) {
			bstp_set_all_sync(bs);
			bp->bp_proposed = 0;
			DPRINTF("%s -> ROOT_PROPOSED\n", bp->bp_ifp->if_xname);
		}

		if (bp->bp_state != BSTP_IFSTATE_FORWARDING &&
		    (bp->bp_forward_delay_timer.active == 0 ||
		    (bstp_rerooted(bs, bp) &&
		    bp->bp_recent_backup_timer.active == 0 &&
		    bp->bp_protover == BSTP_PROTO_RSTP))) {
			switch (bp->bp_state) {
			case BSTP_IFSTATE_DISCARDING:
				bstp_set_port_state(bp, BSTP_IFSTATE_LEARNING);
				break;
			case BSTP_IFSTATE_LEARNING:
				bstp_set_port_state(bp,
				    BSTP_IFSTATE_FORWARDING);
				break;
			}
		}

		if (bp->bp_state == BSTP_IFSTATE_FORWARDING && bp->bp_reroot) {
			bp->bp_reroot = 0;
			DPRINTF("%s -> ROOT_REROOTED\n", bp->bp_ifp->if_xname);
		}
		break;

	case BSTP_ROLE_DESIGNATED:
		if (bp->bp_recent_root_timer.active == 0 && bp->bp_reroot) {
			bp->bp_reroot = 0;
			DPRINTF("%s -> DESIGNATED_RETIRED\n",
			    bp->bp_ifp->if_xname);
		}

		if ((bp->bp_state == BSTP_IFSTATE_DISCARDING &&
		    !bp->bp_synced) || (bp->bp_agreed && !bp->bp_synced) ||
		    (bp->bp_operedge && !bp->bp_synced) ||
		    (bp->bp_sync && bp->bp_synced)) {
			bstp_timer_stop(&bp->bp_recent_root_timer);
			bp->bp_synced = 1;
			bp->bp_sync = 0;
			DPRINTF("%s -> DESIGNATED_SYNCED\n",
			    bp->bp_ifp->if_xname);
		}

		if (bp->bp_state != BSTP_IFSTATE_FORWARDING &&
		    !bp->bp_agreed && !bp->bp_proposing &&
		    !bp->bp_operedge) {
			bp->bp_proposing = 1;
			bp->bp_flags |= BSTP_PORT_NEWINFO;
			bstp_timer_start(&bp->bp_edge_delay_timer,
			    (bp->bp_ptp_link ? BSTP_DEFAULT_MIGRATE_DELAY :
			     bp->bp_desg_max_age));
			DPRINTF("%s -> DESIGNATED_PROPOSE\n",
			    bp->bp_ifp->if_xname);
		}

		if (bp->bp_state != BSTP_IFSTATE_FORWARDING &&
		    (bp->bp_forward_delay_timer.active == 0 || bp->bp_agreed ||
		    bp->bp_operedge) &&
		    (bp->bp_recent_root_timer.active == 0 || !bp->bp_reroot) &&
		    !bp->bp_sync) {
#ifdef  BRIDGESTP_DEBUG
			if (bp->bp_agreed)
				DPRINTF("%s -> AGREED\n", bp->bp_ifp->if_xname);
#endif /* BRIDGESTP_DEBUG */
			/*
			 * If agreed|operedge then go straight to forwarding,
			 * otherwise follow discard -> learn -> forward.
			 */
			if (bp->bp_agreed || bp->bp_operedge ||
			    bp->bp_state == BSTP_IFSTATE_LEARNING) {
				bstp_set_port_state(bp,
				    BSTP_IFSTATE_FORWARDING);
				bp->bp_agreed = bp->bp_protover;
			} else if (bp->bp_state == BSTP_IFSTATE_DISCARDING)
				bstp_set_port_state(bp, BSTP_IFSTATE_LEARNING);
		}

		if (((bp->bp_sync && !bp->bp_synced) ||
		    (bp->bp_reroot && bp->bp_recent_root_timer.active) ||
		    (bp->bp_flags & BSTP_PORT_DISPUTED)) && !bp->bp_operedge &&
		    bp->bp_state != BSTP_IFSTATE_DISCARDING) {
			bstp_set_port_state(bp, BSTP_IFSTATE_DISCARDING);
			bp->bp_flags &= ~BSTP_PORT_DISPUTED;
			bstp_timer_start(&bp->bp_forward_delay_timer,
			    bp->bp_protover == BSTP_PROTO_RSTP ?
			    bp->bp_desg_htime : bp->bp_desg_fdelay);
			DPRINTF("%s -> DESIGNATED_DISCARD\n",
			    bp->bp_ifp->if_xname);
		}
		break;
	}

	if (bp->bp_flags & BSTP_PORT_NEWINFO)
		bstp_transmit(bs, bp);
}