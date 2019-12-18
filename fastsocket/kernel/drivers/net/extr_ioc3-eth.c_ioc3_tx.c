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
typedef  int u32 ;
struct sk_buff {scalar_t__ len; } ;
struct TYPE_2__ {unsigned long tx_packets; unsigned long tx_bytes; } ;
struct ioc3_private {int tx_ci; unsigned long txqlen; int /*<<< orphan*/  ioc3_lock; TYPE_1__ stats; struct sk_buff** tx_skbs; struct ioc3* regs; } ;
struct ioc3 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb_irq (struct sk_buff*) ; 
 int ioc3_r_etcir () ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  priv_netdev (struct ioc3_private*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void ioc3_tx(struct ioc3_private *ip)
{
	unsigned long packets, bytes;
	struct ioc3 *ioc3 = ip->regs;
	int tx_entry, o_entry;
	struct sk_buff *skb;
	u32 etcir;

	spin_lock(&ip->ioc3_lock);
	etcir = ioc3_r_etcir();

	tx_entry = (etcir >> 7) & 127;
	o_entry = ip->tx_ci;
	packets = 0;
	bytes = 0;

	while (o_entry != tx_entry) {
		packets++;
		skb = ip->tx_skbs[o_entry];
		bytes += skb->len;
		dev_kfree_skb_irq(skb);
		ip->tx_skbs[o_entry] = NULL;

		o_entry = (o_entry + 1) & 127;		/* Next */

		etcir = ioc3_r_etcir();			/* More pkts sent?  */
		tx_entry = (etcir >> 7) & 127;
	}

	ip->stats.tx_packets += packets;
	ip->stats.tx_bytes += bytes;
	ip->txqlen -= packets;

	if (ip->txqlen < 128)
		netif_wake_queue(priv_netdev(ip));

	ip->tx_ci = o_entry;
	spin_unlock(&ip->ioc3_lock);
}