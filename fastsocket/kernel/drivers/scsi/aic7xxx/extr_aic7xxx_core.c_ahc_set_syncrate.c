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
struct ahc_tmode_tstate {int ultraenb; } ;
struct ahc_syncrate {scalar_t__ sxfr_u2; int sxfr; char* rate; } ;
struct ahc_softc {int features; } ;
struct TYPE_6__ {scalar_t__ period; scalar_t__ offset; scalar_t__ ppr_options; } ;
struct TYPE_5__ {scalar_t__ ppr_options; scalar_t__ offset; scalar_t__ period; } ;
struct TYPE_4__ {scalar_t__ ppr_options; scalar_t__ offset; scalar_t__ period; } ;
struct ahc_initiator_tinfo {scalar_t__ scsirate; TYPE_3__ curr; TYPE_2__ goal; TYPE_1__ user; } ;
struct ahc_devinfo {int target; int target_mask; int /*<<< orphan*/  channel; int /*<<< orphan*/  our_scsiid; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_TRANSFER_NEG ; 
 int /*<<< orphan*/  AHC_NEG_TO_GOAL ; 
 scalar_t__ AHC_TRANS_ACTIVE ; 
 scalar_t__ AHC_TRANS_CUR ; 
 scalar_t__ AHC_TRANS_GOAL ; 
 scalar_t__ AHC_TRANS_USER ; 
 int AHC_ULTRA2 ; 
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 scalar_t__ ENABLE_CRC ; 
 scalar_t__ FAST20 ; 
 scalar_t__ MSG_EXT_PPR_DT_REQ ; 
 int /*<<< orphan*/  SCSIOFFSET ; 
 int /*<<< orphan*/  SCSIRATE ; 
 scalar_t__ SINGLE_EDGE ; 
 scalar_t__ SOFS ; 
 scalar_t__ SXFR ; 
 int /*<<< orphan*/  SXFRCTL0 ; 
 scalar_t__ SXFR_ULTRA2 ; 
 int ULTRA_SXFR ; 
 struct ahc_initiator_tinfo* ahc_fetch_transinfo (struct ahc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct ahc_tmode_tstate**) ; 
 scalar_t__ ahc_inb (struct ahc_softc*,int /*<<< orphan*/ ) ; 
 char* ahc_name (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_outb (struct ahc_softc*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ahc_send_async (struct ahc_softc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ahc_update_neg_request (struct ahc_softc*,struct ahc_devinfo*,struct ahc_tmode_tstate*,struct ahc_initiator_tinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_update_pending_scbs (struct ahc_softc*) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  printf (char*,char*,int,...) ; 

void
ahc_set_syncrate(struct ahc_softc *ahc, struct ahc_devinfo *devinfo,
		 const struct ahc_syncrate *syncrate, u_int period,
		 u_int offset, u_int ppr_options, u_int type, int paused)
{
	struct	ahc_initiator_tinfo *tinfo;
	struct	ahc_tmode_tstate *tstate;
	u_int	old_period;
	u_int	old_offset;
	u_int	old_ppr;
	int	active;
	int	update_needed;

	active = (type & AHC_TRANS_ACTIVE) == AHC_TRANS_ACTIVE;
	update_needed = 0;

	if (syncrate == NULL) {
		period = 0;
		offset = 0;
	}

	tinfo = ahc_fetch_transinfo(ahc, devinfo->channel, devinfo->our_scsiid,
				    devinfo->target, &tstate);

	if ((type & AHC_TRANS_USER) != 0) {
		tinfo->user.period = period;
		tinfo->user.offset = offset;
		tinfo->user.ppr_options = ppr_options;
	}

	if ((type & AHC_TRANS_GOAL) != 0) {
		tinfo->goal.period = period;
		tinfo->goal.offset = offset;
		tinfo->goal.ppr_options = ppr_options;
	}

	old_period = tinfo->curr.period;
	old_offset = tinfo->curr.offset;
	old_ppr	   = tinfo->curr.ppr_options;

	if ((type & AHC_TRANS_CUR) != 0
	 && (old_period != period
	  || old_offset != offset
	  || old_ppr != ppr_options)) {
		u_int	scsirate;

		update_needed++;
		scsirate = tinfo->scsirate;
		if ((ahc->features & AHC_ULTRA2) != 0) {

			scsirate &= ~(SXFR_ULTRA2|SINGLE_EDGE|ENABLE_CRC);
			if (syncrate != NULL) {
				scsirate |= syncrate->sxfr_u2;
				if ((ppr_options & MSG_EXT_PPR_DT_REQ) != 0)
					scsirate |= ENABLE_CRC;
				else
					scsirate |= SINGLE_EDGE;
			}
		} else {

			scsirate &= ~(SXFR|SOFS);
			/*
			 * Ensure Ultra mode is set properly for
			 * this target.
			 */
			tstate->ultraenb &= ~devinfo->target_mask;
			if (syncrate != NULL) {
				if (syncrate->sxfr & ULTRA_SXFR) {
					tstate->ultraenb |=
						devinfo->target_mask;
				}
				scsirate |= syncrate->sxfr & SXFR;
				scsirate |= offset & SOFS;
			}
			if (active) {
				u_int sxfrctl0;

				sxfrctl0 = ahc_inb(ahc, SXFRCTL0);
				sxfrctl0 &= ~FAST20;
				if (tstate->ultraenb & devinfo->target_mask)
					sxfrctl0 |= FAST20;
				ahc_outb(ahc, SXFRCTL0, sxfrctl0);
			}
		}
		if (active) {
			ahc_outb(ahc, SCSIRATE, scsirate);
			if ((ahc->features & AHC_ULTRA2) != 0)
				ahc_outb(ahc, SCSIOFFSET, offset);
		}

		tinfo->scsirate = scsirate;
		tinfo->curr.period = period;
		tinfo->curr.offset = offset;
		tinfo->curr.ppr_options = ppr_options;

		ahc_send_async(ahc, devinfo->channel, devinfo->target,
			       CAM_LUN_WILDCARD, AC_TRANSFER_NEG);
		if (bootverbose) {
			if (offset != 0) {
				printf("%s: target %d synchronous at %sMHz%s, "
				       "offset = 0x%x\n", ahc_name(ahc),
				       devinfo->target, syncrate->rate,
				       (ppr_options & MSG_EXT_PPR_DT_REQ)
				       ? " DT" : "", offset);
			} else {
				printf("%s: target %d using "
				       "asynchronous transfers\n",
				       ahc_name(ahc), devinfo->target);
			}
		}
	}

	update_needed += ahc_update_neg_request(ahc, devinfo, tstate,
						tinfo, AHC_NEG_TO_GOAL);

	if (update_needed)
		ahc_update_pending_scbs(ahc);
}