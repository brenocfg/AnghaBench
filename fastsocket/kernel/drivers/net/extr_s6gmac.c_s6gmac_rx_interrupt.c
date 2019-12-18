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
typedef  int u32 ;
struct sk_buff {int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  protocol; struct net_device* dev; } ;
struct s6gmac {scalar_t__ reg; scalar_t__ rx_skb_o; struct sk_buff** rx_skb; int /*<<< orphan*/  rx_chan; int /*<<< orphan*/  rx_dma; scalar_t__ rx_skb_i; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 scalar_t__ S6_GMAC_BURST_POSTRD ; 
 int S6_GMAC_BURST_POSTRD_DROP ; 
 int S6_GMAC_BURST_POSTRD_LEN ; 
 int S6_GMAC_BURST_POSTRD_LEN_MASK ; 
 size_t S6_NUM_RX_SKB ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (struct sk_buff*) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 struct s6gmac* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int readl (scalar_t__) ; 
 scalar_t__ s6dmac_pending_count (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static void s6gmac_rx_interrupt(struct net_device *dev)
{
	struct s6gmac *pd = netdev_priv(dev);
	u32 pfx;
	struct sk_buff *skb;
	while (((u8)(pd->rx_skb_i - pd->rx_skb_o)) >
			s6dmac_pending_count(pd->rx_dma, pd->rx_chan)) {
		skb = pd->rx_skb[(pd->rx_skb_o++) % S6_NUM_RX_SKB];
		pfx = readl(pd->reg + S6_GMAC_BURST_POSTRD);
		if (pfx & (1 << S6_GMAC_BURST_POSTRD_DROP)) {
			dev_kfree_skb_irq(skb);
		} else {
			skb_put(skb, (pfx >> S6_GMAC_BURST_POSTRD_LEN)
				& S6_GMAC_BURST_POSTRD_LEN_MASK);
			skb->dev = dev;
			skb->protocol = eth_type_trans(skb, dev);
			skb->ip_summed = CHECKSUM_UNNECESSARY;
			netif_rx(skb);
		}
	}
}