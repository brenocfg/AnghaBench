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
struct sk_buff {int len; int /*<<< orphan*/  protocol; } ;
struct TYPE_2__ {int tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_dropped; } ;
struct net_device {TYPE_1__ stats; } ;
struct bpqdev {int /*<<< orphan*/  dest_addr; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  AX25_BPQ_HEADER_LEN ; 
 int /*<<< orphan*/  ETH_P_BPQ ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  ax25_type_trans (struct sk_buff*,struct net_device*) ; 
 struct net_device* bpq_get_ether_dev (struct net_device*) ; 
 int /*<<< orphan*/  dev_hard_header (struct sk_buff*,struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_queue_xmit (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ net_ratelimit () ; 
 struct bpqdev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ skb_cow (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 unsigned char* skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 

__attribute__((used)) static netdev_tx_t bpq_xmit(struct sk_buff *skb, struct net_device *dev)
{
	unsigned char *ptr;
	struct bpqdev *bpq;
	int size;

	/*
	 * Just to be *really* sure not to send anything if the interface
	 * is down, the ethernet device may have gone.
	 */
	if (!netif_running(dev)) {
		kfree_skb(skb);
		return NETDEV_TX_OK;
	}

	skb_pull(skb, 1);			/* Drop KISS byte */
	size = skb->len;

	/*
	 * We're about to mess with the skb which may still shared with the
	 * generic networking code so unshare and ensure it's got enough
	 * space for the BPQ headers.
	 */
	if (skb_cow(skb, AX25_BPQ_HEADER_LEN)) {
		if (net_ratelimit())
			pr_err("bpqether: out of memory\n");
		kfree_skb(skb);

		return NETDEV_TX_OK;
	}

	ptr = skb_push(skb, 2);			/* Make space for length */

	*ptr++ = (size + 5) % 256;
	*ptr++ = (size + 5) / 256;

	bpq = netdev_priv(dev);

	if ((dev = bpq_get_ether_dev(dev)) == NULL) {
		dev->stats.tx_dropped++;
		kfree_skb(skb);
		return NETDEV_TX_OK;
	}

	skb->protocol = ax25_type_trans(skb, dev);
	skb_reset_network_header(skb);
	dev_hard_header(skb, dev, ETH_P_BPQ, bpq->dest_addr, NULL, 0);
	dev->stats.tx_packets++;
	dev->stats.tx_bytes+=skb->len;
  
	dev_queue_xmit(skb);
	netif_wake_queue(dev);
	return NETDEV_TX_OK;
}