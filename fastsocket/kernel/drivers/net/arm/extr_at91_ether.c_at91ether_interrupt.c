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
struct TYPE_2__ {int tx_errors; } ;
struct net_device {int /*<<< orphan*/  name; TYPE_1__ stats; } ;
struct at91_private {int /*<<< orphan*/  skb_length; int /*<<< orphan*/  skb_physaddr; int /*<<< orphan*/ * skb; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_EMAC_CTL ; 
 int /*<<< orphan*/  AT91_EMAC_ISR ; 
 unsigned long AT91_EMAC_RBNA ; 
 unsigned long AT91_EMAC_RCOM ; 
 unsigned long AT91_EMAC_RE ; 
 unsigned long AT91_EMAC_ROVR ; 
 unsigned long AT91_EMAC_RTRY ; 
 unsigned long AT91_EMAC_TCOM ; 
 unsigned long AT91_EMAC_TUND ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned long at91_emac_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at91_emac_write (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  at91ether_rx (struct net_device*) ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct at91_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t at91ether_interrupt(int irq, void *dev_id)
{
	struct net_device *dev = (struct net_device *) dev_id;
	struct at91_private *lp = netdev_priv(dev);
	unsigned long intstatus, ctl;

	/* MAC Interrupt Status register indicates what interrupts are pending.
	   It is automatically cleared once read. */
	intstatus = at91_emac_read(AT91_EMAC_ISR);

	if (intstatus & AT91_EMAC_RCOM)		/* Receive complete */
		at91ether_rx(dev);

	if (intstatus & AT91_EMAC_TCOM) {	/* Transmit complete */
		/* The TCOM bit is set even if the transmission failed. */
		if (intstatus & (AT91_EMAC_TUND | AT91_EMAC_RTRY))
			dev->stats.tx_errors += 1;

		if (lp->skb) {
			dev_kfree_skb_irq(lp->skb);
			lp->skb = NULL;
			dma_unmap_single(NULL, lp->skb_physaddr, lp->skb_length, DMA_TO_DEVICE);
		}
		netif_wake_queue(dev);
	}

	/* Work-around for Errata #11 */
	if (intstatus & AT91_EMAC_RBNA) {
		ctl = at91_emac_read(AT91_EMAC_CTL);
		at91_emac_write(AT91_EMAC_CTL, ctl & ~AT91_EMAC_RE);
		at91_emac_write(AT91_EMAC_CTL, ctl | AT91_EMAC_RE);
	}

	if (intstatus & AT91_EMAC_ROVR)
		printk("%s: ROVR error\n", dev->name);

	return IRQ_HANDLED;
}