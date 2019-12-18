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
struct sk_buff {int len; scalar_t__ data; } ;
struct packet_type {int dummy; } ;
struct net_device {int priv_flags; int flags; } ;
struct bonding {int dummy; } ;
struct arp_pkt {scalar_t__ op_code; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPOP_REPLY ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int IFF_802_1Q_VLAN ; 
 int IFF_BONDING ; 
 int IFF_MASTER ; 
 int NET_RX_DROP ; 
 int NET_RX_SUCCESS ; 
 int /*<<< orphan*/  arp_hdr_len (struct net_device*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/ * dev_net (struct net_device*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_net ; 
 struct bonding* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rlb_update_entry_from_arp (struct bonding*,struct arp_pkt*) ; 
 struct sk_buff* skb_share_check (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct net_device* vlan_dev_real_dev (struct net_device*) ; 

__attribute__((used)) static int rlb_arp_recv(struct sk_buff *skb, struct net_device *bond_dev, struct packet_type *ptype, struct net_device *orig_dev)
{
	struct bonding *bond;
	struct arp_pkt *arp = (struct arp_pkt *)skb->data;
	int res = NET_RX_DROP;

	if (dev_net(bond_dev) != &init_net)
		goto out;

	while (bond_dev->priv_flags & IFF_802_1Q_VLAN)
		bond_dev = vlan_dev_real_dev(bond_dev);

	if (!(bond_dev->priv_flags & IFF_BONDING) ||
	    !(bond_dev->flags & IFF_MASTER))
		goto out;

	if (!arp) {
		pr_debug("Packet has no ARP data\n");
		goto out;
	}

	skb = skb_share_check(skb, GFP_ATOMIC);
	if (!skb)
		goto out;

	if (!pskb_may_pull(skb, arp_hdr_len(bond_dev)))
		goto out;

	if (skb->len < sizeof(struct arp_pkt)) {
		pr_debug("Packet is too small to be an ARP\n");
		goto out;
	}

	if (arp->op_code == htons(ARPOP_REPLY)) {
		/* update rx hash table for this ARP */
		bond = netdev_priv(bond_dev);
		rlb_update_entry_from_arp(bond, arp);
		pr_debug("Server received an ARP Reply from client\n");
	}

	res = NET_RX_SUCCESS;

out:
	dev_kfree_skb(skb);

	return res;
}