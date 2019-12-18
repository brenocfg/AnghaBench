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
typedef  size_t u_int ;
struct ahc_tmode_tstate {struct ahc_tmode_lstate** enabled_luns; } ;
struct ahc_tmode_lstate {int dummy; } ;
struct ahc_softc {int flags; int features; struct ahc_tmode_tstate** enabled_targets; int /*<<< orphan*/ * pending_device; } ;
struct ahc_devinfo {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_BUS_RESET ; 
 size_t AHC_NUM_LUNS ; 
 int AHC_TARGETROLE ; 
 int /*<<< orphan*/  AHC_TRANS_CUR ; 
 int AHC_TWIN ; 
 int AHC_WIDE ; 
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 int /*<<< orphan*/  CAM_SCSI_BUS_RESET ; 
 size_t CAM_TARGET_WILDCARD ; 
 size_t ENAUTOATNP ; 
 size_t ENBUSFREE ; 
 size_t ENRSELI ; 
 size_t ENSCSIRST ; 
 size_t ENSELI ; 
 int /*<<< orphan*/  EVENT_TYPE_BUS_RESET ; 
 int FALSE ; 
 int /*<<< orphan*/  MSG_EXT_WDTR_BUS_8_BIT ; 
 int /*<<< orphan*/  ROLE_UNKNOWN ; 
 int /*<<< orphan*/  SBLKCTL ; 
 int /*<<< orphan*/  SCB_LIST_NULL ; 
 int /*<<< orphan*/  SCSISEQ ; 
 int /*<<< orphan*/  SCSISEQ_TEMPLATE ; 
 size_t SELBUSB ; 
 int /*<<< orphan*/  SIMODE1 ; 
 int TRUE ; 
 int ahc_abort_scbs (struct ahc_softc*,size_t,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_clear_critical_section (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_clear_intstat (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_compile_devinfo (struct ahc_devinfo*,size_t,size_t,int /*<<< orphan*/ ,char,int /*<<< orphan*/ ) ; 
 size_t ahc_inb (struct ahc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_outb (struct ahc_softc*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ahc_pause (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_queue_lstate_event (struct ahc_softc*,struct ahc_tmode_lstate*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_reset_current_bus (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_restart (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_run_qoutfifo (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_run_tqinfifo (struct ahc_softc*,int) ; 
 int /*<<< orphan*/  ahc_send_async (struct ahc_softc*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_send_lstate_events (struct ahc_softc*,struct ahc_tmode_lstate*) ; 
 int /*<<< orphan*/  ahc_set_syncrate (struct ahc_softc*,struct ahc_devinfo*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ahc_set_width (struct ahc_softc*,struct ahc_devinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ahc_unpause (struct ahc_softc*) ; 

int
ahc_reset_channel(struct ahc_softc *ahc, char channel, int initiate_reset)
{
	struct	ahc_devinfo devinfo;
	u_int	initiator, target, max_scsiid;
	u_int	sblkctl;
	u_int	scsiseq;
	u_int	simode1;
	int	found;
	int	restart_needed;
	char	cur_channel;

	ahc->pending_device = NULL;

	ahc_compile_devinfo(&devinfo,
			    CAM_TARGET_WILDCARD,
			    CAM_TARGET_WILDCARD,
			    CAM_LUN_WILDCARD,
			    channel, ROLE_UNKNOWN);
	ahc_pause(ahc);

	/* Make sure the sequencer is in a safe location. */
	ahc_clear_critical_section(ahc);

	/*
	 * Run our command complete fifos to ensure that we perform
	 * completion processing on any commands that 'completed'
	 * before the reset occurred.
	 */
	ahc_run_qoutfifo(ahc);
#ifdef AHC_TARGET_MODE
	/*
	 * XXX - In Twin mode, the tqinfifo may have commands
	 *	 for an unaffected channel in it.  However, if
	 *	 we have run out of ATIO resources to drain that
	 *	 queue, we may not get them all out here.  Further,
	 *	 the blocked transactions for the reset channel
	 *	 should just be killed off, irrespecitve of whether
	 *	 we are blocked on ATIO resources.  Write a routine
	 *	 to compact the tqinfifo appropriately.
	 */
	if ((ahc->flags & AHC_TARGETROLE) != 0) {
		ahc_run_tqinfifo(ahc, /*paused*/TRUE);
	}
#endif

	/*
	 * Reset the bus if we are initiating this reset
	 */
	sblkctl = ahc_inb(ahc, SBLKCTL);
	cur_channel = 'A';
	if ((ahc->features & AHC_TWIN) != 0
	 && ((sblkctl & SELBUSB) != 0))
	    cur_channel = 'B';
	scsiseq = ahc_inb(ahc, SCSISEQ_TEMPLATE);
	if (cur_channel != channel) {
		/* Case 1: Command for another bus is active
		 * Stealthily reset the other bus without
		 * upsetting the current bus.
		 */
		ahc_outb(ahc, SBLKCTL, sblkctl ^ SELBUSB);
		simode1 = ahc_inb(ahc, SIMODE1) & ~(ENBUSFREE|ENSCSIRST);
#ifdef AHC_TARGET_MODE
		/*
		 * Bus resets clear ENSELI, so we cannot
		 * defer re-enabling bus reset interrupts
		 * if we are in target mode.
		 */
		if ((ahc->flags & AHC_TARGETROLE) != 0)
			simode1 |= ENSCSIRST;
#endif
		ahc_outb(ahc, SIMODE1, simode1);
		if (initiate_reset)
			ahc_reset_current_bus(ahc);
		ahc_clear_intstat(ahc);
		ahc_outb(ahc, SCSISEQ, scsiseq & (ENSELI|ENRSELI|ENAUTOATNP));
		ahc_outb(ahc, SBLKCTL, sblkctl);
		restart_needed = FALSE;
	} else {
		/* Case 2: A command from this bus is active or we're idle */
		simode1 = ahc_inb(ahc, SIMODE1) & ~(ENBUSFREE|ENSCSIRST);
#ifdef AHC_TARGET_MODE
		/*
		 * Bus resets clear ENSELI, so we cannot
		 * defer re-enabling bus reset interrupts
		 * if we are in target mode.
		 */
		if ((ahc->flags & AHC_TARGETROLE) != 0)
			simode1 |= ENSCSIRST;
#endif
		ahc_outb(ahc, SIMODE1, simode1);
		if (initiate_reset)
			ahc_reset_current_bus(ahc);
		ahc_clear_intstat(ahc);
		ahc_outb(ahc, SCSISEQ, scsiseq & (ENSELI|ENRSELI|ENAUTOATNP));
		restart_needed = TRUE;
	}

	/*
	 * Clean up all the state information for the
	 * pending transactions on this bus.
	 */
	found = ahc_abort_scbs(ahc, CAM_TARGET_WILDCARD, channel,
			       CAM_LUN_WILDCARD, SCB_LIST_NULL,
			       ROLE_UNKNOWN, CAM_SCSI_BUS_RESET);

	max_scsiid = (ahc->features & AHC_WIDE) ? 15 : 7;

#ifdef AHC_TARGET_MODE
	/*
	 * Send an immediate notify ccb to all target more peripheral
	 * drivers affected by this action.
	 */
	for (target = 0; target <= max_scsiid; target++) {
		struct ahc_tmode_tstate* tstate;
		u_int lun;

		tstate = ahc->enabled_targets[target];
		if (tstate == NULL)
			continue;
		for (lun = 0; lun < AHC_NUM_LUNS; lun++) {
			struct ahc_tmode_lstate* lstate;

			lstate = tstate->enabled_luns[lun];
			if (lstate == NULL)
				continue;

			ahc_queue_lstate_event(ahc, lstate, CAM_TARGET_WILDCARD,
					       EVENT_TYPE_BUS_RESET, /*arg*/0);
			ahc_send_lstate_events(ahc, lstate);
		}
	}
#endif
	/* Notify the XPT that a bus reset occurred */
	ahc_send_async(ahc, devinfo.channel, CAM_TARGET_WILDCARD,
		       CAM_LUN_WILDCARD, AC_BUS_RESET);

	/*
	 * Revert to async/narrow transfers until we renegotiate.
	 */
	for (target = 0; target <= max_scsiid; target++) {

		if (ahc->enabled_targets[target] == NULL)
			continue;
		for (initiator = 0; initiator <= max_scsiid; initiator++) {
			struct ahc_devinfo devinfo;

			ahc_compile_devinfo(&devinfo, target, initiator,
					    CAM_LUN_WILDCARD,
					    channel, ROLE_UNKNOWN);
			ahc_set_width(ahc, &devinfo, MSG_EXT_WDTR_BUS_8_BIT,
				      AHC_TRANS_CUR, /*paused*/TRUE);
			ahc_set_syncrate(ahc, &devinfo, /*syncrate*/NULL,
					 /*period*/0, /*offset*/0,
					 /*ppr_options*/0, AHC_TRANS_CUR,
					 /*paused*/TRUE);
		}
	}

	if (restart_needed)
		ahc_restart(ahc);
	else
		ahc_unpause(ahc);
	return found;
}