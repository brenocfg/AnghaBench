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
struct net2280 {int /*<<< orphan*/  lock; TYPE_1__* regs; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  irqstat0; int /*<<< orphan*/  irqstat1; } ;

/* Variables and functions */
 int INTA_ASSERTED ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  handle_stat0_irqs (struct net2280*,int) ; 
 int /*<<< orphan*/  handle_stat1_irqs (struct net2280*,int) ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t net2280_irq (int irq, void *_dev)
{
	struct net2280		*dev = _dev;

	/* shared interrupt, not ours */
	if (!(readl(&dev->regs->irqstat0) & (1 << INTA_ASSERTED)))
		return IRQ_NONE;

	spin_lock (&dev->lock);

	/* handle disconnect, dma, and more */
	handle_stat1_irqs (dev, readl (&dev->regs->irqstat1));

	/* control requests and PIO */
	handle_stat0_irqs (dev, readl (&dev->regs->irqstat0));

	spin_unlock (&dev->lock);

	return IRQ_HANDLED;
}