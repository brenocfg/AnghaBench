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
struct pq2ads_pci_pic {TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 int NUM_IRQS ; 
 int /*<<< orphan*/  clrbits32 (int /*<<< orphan*/ *,int) ; 
 struct pq2ads_pci_pic* get_irq_chip_data (unsigned int) ; 
 int /*<<< orphan*/  pci_pic_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int virq_to_hw (unsigned int) ; 

__attribute__((used)) static void pq2ads_pci_unmask_irq(unsigned int virq)
{
	struct pq2ads_pci_pic *priv = get_irq_chip_data(virq);
	int irq = NUM_IRQS - virq_to_hw(virq) - 1;

	if (irq != -1) {
		unsigned long flags;

		spin_lock_irqsave(&pci_pic_lock, flags);
		clrbits32(&priv->regs->mask, 1 << irq);
		spin_unlock_irqrestore(&pci_pic_lock, flags);
	}
}