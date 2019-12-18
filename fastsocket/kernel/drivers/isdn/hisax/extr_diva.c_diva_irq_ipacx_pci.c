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
typedef  int /*<<< orphan*/  u_long ;
typedef  int u_char ;
struct TYPE_3__ {scalar_t__ pci_cfg; } ;
struct TYPE_4__ {TYPE_1__ diva; } ;
struct IsdnCardState {int /*<<< orphan*/  lock; TYPE_2__ hw; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int PITA_INT0_STATUS ; 
 int /*<<< orphan*/  interrupt_ipacx (struct IsdnCardState*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t
diva_irq_ipacx_pci(int intno, void *dev_id)
{
	struct IsdnCardState *cs = dev_id;
	u_char val;
	u_char *cfg;
	u_long flags;

	spin_lock_irqsave(&cs->lock, flags);
	cfg = (u_char *) cs->hw.diva.pci_cfg;
	val = *cfg;
	if (!(val &PITA_INT0_STATUS)) {
		spin_unlock_irqrestore(&cs->lock, flags);
		return IRQ_NONE; // other shared IRQ
	}
 	interrupt_ipacx(cs);      // handler for chip
	*cfg = PITA_INT0_STATUS;  // Reset PLX interrupt
	spin_unlock_irqrestore(&cs->lock, flags);
	return IRQ_HANDLED;
}