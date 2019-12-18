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
struct Scsi_Host {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int service; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLRBITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMACNTRL0 ; 
 int /*<<< orphan*/  DMASTAT ; 
 int /*<<< orphan*/  DO_LOCK (unsigned long) ; 
 int /*<<< orphan*/  DO_UNLOCK (unsigned long) ; 
 unsigned char GETPORT (int /*<<< orphan*/ ) ; 
 TYPE_1__* HOSTDATA (struct Scsi_Host*) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTEN ; 
 int /*<<< orphan*/  INTSTAT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  REV ; 
 scalar_t__ TESTLO (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aha152x_tq ; 
 int /*<<< orphan*/  run ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t intr(int irqno, void *dev_id)
{
	struct Scsi_Host *shpnt = dev_id;
	unsigned long flags;
	unsigned char rev, dmacntrl0;

	/*
	 * Read a couple of registers that are known to not be all 1's. If
	 * we read all 1's (-1), that means that either:
	 *
	 * a. The host adapter chip has gone bad, and we cannot control it,
	 *	OR
	 * b. The host adapter is a PCMCIA card that has been ejected
	 *
	 * In either case, we cannot do anything with the host adapter at
	 * this point in time. So just ignore the interrupt and return.
	 * In the latter case, the interrupt might actually be meant for
	 * someone else sharing this IRQ, and that driver will handle it.
	 */
	rev = GETPORT(REV);
	dmacntrl0 = GETPORT(DMACNTRL0);
	if ((rev == 0xFF) && (dmacntrl0 == 0xFF))
		return IRQ_NONE;

	if( TESTLO(DMASTAT, INTSTAT) )
		return IRQ_NONE;	

	/* no more interrupts from the controller, while we're busy.
	   INTEN is restored by the BH handler */
	CLRBITS(DMACNTRL0, INTEN);

	DO_LOCK(flags);
	if( HOSTDATA(shpnt)->service==0 ) {
		HOSTDATA(shpnt)->service=1;

		/* Poke the BH handler */
		INIT_WORK(&aha152x_tq, run);
		schedule_work(&aha152x_tq);
	}
	DO_UNLOCK(flags);

	return IRQ_HANDLED;
}