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
struct sock {int dummy; } ;
struct sk_buff {scalar_t__ pkt_type; struct sock* sk; scalar_t__ len; } ;
struct net_device_stats {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {struct net_device_stats stats; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 scalar_t__ PACKET_LOOPBACK ; 
 int /*<<< orphan*/  echo ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct sk_buff* skb_share_check (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcan_rx (struct sk_buff*,struct net_device*) ; 

__attribute__((used)) static netdev_tx_t vcan_tx(struct sk_buff *skb, struct net_device *dev)
{
	struct net_device_stats *stats = &dev->stats;
	int loop;

	stats->tx_packets++;
	stats->tx_bytes += skb->len;

	/* set flag whether this packet has to be looped back */
	loop = skb->pkt_type == PACKET_LOOPBACK;

	if (!echo) {
		/* no echo handling available inside this driver */

		if (loop) {
			/*
			 * only count the packets here, because the
			 * CAN core already did the echo for us
			 */
			stats->rx_packets++;
			stats->rx_bytes += skb->len;
		}
		kfree_skb(skb);
		return NETDEV_TX_OK;
	}

	/* perform standard echo handling for CAN network interfaces */

	if (loop) {
		struct sock *srcsk = skb->sk;

		skb = skb_share_check(skb, GFP_ATOMIC);
		if (!skb)
			return NETDEV_TX_OK;

		/* receive with packet counting */
		skb->sk = srcsk;
		vcan_rx(skb, dev);
	} else {
		/* no looped packets => no counting */
		kfree_skb(skb);
	}
	return NETDEV_TX_OK;
}