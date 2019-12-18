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
struct sk_buff {scalar_t__ protocol; int /*<<< orphan*/  dev; scalar_t__ cb; int /*<<< orphan*/  pkt_type; struct nf_bridge_info* nf_bridge; } ;
struct nf_bridge_info {int mask; struct net_device* physindev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int BRNF_PKT_TYPE ; 
 int /*<<< orphan*/  ETH_P_ARP ; 
 int /*<<< orphan*/  IS_VLAN_ARP (struct sk_buff*) ; 
 int /*<<< orphan*/  NF_BR_FORWARD ; 
 int /*<<< orphan*/  NF_HOOK_THRESH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*,struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PACKET_OTHERHOST ; 
 int /*<<< orphan*/  PF_BRIDGE ; 
 int /*<<< orphan*/  br_forward_finish ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_bridge_push_encap_header (struct sk_buff*) ; 

__attribute__((used)) static int br_nf_forward_finish(struct sk_buff *skb)
{
	struct nf_bridge_info *nf_bridge = skb->nf_bridge;
	struct net_device *in;

	if (skb->protocol != htons(ETH_P_ARP) && !IS_VLAN_ARP(skb)) {
		in = nf_bridge->physindev;
		if (nf_bridge->mask & BRNF_PKT_TYPE) {
			skb->pkt_type = PACKET_OTHERHOST;
			nf_bridge->mask ^= BRNF_PKT_TYPE;
		}
	} else {
		in = *((struct net_device **)(skb->cb));
	}
	nf_bridge_push_encap_header(skb);
	NF_HOOK_THRESH(PF_BRIDGE, NF_BR_FORWARD, skb, in,
		       skb->dev, br_forward_finish, 1);
	return 0;
}