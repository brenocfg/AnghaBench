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
struct sk_buff {scalar_t__ protocol; scalar_t__ cb; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int ar_pln; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_ARP ; 
 scalar_t__ IS_VLAN_ARP (struct sk_buff*) ; 
 int /*<<< orphan*/  NFPROTO_ARP ; 
 unsigned int NF_ACCEPT ; 
 int /*<<< orphan*/  NF_ARP_FORWARD ; 
 int /*<<< orphan*/  NF_HOOK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*,struct net_device*,struct net_device*,int /*<<< orphan*/ ) ; 
 unsigned int NF_STOLEN ; 
 TYPE_1__* arp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  br_nf_forward_finish ; 
 int /*<<< orphan*/  brnf_call_arptables ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_bridge_pull_encap_header (struct sk_buff*) ; 
 int /*<<< orphan*/  nf_bridge_push_encap_header (struct sk_buff*) ; 

__attribute__((used)) static unsigned int br_nf_forward_arp(unsigned int hook, struct sk_buff *skb,
				      const struct net_device *in,
				      const struct net_device *out,
				      int (*okfn)(struct sk_buff *))
{
	struct net_device **d = (struct net_device **)(skb->cb);

#ifdef CONFIG_SYSCTL
	if (!brnf_call_arptables)
		return NF_ACCEPT;
#endif

	if (skb->protocol != htons(ETH_P_ARP)) {
		if (!IS_VLAN_ARP(skb))
			return NF_ACCEPT;
		nf_bridge_pull_encap_header(skb);
	}

	if (arp_hdr(skb)->ar_pln != 4) {
		if (IS_VLAN_ARP(skb))
			nf_bridge_push_encap_header(skb);
		return NF_ACCEPT;
	}
	*d = (struct net_device *)in;
	NF_HOOK(NFPROTO_ARP, NF_ARP_FORWARD, skb, (struct net_device *)in,
		(struct net_device *)out, br_nf_forward_finish);

	return NF_STOLEN;
}