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
struct c2_dev {scalar_t__ regs; int /*<<< orphan*/  netdev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ C2_DISR ; 
 scalar_t__ C2_NISR0 ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  c2_rnic_interrupt (struct c2_dev*) ; 
 int /*<<< orphan*/  c2_rx_interrupt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c2_tx_interrupt (int /*<<< orphan*/ ) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t c2_interrupt(int irq, void *dev_id)
{
	unsigned int netisr0, dmaisr;
	int handled = 0;
	struct c2_dev *c2dev = (struct c2_dev *) dev_id;

	/* Process CCILNET interrupts */
	netisr0 = readl(c2dev->regs + C2_NISR0);
	if (netisr0) {

		/*
		 * There is an issue with the firmware that always
		 * provides the status of RX for both TX & RX
		 * interrupts.  So process both queues here.
		 */
		c2_rx_interrupt(c2dev->netdev);
		c2_tx_interrupt(c2dev->netdev);

		/* Clear the interrupt */
		writel(netisr0, c2dev->regs + C2_NISR0);
		handled++;
	}

	/* Process RNIC interrupts */
	dmaisr = readl(c2dev->regs + C2_DISR);
	if (dmaisr) {
		writel(dmaisr, c2dev->regs + C2_DISR);
		c2_rnic_interrupt(c2dev);
		handled++;
	}

	if (handled) {
		return IRQ_HANDLED;
	} else {
		return IRQ_NONE;
	}
}