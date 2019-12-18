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
struct vxlan_dev {int flags; } ;
struct sk_buff {int dummy; } ;
struct net_device {int /*<<< orphan*/  addr_len; } ;
struct neighbour {int /*<<< orphan*/  ha; } ;
struct iphdr {int /*<<< orphan*/  daddr; } ;
struct TYPE_2__ {int /*<<< orphan*/  h_dest; int /*<<< orphan*/  h_source; int /*<<< orphan*/  h_proto; } ;

/* Variables and functions */
#define  ETH_P_IP 128 
 int VXLAN_F_L3MISS ; 
 int /*<<< orphan*/  arp_tbl ; 
 scalar_t__ compare_ether_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* eth_hdr (struct sk_buff*) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct neighbour* neigh_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct net_device*) ; 
 int /*<<< orphan*/  neigh_release (struct neighbour*) ; 
 struct vxlan_dev* netdev_priv (struct net_device*) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  vxlan_ip_miss (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool route_shortcircuit(struct net_device *dev, struct sk_buff *skb)
{
	struct vxlan_dev *vxlan = netdev_priv(dev);
	struct neighbour *n;
	struct iphdr *pip;

	if (is_multicast_ether_addr(eth_hdr(skb)->h_dest))
		return false;

	n = NULL;
	switch (ntohs(eth_hdr(skb)->h_proto)) {
	case ETH_P_IP:
		if (!pskb_may_pull(skb, sizeof(struct iphdr)))
			return false;
		pip = ip_hdr(skb);
		n = neigh_lookup(&arp_tbl, &pip->daddr, dev);
		break;
	default:
		return false;
	}

	if (n) {
		bool diff;

		diff = compare_ether_addr(eth_hdr(skb)->h_dest, n->ha) != 0;
		if (diff) {
			memcpy(eth_hdr(skb)->h_source, eth_hdr(skb)->h_dest,
				dev->addr_len);
			memcpy(eth_hdr(skb)->h_dest, n->ha, dev->addr_len);
		}
		neigh_release(n);
		return diff;
	} else if (vxlan->flags & VXLAN_F_L3MISS)
		vxlan_ip_miss(dev, pip->daddr);
	return false;
}