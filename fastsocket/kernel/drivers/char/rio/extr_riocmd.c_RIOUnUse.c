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
struct Port {scalar_t__ InUse; int /*<<< orphan*/  portSem; TYPE_2__* HostP; } ;
struct CmdBlk {int dummy; } ;
struct TYPE_4__ {TYPE_1__* ParmMapP; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_intr; } ;

/* Variables and functions */
 scalar_t__ NOT_INUSE ; 
 int /*<<< orphan*/  RIO_DEBUG_CMD ; 
 int /*<<< orphan*/  rio_dprintk (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rio_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  rio_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writew (int,int /*<<< orphan*/ *) ; 

int RIOUnUse(unsigned long iPortP, struct CmdBlk *CmdBlkP)
{
	struct Port *PortP = (struct Port *) iPortP;
	unsigned long flags;

	rio_spin_lock_irqsave(&PortP->portSem, flags);

	rio_dprintk(RIO_DEBUG_CMD, "Decrement in use count for port\n");

	if (PortP->InUse) {
		if (--PortP->InUse != NOT_INUSE) {
			rio_spin_unlock_irqrestore(&PortP->portSem, flags);
			return 0;
		}
	}
	/*
	 ** While PortP->InUse is set (i.e. a preemptive command has been sent to
	 ** the RTA and is awaiting completion), any transmit data is prevented from
	 ** being transferred from the write queue into the transmit packets
	 ** (add_transmit) and no furthur transmit interrupt will be sent for that
	 ** data. The next interrupt will occur up to 500ms later (RIOIntr is called
	 ** twice a second as a saftey measure). This was the case when kermit was
	 ** used to send data into a RIO port. After each packet was sent, TCFLSH
	 ** was called to flush the read queue preemptively. PortP->InUse was
	 ** incremented, thereby blocking the 6 byte acknowledgement packet
	 ** transmitted back. This acknowledgment hung around for 500ms before
	 ** being sent, thus reducing input performance substantially!.
	 ** When PortP->InUse becomes NOT_INUSE, we must ensure that any data
	 ** hanging around in the transmit buffer is sent immediately.
	 */
	writew(1, &PortP->HostP->ParmMapP->tx_intr);
	/* What to do here ..
	   wakeup( (caddr_t)&(PortP->InUse) );
	 */
	rio_spin_unlock_irqrestore(&PortP->portSem, flags);
	return 0;
}