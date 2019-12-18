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
struct TYPE_3__ {unsigned char ToPcInt; unsigned char volatile ToPcIntMetro; unsigned char volatile ToHyInt; } ;
typedef  TYPE_1__ tErgDpram ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int /*<<< orphan*/  hysdn_lock; int /*<<< orphan*/  irq_queue; int /*<<< orphan*/  hw_lock; TYPE_1__* dpram; scalar_t__ iobase; int /*<<< orphan*/  irq_enabled; } ;
typedef  TYPE_2__ hysdn_card ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ PCI9050_INTR_REG ; 
 int PCI9050_INTR_REG_STAT1 ; 
 int bytein (scalar_t__) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t
ergo_interrupt(int intno, void *dev_id)
{
	hysdn_card *card = dev_id;	/* parameter from irq */
	tErgDpram *dpr;
	unsigned long flags;
	unsigned char volatile b;

	if (!card)
		return IRQ_NONE;		/* error -> spurious interrupt */
	if (!card->irq_enabled)
		return IRQ_NONE;		/* other device interrupting or irq switched off */

	spin_lock_irqsave(&card->hysdn_lock, flags); /* no further irqs allowed */

	if (!(bytein(card->iobase + PCI9050_INTR_REG) & PCI9050_INTR_REG_STAT1)) {
		spin_unlock_irqrestore(&card->hysdn_lock, flags);	/* restore old state */
		return IRQ_NONE;		/* no interrupt requested by E1 */
	}
	/* clear any pending ints on the board */
	dpr = card->dpram;
	b = dpr->ToPcInt;	/* clear for ergo */
	b |= dpr->ToPcIntMetro;	/* same for metro */
	b |= dpr->ToHyInt;	/* and for champ */

	/* start kernel task immediately after leaving all interrupts */
	if (!card->hw_lock)
		schedule_work(&card->irq_queue);
	spin_unlock_irqrestore(&card->hysdn_lock, flags);
	return IRQ_HANDLED;
}