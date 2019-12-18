#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct ahd_tmode_tstate {int dummy; } ;
struct ahd_softc {scalar_t__ msg_type; int msg_flags; } ;
struct TYPE_6__ {scalar_t__ period; scalar_t__ offset; scalar_t__ ppr_options; } ;
struct TYPE_5__ {scalar_t__ ppr_options; scalar_t__ offset; scalar_t__ period; } ;
struct TYPE_4__ {scalar_t__ ppr_options; scalar_t__ offset; scalar_t__ period; } ;
struct ahd_initiator_tinfo {TYPE_3__ curr; TYPE_2__ goal; TYPE_1__ user; } ;
struct ahd_devinfo {int target; int /*<<< orphan*/  channel; int /*<<< orphan*/  our_scsiid; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_TRANSFER_NEG ; 
 int /*<<< orphan*/  AHD_NEG_TO_GOAL ; 
 int AHD_SHOW_MESSAGES ; 
 scalar_t__ AHD_TRANS_ACTIVE ; 
 scalar_t__ AHD_TRANS_CUR ; 
 scalar_t__ AHD_TRANS_GOAL ; 
 scalar_t__ AHD_TRANS_USER ; 
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 scalar_t__ MSG_EXT_PPR_DT_REQ ; 
 scalar_t__ MSG_EXT_PPR_IU_REQ ; 
 scalar_t__ MSG_EXT_PPR_QAS_REQ ; 
 scalar_t__ MSG_EXT_PPR_RD_STRM ; 
 scalar_t__ MSG_EXT_PPR_RTI ; 
 int MSG_FLAG_EXPECT_PPR_BUSFREE ; 
 int MSG_FLAG_IU_REQ_CHANGED ; 
 scalar_t__ MSG_TYPE_NONE ; 
 int ahd_debug ; 
 struct ahd_initiator_tinfo* ahd_fetch_transinfo (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct ahd_tmode_tstate**) ; 
 char* ahd_name (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_pause (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_print_devinfo (struct ahd_softc*,struct ahd_devinfo*) ; 
 int /*<<< orphan*/  ahd_send_async (struct ahd_softc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_unpause (struct ahd_softc*) ; 
 scalar_t__ ahd_update_neg_request (struct ahd_softc*,struct ahd_devinfo*,struct ahd_tmode_tstate*,struct ahd_initiator_tinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_update_neg_table (struct ahd_softc*,struct ahd_devinfo*,TYPE_3__*) ; 
 int /*<<< orphan*/  ahd_update_pending_scbs (struct ahd_softc*) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void
ahd_set_syncrate(struct ahd_softc *ahd, struct ahd_devinfo *devinfo,
		 u_int period, u_int offset, u_int ppr_options,
		 u_int type, int paused)
{
	struct	ahd_initiator_tinfo *tinfo;
	struct	ahd_tmode_tstate *tstate;
	u_int	old_period;
	u_int	old_offset;
	u_int	old_ppr;
	int	active;
	int	update_needed;

	active = (type & AHD_TRANS_ACTIVE) == AHD_TRANS_ACTIVE;
	update_needed = 0;

	if (period == 0 || offset == 0) {
		period = 0;
		offset = 0;
	}

	tinfo = ahd_fetch_transinfo(ahd, devinfo->channel, devinfo->our_scsiid,
				    devinfo->target, &tstate);

	if ((type & AHD_TRANS_USER) != 0) {
		tinfo->user.period = period;
		tinfo->user.offset = offset;
		tinfo->user.ppr_options = ppr_options;
	}

	if ((type & AHD_TRANS_GOAL) != 0) {
		tinfo->goal.period = period;
		tinfo->goal.offset = offset;
		tinfo->goal.ppr_options = ppr_options;
	}

	old_period = tinfo->curr.period;
	old_offset = tinfo->curr.offset;
	old_ppr	   = tinfo->curr.ppr_options;

	if ((type & AHD_TRANS_CUR) != 0
	 && (old_period != period
	  || old_offset != offset
	  || old_ppr != ppr_options)) {

		update_needed++;

		tinfo->curr.period = period;
		tinfo->curr.offset = offset;
		tinfo->curr.ppr_options = ppr_options;

		ahd_send_async(ahd, devinfo->channel, devinfo->target,
			       CAM_LUN_WILDCARD, AC_TRANSFER_NEG);
		if (bootverbose) {
			if (offset != 0) {
				int options;

				printf("%s: target %d synchronous with "
				       "period = 0x%x, offset = 0x%x",
				       ahd_name(ahd), devinfo->target,
				       period, offset);
				options = 0;
				if ((ppr_options & MSG_EXT_PPR_RD_STRM) != 0) {
					printf("(RDSTRM");
					options++;
				}
				if ((ppr_options & MSG_EXT_PPR_DT_REQ) != 0) {
					printf("%s", options ? "|DT" : "(DT");
					options++;
				}
				if ((ppr_options & MSG_EXT_PPR_IU_REQ) != 0) {
					printf("%s", options ? "|IU" : "(IU");
					options++;
				}
				if ((ppr_options & MSG_EXT_PPR_RTI) != 0) {
					printf("%s", options ? "|RTI" : "(RTI");
					options++;
				}
				if ((ppr_options & MSG_EXT_PPR_QAS_REQ) != 0) {
					printf("%s", options ? "|QAS" : "(QAS");
					options++;
				}
				if (options != 0)
					printf(")\n");
				else
					printf("\n");
			} else {
				printf("%s: target %d using "
				       "asynchronous transfers%s\n",
				       ahd_name(ahd), devinfo->target,
				       (ppr_options & MSG_EXT_PPR_QAS_REQ) != 0
				     ?  "(QAS)" : "");
			}
		}
	}
	/*
	 * Always refresh the neg-table to handle the case of the
	 * sequencer setting the ENATNO bit for a MK_MESSAGE request.
	 * We will always renegotiate in that case if this is a
	 * packetized request.  Also manage the busfree expected flag
	 * from this common routine so that we catch changes due to
	 * WDTR or SDTR messages.
	 */
	if ((type & AHD_TRANS_CUR) != 0) {
		if (!paused)
			ahd_pause(ahd);
		ahd_update_neg_table(ahd, devinfo, &tinfo->curr);
		if (!paused)
			ahd_unpause(ahd);
		if (ahd->msg_type != MSG_TYPE_NONE) {
			if ((old_ppr & MSG_EXT_PPR_IU_REQ)
			 != (ppr_options & MSG_EXT_PPR_IU_REQ)) {
#ifdef AHD_DEBUG
				if ((ahd_debug & AHD_SHOW_MESSAGES) != 0) {
					ahd_print_devinfo(ahd, devinfo);
					printf("Expecting IU Change busfree\n");
				}
#endif
				ahd->msg_flags |= MSG_FLAG_EXPECT_PPR_BUSFREE
					       |  MSG_FLAG_IU_REQ_CHANGED;
			}
			if ((old_ppr & MSG_EXT_PPR_IU_REQ) != 0) {
#ifdef AHD_DEBUG
				if ((ahd_debug & AHD_SHOW_MESSAGES) != 0)
					printf("PPR with IU_REQ outstanding\n");
#endif
				ahd->msg_flags |= MSG_FLAG_EXPECT_PPR_BUSFREE;
			}
		}
	}

	update_needed += ahd_update_neg_request(ahd, devinfo, tstate,
						tinfo, AHD_NEG_TO_GOAL);

	if (update_needed && active)
		ahd_update_pending_scbs(ahd);
}