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
struct rio_info {struct Port** RIOPortp; } ;
struct Port {int /*<<< orphan*/  portSem; scalar_t__ TxBufferOut; scalar_t__ TxBufferIn; scalar_t__ RxDataStart; scalar_t__ MagicFlags; scalar_t__ WflushFlag; scalar_t__ Mapped; scalar_t__ ParamSem; scalar_t__ CookMode; scalar_t__ ModemState; scalar_t__ ModemLines; scalar_t__ FlushCmdBodge; scalar_t__ PortState; int /*<<< orphan*/  InUse; scalar_t__ State; scalar_t__ Config; } ;

/* Variables and functions */
 int /*<<< orphan*/  NOT_INUSE ; 
 int RIO_PORTS ; 
 int /*<<< orphan*/  rio_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  rio_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int RIOFoadWakeup(struct rio_info *p)
{
	int port;
	struct Port *PortP;
	unsigned long flags;

	for (port = 0; port < RIO_PORTS; port++) {
		PortP = p->RIOPortp[port];

		rio_spin_lock_irqsave(&PortP->portSem, flags);
		PortP->Config = 0;
		PortP->State = 0;
		PortP->InUse = NOT_INUSE;
		PortP->PortState = 0;
		PortP->FlushCmdBodge = 0;
		PortP->ModemLines = 0;
		PortP->ModemState = 0;
		PortP->CookMode = 0;
		PortP->ParamSem = 0;
		PortP->Mapped = 0;
		PortP->WflushFlag = 0;
		PortP->MagicFlags = 0;
		PortP->RxDataStart = 0;
		PortP->TxBufferIn = 0;
		PortP->TxBufferOut = 0;
		rio_spin_unlock_irqrestore(&PortP->portSem, flags);
	}
	return (0);
}