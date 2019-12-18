#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {unsigned char* data; scalar_t__ len; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {TYPE_1__ stats; } ;
struct net_bridge_mdb_entry {int dummy; } ;
struct net_bridge_fdb_entry {int /*<<< orphan*/  dst; } ;
struct net_bridge {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_4__ {scalar_t__ mrouters_only; struct net_device* brdev; } ;

/* Variables and functions */
 TYPE_2__* BR_INPUT_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  ETH_HLEN ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 struct net_bridge_fdb_entry* __br_fdb_get (struct net_bridge*,unsigned char const*) ; 
 int /*<<< orphan*/  br_deliver (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  br_flood_deliver (struct net_bridge*,struct sk_buff*) ; 
 struct net_bridge_mdb_entry* br_mdb_get (struct net_bridge*,struct sk_buff*) ; 
 int /*<<< orphan*/  br_multicast_deliver (struct net_bridge_mdb_entry*,struct sk_buff*) ; 
 scalar_t__ br_multicast_rcv (struct net_bridge*,int /*<<< orphan*/ *,struct sk_buff*) ; 
 scalar_t__ is_broadcast_ether_addr (unsigned char const*) ; 
 scalar_t__ is_multicast_ether_addr (unsigned char const*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct net_bridge* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netpoll_tx_running (struct net_device*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

netdev_tx_t br_dev_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct net_bridge *br = netdev_priv(dev);
	const unsigned char *dest = skb->data;
	struct net_bridge_fdb_entry *dst;
	struct net_bridge_mdb_entry *mdst;

	BR_INPUT_SKB_CB(skb)->brdev = dev;

	dev->stats.tx_packets++;
	dev->stats.tx_bytes += skb->len;

	skb_reset_mac_header(skb);
	skb_pull(skb, ETH_HLEN);

	if (is_broadcast_ether_addr(dest))
		br_flood_deliver(br, skb);
	else if (is_multicast_ether_addr(dest)) {
		if (unlikely(netpoll_tx_running(dev))) {
			br_flood_deliver(br, skb);
			goto out;
		}
		if (br_multicast_rcv(br, NULL, skb)) {
			kfree_skb(skb);
			goto out;
		}

		mdst = br_mdb_get(br, skb);
		if (mdst || BR_INPUT_SKB_CB(skb)->mrouters_only)
			br_multicast_deliver(mdst, skb);
		else
			br_flood_deliver(br, skb);
	} else if ((dst = __br_fdb_get(br, dest)) != NULL)
		br_deliver(dst->dst, skb);
	else
		br_flood_deliver(br, skb);

out:
	return NETDEV_TX_OK;
}