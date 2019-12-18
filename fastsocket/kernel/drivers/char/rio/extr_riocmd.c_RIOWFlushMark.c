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
struct Port {int /*<<< orphan*/  portSem; int /*<<< orphan*/  MagicFlags; int /*<<< orphan*/  WflushFlag; } ;
struct CmdBlk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAGIC_FLUSH ; 
 int RIOUnUse (unsigned long,struct CmdBlk*) ; 
 int /*<<< orphan*/  rio_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  rio_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int RIOWFlushMark(unsigned long iPortP, struct CmdBlk *CmdBlkP)
{
	struct Port *PortP = (struct Port *) iPortP;
	unsigned long flags;

	rio_spin_lock_irqsave(&PortP->portSem, flags);
	PortP->WflushFlag++;
	PortP->MagicFlags |= MAGIC_FLUSH;
	rio_spin_unlock_irqrestore(&PortP->portSem, flags);
	return RIOUnUse(iPortP, CmdBlkP);
}