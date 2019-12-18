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
typedef  int u16 ;
struct vlan_group {int dummy; } ;
struct sk_buff {int deliver_no_wcard; int /*<<< orphan*/  pkt_type; struct net_device* dev; int /*<<< orphan*/  iif; } ;
struct net_device {int flags; int /*<<< orphan*/  ifindex; int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACCESS_ONCE (int /*<<< orphan*/ ) ; 
 int IFF_PROMISC ; 
 int NET_RX_DROP ; 
 int /*<<< orphan*/  PACKET_OTHERHOST ; 
 int VLAN_VID_MASK ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,int) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int netif_receive_skb (struct sk_buff*) ; 
 int netif_rx (struct sk_buff*) ; 
 scalar_t__ netpoll_rx (struct sk_buff*) ; 
 scalar_t__ skb_bond_should_drop (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct net_device* vlan_group_get_device (struct vlan_group*,int) ; 

int __vlan_hwaccel_rx(struct sk_buff *skb, struct vlan_group *grp,
		      u16 vlan_tci, int polling)
{
	struct net_device *vlan_dev;
	u16 vlan_id;

	if (netpoll_rx(skb))
		return NET_RX_DROP;

	if (skb_bond_should_drop(skb, ACCESS_ONCE(skb->dev->master)))
		skb->deliver_no_wcard = 1;

	skb->iif = skb->dev->ifindex;
	vlan_id = vlan_tci & VLAN_VID_MASK;
	if (vlan_id)
		__vlan_hwaccel_put_tag(skb, vlan_tci);
	vlan_dev = vlan_group_get_device(grp, vlan_id);

	if (vlan_dev)
		skb->dev = vlan_dev;
	else if (vlan_id) {
		if (!(skb->dev->flags & IFF_PROMISC))
			goto drop;
		skb->pkt_type = PACKET_OTHERHOST;
	}

	return (polling ? netif_receive_skb(skb) : netif_rx(skb));

drop:
	dev_kfree_skb_any(skb);
	return NET_RX_DROP;
}