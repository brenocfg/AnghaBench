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
struct s6gmac {scalar_t__ tx_skb_i; scalar_t__ tx_skb_o; scalar_t__ rx_skb_i; scalar_t__ rx_skb_o; int /*<<< orphan*/  lock; int /*<<< orphan*/ * rx_skb; int /*<<< orphan*/ * tx_skb; int /*<<< orphan*/  phydev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 size_t S6_NUM_RX_SKB ; 
 size_t S6_NUM_TX_SKB ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ ) ; 
 struct s6gmac* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  phy_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s6gmac_init_dmac (struct net_device*) ; 
 int /*<<< orphan*/  s6gmac_stop_device (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int s6gmac_stop(struct net_device *dev)
{
	struct s6gmac *pd = netdev_priv(dev);
	unsigned long flags;
	netif_stop_queue(dev);
	phy_stop(pd->phydev);
	spin_lock_irqsave(&pd->lock, flags);
	s6gmac_init_dmac(dev);
	s6gmac_stop_device(dev);
	while (pd->tx_skb_i != pd->tx_skb_o)
		dev_kfree_skb(pd->tx_skb[(pd->tx_skb_o++) % S6_NUM_TX_SKB]);
	while (pd->rx_skb_i != pd->rx_skb_o)
		dev_kfree_skb(pd->rx_skb[(pd->rx_skb_o++) % S6_NUM_RX_SKB]);
	spin_unlock_irqrestore(&pd->lock, flags);
	return 0;
}