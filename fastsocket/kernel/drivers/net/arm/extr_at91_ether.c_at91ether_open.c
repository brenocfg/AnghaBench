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
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct at91_private {int /*<<< orphan*/  lock; int /*<<< orphan*/  ether_clk; } ;

/* Variables and functions */
 unsigned long AT91_EMAC_ABT ; 
 unsigned long AT91_EMAC_CSR ; 
 int /*<<< orphan*/  AT91_EMAC_CTL ; 
 int /*<<< orphan*/  AT91_EMAC_IER ; 
 unsigned long AT91_EMAC_RBNA ; 
 unsigned long AT91_EMAC_RCOM ; 
 unsigned long AT91_EMAC_ROVR ; 
 unsigned long AT91_EMAC_RTRY ; 
 unsigned long AT91_EMAC_TCOM ; 
 unsigned long AT91_EMAC_TUND ; 
 int EADDRNOTAVAIL ; 
 unsigned long at91_emac_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at91_emac_write (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  at91ether_start (struct net_device*) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_mdi () ; 
 int /*<<< orphan*/  enable_mdi () ; 
 int /*<<< orphan*/  enable_phyirq (struct net_device*) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 struct at91_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_linkspeed (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_mac_address (struct net_device*) ; 

__attribute__((used)) static int at91ether_open(struct net_device *dev)
{
	struct at91_private *lp = netdev_priv(dev);
	unsigned long ctl;

	if (!is_valid_ether_addr(dev->dev_addr))
		return -EADDRNOTAVAIL;

	clk_enable(lp->ether_clk);		/* Re-enable Peripheral clock */

	/* Clear internal statistics */
	ctl = at91_emac_read(AT91_EMAC_CTL);
	at91_emac_write(AT91_EMAC_CTL, ctl | AT91_EMAC_CSR);

	/* Update the MAC address (incase user has changed it) */
	update_mac_address(dev);

	/* Enable PHY interrupt */
	enable_phyirq(dev);

	/* Enable MAC interrupts */
	at91_emac_write(AT91_EMAC_IER, AT91_EMAC_RCOM | AT91_EMAC_RBNA
				| AT91_EMAC_TUND | AT91_EMAC_RTRY | AT91_EMAC_TCOM
				| AT91_EMAC_ROVR | AT91_EMAC_ABT);

	/* Determine current link speed */
	spin_lock_irq(&lp->lock);
	enable_mdi();
	update_linkspeed(dev, 0);
	disable_mdi();
	spin_unlock_irq(&lp->lock);

	at91ether_start(dev);
	netif_start_queue(dev);
	return 0;
}