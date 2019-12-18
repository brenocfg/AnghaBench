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
struct sk_buff {int* data; int /*<<< orphan*/  protocol; } ;
struct packet_type {int dummy; } ;
struct TYPE_2__ {int rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct net_device {TYPE_1__ stats; } ;
struct ethhdr {int /*<<< orphan*/  h_source; } ;
struct bpqdev {int* acpt_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int NET_RX_DROP ; 
 int /*<<< orphan*/  ax25_type_trans (struct sk_buff*,struct net_device*) ; 
 struct net_device* bpq_get_ax25_dev (struct net_device*) ; 
 int /*<<< orphan*/ * dev_net (struct net_device*) ; 
 struct ethhdr* eth_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 struct bpqdev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ skb_cow (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 char* skb_push (struct sk_buff*,int) ; 
 struct sk_buff* skb_share_check (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int) ; 

__attribute__((used)) static int bpq_rcv(struct sk_buff *skb, struct net_device *dev, struct packet_type *ptype, struct net_device *orig_dev)
{
	int len;
	char * ptr;
	struct ethhdr *eth;
	struct bpqdev *bpq;

	if (dev_net(dev) != &init_net)
		goto drop;

	if ((skb = skb_share_check(skb, GFP_ATOMIC)) == NULL)
		return NET_RX_DROP;

	if (!pskb_may_pull(skb, sizeof(struct ethhdr)))
		goto drop;

	rcu_read_lock();
	dev = bpq_get_ax25_dev(dev);

	if (dev == NULL || !netif_running(dev)) 
		goto drop_unlock;

	/*
	 * if we want to accept frames from just one ethernet device
	 * we check the source address of the sender.
	 */

	bpq = netdev_priv(dev);

	eth = eth_hdr(skb);

	if (!(bpq->acpt_addr[0] & 0x01) &&
	    memcmp(eth->h_source, bpq->acpt_addr, ETH_ALEN))
		goto drop_unlock;

	if (skb_cow(skb, sizeof(struct ethhdr)))
		goto drop_unlock;

	len = skb->data[0] + skb->data[1] * 256 - 5;

	skb_pull(skb, 2);	/* Remove the length bytes */
	skb_trim(skb, len);	/* Set the length of the data */

	dev->stats.rx_packets++;
	dev->stats.rx_bytes += len;

	ptr = skb_push(skb, 1);
	*ptr = 0;

	skb->protocol = ax25_type_trans(skb, dev);
	netif_rx(skb);
unlock:

	rcu_read_unlock();

	return 0;
drop_unlock:
	kfree_skb(skb);
	goto unlock;

drop:
	kfree_skb(skb);
	return 0;
}