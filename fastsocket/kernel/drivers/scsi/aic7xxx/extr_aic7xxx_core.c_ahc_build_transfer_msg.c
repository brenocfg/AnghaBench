#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct ahc_tmode_tstate {int dummy; } ;
struct ahc_syncrate {int dummy; } ;
struct ahc_softc {int features; } ;
struct TYPE_4__ {scalar_t__ period; scalar_t__ offset; scalar_t__ ppr_options; scalar_t__ width; } ;
struct TYPE_3__ {scalar_t__ width; scalar_t__ offset; scalar_t__ period; } ;
struct ahc_initiator_tinfo {TYPE_2__ goal; TYPE_1__ curr; } ;
struct ahc_devinfo {int /*<<< orphan*/  role; int /*<<< orphan*/  target; int /*<<< orphan*/  our_scsiid; int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int AHC_WIDE ; 
 scalar_t__ MSG_EXT_WDTR_BUS_8_BIT ; 
 int /*<<< orphan*/  ROLE_TARGET ; 
 int /*<<< orphan*/  ahc_construct_ppr (struct ahc_softc*,struct ahc_devinfo*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ahc_construct_sdtr (struct ahc_softc*,struct ahc_devinfo*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ahc_construct_wdtr (struct ahc_softc*,struct ahc_devinfo*,scalar_t__) ; 
 struct ahc_syncrate* ahc_devlimited_syncrate (struct ahc_softc*,struct ahc_initiator_tinfo*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 struct ahc_initiator_tinfo* ahc_fetch_transinfo (struct ahc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ahc_tmode_tstate**) ; 
 int /*<<< orphan*/  ahc_print_devinfo (struct ahc_softc*,struct ahc_devinfo*) ; 
 int /*<<< orphan*/  ahc_validate_offset (struct ahc_softc*,struct ahc_initiator_tinfo*,struct ahc_syncrate const*,scalar_t__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
ahc_build_transfer_msg(struct ahc_softc *ahc, struct ahc_devinfo *devinfo)
{
	/*
	 * We need to initiate transfer negotiations.
	 * If our current and goal settings are identical,
	 * we want to renegotiate due to a check condition.
	 */
	struct	ahc_initiator_tinfo *tinfo;
	struct	ahc_tmode_tstate *tstate;
	const struct ahc_syncrate *rate;
	int	dowide;
	int	dosync;
	int	doppr;
	u_int	period;
	u_int	ppr_options;
	u_int	offset;

	tinfo = ahc_fetch_transinfo(ahc, devinfo->channel, devinfo->our_scsiid,
				    devinfo->target, &tstate);
	/*
	 * Filter our period based on the current connection.
	 * If we can't perform DT transfers on this segment (not in LVD
	 * mode for instance), then our decision to issue a PPR message
	 * may change.
	 */
	period = tinfo->goal.period;
	offset = tinfo->goal.offset;
	ppr_options = tinfo->goal.ppr_options;
	/* Target initiated PPR is not allowed in the SCSI spec */
	if (devinfo->role == ROLE_TARGET)
		ppr_options = 0;
	rate = ahc_devlimited_syncrate(ahc, tinfo, &period,
				       &ppr_options, devinfo->role);
	dowide = tinfo->curr.width != tinfo->goal.width;
	dosync = tinfo->curr.offset != offset || tinfo->curr.period != period;
	/*
	 * Only use PPR if we have options that need it, even if the device
	 * claims to support it.  There might be an expander in the way
	 * that doesn't.
	 */
	doppr = ppr_options != 0;

	if (!dowide && !dosync && !doppr) {
		dowide = tinfo->goal.width != MSG_EXT_WDTR_BUS_8_BIT;
		dosync = tinfo->goal.offset != 0;
	}

	if (!dowide && !dosync && !doppr) {
		/*
		 * Force async with a WDTR message if we have a wide bus,
		 * or just issue an SDTR with a 0 offset.
		 */
		if ((ahc->features & AHC_WIDE) != 0)
			dowide = 1;
		else
			dosync = 1;

		if (bootverbose) {
			ahc_print_devinfo(ahc, devinfo);
			printf("Ensuring async\n");
		}
	}

	/* Target initiated PPR is not allowed in the SCSI spec */
	if (devinfo->role == ROLE_TARGET)
		doppr = 0;

	/*
	 * Both the PPR message and SDTR message require the
	 * goal syncrate to be limited to what the target device
	 * is capable of handling (based on whether an LVD->SE
	 * expander is on the bus), so combine these two cases.
	 * Regardless, guarantee that if we are using WDTR and SDTR
	 * messages that WDTR comes first.
	 */
	if (doppr || (dosync && !dowide)) {

		offset = tinfo->goal.offset;
		ahc_validate_offset(ahc, tinfo, rate, &offset,
				    doppr ? tinfo->goal.width
					  : tinfo->curr.width,
				    devinfo->role);
		if (doppr) {
			ahc_construct_ppr(ahc, devinfo, period, offset,
					  tinfo->goal.width, ppr_options);
		} else {
			ahc_construct_sdtr(ahc, devinfo, period, offset);
		}
	} else {
		ahc_construct_wdtr(ahc, devinfo, tinfo->goal.width);
	}
}