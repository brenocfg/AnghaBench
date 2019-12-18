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
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct net_device {int /*<<< orphan*/  dev; } ;
struct ethoc_bd {int stat; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {int rx_bytes; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_packets; } ;
struct ethoc {unsigned int num_tx; unsigned int cur_rx; unsigned int num_rx; TYPE_1__ stats; } ;

/* Variables and functions */
 int RX_BD_EMPTY ; 
 int RX_BD_STATS ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  ethoc_read_bd (struct ethoc*,unsigned int,struct ethoc_bd*) ; 
 scalar_t__ ethoc_update_rx_stats (struct ethoc*,struct ethoc_bd*) ; 
 int /*<<< orphan*/  ethoc_write_bd (struct ethoc*,unsigned int,struct ethoc_bd*) ; 
 scalar_t__ likely (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy_fromio (int /*<<< orphan*/ ,void*,int) ; 
 scalar_t__ net_ratelimit () ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,int) ; 
 struct ethoc* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 void* phys_to_virt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

__attribute__((used)) static int ethoc_rx(struct net_device *dev, int limit)
{
	struct ethoc *priv = netdev_priv(dev);
	int count;

	for (count = 0; count < limit; ++count) {
		unsigned int entry;
		struct ethoc_bd bd;

		entry = priv->num_tx + (priv->cur_rx % priv->num_rx);
		ethoc_read_bd(priv, entry, &bd);
		if (bd.stat & RX_BD_EMPTY)
			break;

		if (ethoc_update_rx_stats(priv, &bd) == 0) {
			int size = bd.stat >> 16;
			struct sk_buff *skb = netdev_alloc_skb(dev, size);

			size -= 4; /* strip the CRC */
			skb_reserve(skb, 2); /* align TCP/IP header */

			if (likely(skb)) {
				void *src = phys_to_virt(bd.addr);
				memcpy_fromio(skb_put(skb, size), src, size);
				skb->protocol = eth_type_trans(skb, dev);
				priv->stats.rx_packets++;
				priv->stats.rx_bytes += size;
				netif_receive_skb(skb);
			} else {
				if (net_ratelimit())
					dev_warn(&dev->dev, "low on memory - "
							"packet dropped\n");

				priv->stats.rx_dropped++;
				break;
			}
		}

		/* clear the buffer descriptor so it can be reused */
		bd.stat &= ~RX_BD_STATS;
		bd.stat |=  RX_BD_EMPTY;
		ethoc_write_bd(priv, entry, &bd);
		priv->cur_rx++;
	}

	return count;
}