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
typedef  int u_int ;
struct ahd_softc {int pause; int flags; int bugs; size_t cmdcmplt_bucket; int features; int /*<<< orphan*/  (* bus_intr ) (struct ahd_softc*) ;int /*<<< orphan*/  cmdcmplt_total; int /*<<< orphan*/ * cmdcmplt_counts; } ;

/* Variables and functions */
 int AHD_ALL_INTERRUPTS ; 
 int AHD_INTCOLLISION_BUG ; 
 int AHD_REMOVABLE ; 
 int AHD_TARGETROLE ; 
 int /*<<< orphan*/  CLRCMDINT ; 
 int /*<<< orphan*/  CLRINT ; 
 int CMDCMPLT ; 
 int /*<<< orphan*/  FALSE ; 
 int HWERRINT ; 
 int INTEN ; 
 int /*<<< orphan*/  INTSTAT ; 
 int INT_PEND ; 
 scalar_t__ NO_SEQINT ; 
 int PCIINT ; 
 int SCSIINT ; 
 int SEQINT ; 
 int /*<<< orphan*/  SEQINTCODE ; 
 int SPLTINT ; 
 scalar_t__ ahd_check_cmdcmpltqueues (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_flush_device_writes (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_handle_hwerrint (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_handle_scsiint (struct ahd_softc*,int) ; 
 int /*<<< orphan*/  ahd_handle_seqint (struct ahd_softc*,int) ; 
 scalar_t__ ahd_inb (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ ahd_is_paused (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_outb (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_run_qoutfifo (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_run_tqinfifo (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ahd_softc*) ; 

int
ahd_intr(struct ahd_softc *ahd)
{
	u_int	intstat;

	if ((ahd->pause & INTEN) == 0) {
		/*
		 * Our interrupt is not enabled on the chip
		 * and may be disabled for re-entrancy reasons,
		 * so just return.  This is likely just a shared
		 * interrupt.
		 */
		return (0);
	}

	/*
	 * Instead of directly reading the interrupt status register,
	 * infer the cause of the interrupt by checking our in-core
	 * completion queues.  This avoids a costly PCI bus read in
	 * most cases.
	 */
	if ((ahd->flags & AHD_ALL_INTERRUPTS) == 0
	 && (ahd_check_cmdcmpltqueues(ahd) != 0))
		intstat = CMDCMPLT;
	else
		intstat = ahd_inb(ahd, INTSTAT);

	if ((intstat & INT_PEND) == 0)
		return (0);

	if (intstat & CMDCMPLT) {
		ahd_outb(ahd, CLRINT, CLRCMDINT);

		/*
		 * Ensure that the chip sees that we've cleared
		 * this interrupt before we walk the output fifo.
		 * Otherwise, we may, due to posted bus writes,
		 * clear the interrupt after we finish the scan,
		 * and after the sequencer has added new entries
		 * and asserted the interrupt again.
		 */
		if ((ahd->bugs & AHD_INTCOLLISION_BUG) != 0) {
			if (ahd_is_paused(ahd)) {
				/*
				 * Potentially lost SEQINT.
				 * If SEQINTCODE is non-zero,
				 * simulate the SEQINT.
				 */
				if (ahd_inb(ahd, SEQINTCODE) != NO_SEQINT)
					intstat |= SEQINT;
			}
		} else {
			ahd_flush_device_writes(ahd);
		}
		ahd_run_qoutfifo(ahd);
		ahd->cmdcmplt_counts[ahd->cmdcmplt_bucket]++;
		ahd->cmdcmplt_total++;
#ifdef AHD_TARGET_MODE
		if ((ahd->flags & AHD_TARGETROLE) != 0)
			ahd_run_tqinfifo(ahd, /*paused*/FALSE);
#endif
	}

	/*
	 * Handle statuses that may invalidate our cached
	 * copy of INTSTAT separately.
	 */
	if (intstat == 0xFF && (ahd->features & AHD_REMOVABLE) != 0) {
		/* Hot eject.  Do nothing */
	} else if (intstat & HWERRINT) {
		ahd_handle_hwerrint(ahd);
	} else if ((intstat & (PCIINT|SPLTINT)) != 0) {
		ahd->bus_intr(ahd);
	} else {

		if ((intstat & SEQINT) != 0)
			ahd_handle_seqint(ahd, intstat);

		if ((intstat & SCSIINT) != 0)
			ahd_handle_scsiint(ahd, intstat);
	}
	return (1);
}