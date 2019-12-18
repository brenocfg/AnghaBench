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
struct at91_private {int /*<<< orphan*/  ether_clk; } ;

/* Variables and functions */
 unsigned long AT91_EMAC_ABT ; 
 int /*<<< orphan*/  AT91_EMAC_CTL ; 
 int /*<<< orphan*/  AT91_EMAC_IDR ; 
 unsigned long AT91_EMAC_RBNA ; 
 unsigned long AT91_EMAC_RCOM ; 
 unsigned long AT91_EMAC_RE ; 
 unsigned long AT91_EMAC_ROVR ; 
 unsigned long AT91_EMAC_RTRY ; 
 unsigned long AT91_EMAC_TCOM ; 
 unsigned long AT91_EMAC_TE ; 
 unsigned long AT91_EMAC_TUND ; 
 unsigned long at91_emac_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at91_emac_write (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_phyirq (struct net_device*) ; 
 struct at91_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 

__attribute__((used)) static int at91ether_close(struct net_device *dev)
{
	struct at91_private *lp = netdev_priv(dev);
	unsigned long ctl;

	/* Disable Receiver and Transmitter */
	ctl = at91_emac_read(AT91_EMAC_CTL);
	at91_emac_write(AT91_EMAC_CTL, ctl & ~(AT91_EMAC_TE | AT91_EMAC_RE));

	/* Disable PHY interrupt */
	disable_phyirq(dev);

	/* Disable MAC interrupts */
	at91_emac_write(AT91_EMAC_IDR, AT91_EMAC_RCOM | AT91_EMAC_RBNA
				| AT91_EMAC_TUND | AT91_EMAC_RTRY | AT91_EMAC_TCOM
				| AT91_EMAC_ROVR | AT91_EMAC_ABT);

	netif_stop_queue(dev);

	clk_disable(lp->ether_clk);		/* Disable Peripheral clock */

	return 0;
}