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
struct sk_buff {int /*<<< orphan*/  pkt_type; struct net_device* dev; } ;
struct net_device {int /*<<< orphan*/  broadcast; } ;
struct macvlan_dev {int (* forward ) (struct net_device*,struct sk_buff*) ;int (* receive ) (struct sk_buff*) ;struct net_device* dev; } ;
struct ethhdr {int /*<<< orphan*/  h_dest; } ;

/* Variables and functions */
 int NET_RX_DROP ; 
 int /*<<< orphan*/  PACKET_BROADCAST ; 
 int /*<<< orphan*/  PACKET_MULTICAST ; 
 int /*<<< orphan*/  compare_ether_addr_64bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct net_device*,struct sk_buff*) ; 
 int stub2 (struct sk_buff*) ; 

__attribute__((used)) static int macvlan_broadcast_one(struct sk_buff *skb,
				 const struct macvlan_dev *vlan,
				 const struct ethhdr *eth, bool local)
{
	struct net_device *dev = vlan->dev;
	if (!skb)
		return NET_RX_DROP;

	if (local)
		return vlan->forward(dev, skb);

	skb->dev = dev;
	if (!compare_ether_addr_64bits(eth->h_dest,
				       dev->broadcast))
		skb->pkt_type = PACKET_BROADCAST;
	else
		skb->pkt_type = PACKET_MULTICAST;

	return vlan->receive(skb);
}