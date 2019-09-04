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
struct bstp_state {scalar_t__ bs_allsynced; } ;
struct bstp_port {int bp_role; int bp_desg_max_age; int bp_desg_htime; int bp_desg_fdelay; int bp_synced; int /*<<< orphan*/  bp_agree; int /*<<< orphan*/  bp_hello_timer; TYPE_1__* bp_ifp; scalar_t__ bp_proposing; int /*<<< orphan*/  bp_recent_root_timer; int /*<<< orphan*/  bp_reroot; int /*<<< orphan*/  bp_sync; int /*<<< orphan*/  bp_forward_delay_timer; int /*<<< orphan*/  bp_recent_backup_timer; struct bstp_state* bp_bs; } ;
struct TYPE_2__ {int /*<<< orphan*/  if_xname; } ;

/* Variables and functions */
 int BSTP_DEFAULT_FORWARD_DELAY ; 
 int /*<<< orphan*/  BSTP_IFSTATE_DISCARDING ; 
#define  BSTP_ROLE_ALTERNATE 132 
#define  BSTP_ROLE_BACKUP 131 
#define  BSTP_ROLE_DESIGNATED 130 
#define  BSTP_ROLE_DISABLED 129 
#define  BSTP_ROLE_ROOT 128 
 int /*<<< orphan*/  DPRINTF (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bstp_set_port_state (struct bstp_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bstp_timer_latch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bstp_timer_start (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bstp_timer_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bstp_update_tc (struct bstp_port*) ; 

__attribute__((used)) static void
bstp_set_port_role(struct bstp_port *bp, int role)
{
	struct bstp_state *bs = bp->bp_bs;

	if (bp->bp_role == role)
		return;

	/* perform pre-change tasks */
	switch (bp->bp_role) {
		case BSTP_ROLE_DISABLED:
			bstp_timer_start(&bp->bp_forward_delay_timer,
			    bp->bp_desg_max_age);
			break;

		case BSTP_ROLE_BACKUP:
			bstp_timer_start(&bp->bp_recent_backup_timer,
			    bp->bp_desg_htime * 2);
			/* fall through */
		case BSTP_ROLE_ALTERNATE:
			bstp_timer_start(&bp->bp_forward_delay_timer,
			    bp->bp_desg_fdelay);
			bp->bp_sync = 0;
			bp->bp_synced = 1;
			bp->bp_reroot = 0;
			break;

		case BSTP_ROLE_ROOT:
			bstp_timer_start(&bp->bp_recent_root_timer,
			    BSTP_DEFAULT_FORWARD_DELAY);
			break;
	}

	bp->bp_role = role;
	/* clear values not carried between roles */
	bp->bp_proposing = 0;
	bs->bs_allsynced = 0;

	/* initialise the new role */
	switch (bp->bp_role) {
		case BSTP_ROLE_DISABLED:
		case BSTP_ROLE_ALTERNATE:
		case BSTP_ROLE_BACKUP:
			DPRINTF("%s role -> ALT/BACK/DISABLED\n",
			    bp->bp_ifp->if_xname);
			bstp_set_port_state(bp, BSTP_IFSTATE_DISCARDING);
			bstp_timer_stop(&bp->bp_recent_root_timer);
			bstp_timer_latch(&bp->bp_forward_delay_timer);
			bp->bp_sync = 0;
			bp->bp_synced = 1;
			bp->bp_reroot = 0;
			break;

		case BSTP_ROLE_ROOT:
			DPRINTF("%s role -> ROOT\n",
			    bp->bp_ifp->if_xname);
			bstp_set_port_state(bp, BSTP_IFSTATE_DISCARDING);
			bstp_timer_latch(&bp->bp_recent_root_timer);
			bp->bp_proposing = 0;
			break;

		case BSTP_ROLE_DESIGNATED:
			DPRINTF("%s role -> DESIGNATED\n",
			    bp->bp_ifp->if_xname);
			bstp_timer_start(&bp->bp_hello_timer,
			    bp->bp_desg_htime);
			bp->bp_agree = 0;
			break;
	}

	/* let the TC state know that the role changed */
	bstp_update_tc(bp);
}