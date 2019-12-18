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
struct s6gmac {int /*<<< orphan*/  lock; int /*<<< orphan*/  tx_chan; int /*<<< orphan*/  tx_dma; int /*<<< orphan*/  rx_chan; int /*<<< orphan*/  rx_dma; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 struct s6gmac* netdev_priv (struct net_device*) ; 
 scalar_t__ s6dmac_termcnt_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s6gmac_rx_fillfifo (struct s6gmac*) ; 
 int /*<<< orphan*/  s6gmac_rx_interrupt (struct net_device*) ; 
 int /*<<< orphan*/  s6gmac_stats_interrupt (struct s6gmac*,int) ; 
 int /*<<< orphan*/  s6gmac_tx_interrupt (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t s6gmac_interrupt(int irq, void *dev_id)
{
	struct net_device *dev = (struct net_device *)dev_id;
	struct s6gmac *pd = netdev_priv(dev);
	if (!dev)
		return IRQ_NONE;
	spin_lock(&pd->lock);
	if (s6dmac_termcnt_irq(pd->rx_dma, pd->rx_chan))
		s6gmac_rx_interrupt(dev);
	s6gmac_rx_fillfifo(pd);
	if (s6dmac_termcnt_irq(pd->tx_dma, pd->tx_chan))
		s6gmac_tx_interrupt(dev);
	s6gmac_stats_interrupt(pd, 0);
	s6gmac_stats_interrupt(pd, 1);
	spin_unlock(&pd->lock);
	return IRQ_HANDLED;
}