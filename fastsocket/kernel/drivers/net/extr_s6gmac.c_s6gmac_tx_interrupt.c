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
typedef  scalar_t__ u8 ;
struct s6gmac {int /*<<< orphan*/  tx_chan; int /*<<< orphan*/  tx_dma; scalar_t__ tx_skb_o; int /*<<< orphan*/ * tx_skb; scalar_t__ tx_skb_i; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 size_t S6_NUM_TX_SKB ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (int /*<<< orphan*/ ) ; 
 struct s6gmac* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  s6dmac_fifo_full (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ s6dmac_pending_count (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s6gmac_tx_interrupt(struct net_device *dev)
{
	struct s6gmac *pd = netdev_priv(dev);
	while (((u8)(pd->tx_skb_i - pd->tx_skb_o)) >
			s6dmac_pending_count(pd->tx_dma, pd->tx_chan)) {
		dev_kfree_skb_irq(pd->tx_skb[(pd->tx_skb_o++) % S6_NUM_TX_SKB]);
	}
	if (!s6dmac_fifo_full(pd->tx_dma, pd->tx_chan))
		netif_wake_queue(dev);
}