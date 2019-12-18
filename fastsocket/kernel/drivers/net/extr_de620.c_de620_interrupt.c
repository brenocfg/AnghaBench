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
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  int byte ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int RXGOOD ; 
 int /*<<< orphan*/  R_STS ; 
 int TXBF0 ; 
 int TXBF1 ; 
 int de620_get_register (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  de620_lock ; 
 int de620_rx_intr (struct net_device*) ; 
 int de620_tx_buffs (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t
de620_interrupt(int irq_in, void *dev_id)
{
	struct net_device *dev = dev_id;
	byte irq_status;
	int bogus_count = 0;
	int again = 0;

	spin_lock(&de620_lock);

	/* Read the status register (_not_ the status port) */
	irq_status = de620_get_register(dev, R_STS);

	pr_debug("de620_interrupt (%2.2X)\n", irq_status);

	if (irq_status & RXGOOD) {
		do {
			again = de620_rx_intr(dev);
			pr_debug("again=%d\n", again);
		}
		while (again && (++bogus_count < 100));
	}

	if(de620_tx_buffs(dev) != (TXBF0 | TXBF1))
		netif_wake_queue(dev);

	spin_unlock(&de620_lock);
	return IRQ_HANDLED;
}