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
typedef  int /*<<< orphan*/  u_int8_t ;
struct sk_buff {scalar_t__ protocol; scalar_t__ pkt_type; int /*<<< orphan*/  dev; struct nf_bridge_info* nf_bridge; } ;
struct nf_bridge_info {int /*<<< orphan*/  physoutdev; int /*<<< orphan*/  mask; } ;
struct net_device {int dummy; } ;
struct inet_skb_parm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRNF_BRIDGED ; 
 int /*<<< orphan*/  BRNF_PKT_TYPE ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int /*<<< orphan*/  IPCB (struct sk_buff*) ; 
 scalar_t__ IS_PPPOE_IP (struct sk_buff*) ; 
 scalar_t__ IS_PPPOE_IPV6 (struct sk_buff*) ; 
 scalar_t__ IS_VLAN_IP (struct sk_buff*) ; 
 scalar_t__ IS_VLAN_IPV6 (struct sk_buff*) ; 
 unsigned int NF_ACCEPT ; 
 unsigned int NF_DROP ; 
 int /*<<< orphan*/  NF_HOOK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*,struct net_device*,struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NF_INET_FORWARD ; 
 unsigned int NF_STOLEN ; 
 scalar_t__ PACKET_HOST ; 
 scalar_t__ PACKET_OTHERHOST ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  PF_INET6 ; 
 int /*<<< orphan*/  br_nf_forward_finish ; 
 struct net_device* bridge_parent (struct net_device const*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nf_bridge_pull_encap_header (struct sk_buff*) ; 
 int /*<<< orphan*/  nf_bridge_unshare (struct sk_buff*) ; 

__attribute__((used)) static unsigned int br_nf_forward_ip(unsigned int hook, struct sk_buff *skb,
				     const struct net_device *in,
				     const struct net_device *out,
				     int (*okfn)(struct sk_buff *))
{
	struct nf_bridge_info *nf_bridge;
	struct net_device *parent;
	u_int8_t pf;

	if (!skb->nf_bridge)
		return NF_ACCEPT;

	/* Need exclusive nf_bridge_info since we might have multiple
	 * different physoutdevs. */
	if (!nf_bridge_unshare(skb))
		return NF_DROP;

	parent = bridge_parent(out);
	if (!parent)
		return NF_DROP;

	if (skb->protocol == htons(ETH_P_IP) || IS_VLAN_IP(skb) ||
	    IS_PPPOE_IP(skb))
		pf = PF_INET;
	else if (skb->protocol == htons(ETH_P_IPV6) || IS_VLAN_IPV6(skb) ||
		 IS_PPPOE_IPV6(skb))
		pf = PF_INET6;
	else
		return NF_ACCEPT;

	nf_bridge_pull_encap_header(skb);

	nf_bridge = skb->nf_bridge;
	if (skb->pkt_type == PACKET_OTHERHOST) {
		skb->pkt_type = PACKET_HOST;
		nf_bridge->mask |= BRNF_PKT_TYPE;
	}

	/* BUG: Should really parse the IP options here. */
	memset(IPCB(skb), 0, sizeof(struct inet_skb_parm));

	/* The physdev module checks on this */
	nf_bridge->mask |= BRNF_BRIDGED;
	nf_bridge->physoutdev = skb->dev;

	NF_HOOK(pf, NF_INET_FORWARD, skb, bridge_parent(in), parent,
		br_nf_forward_finish);

	return NF_STOLEN;
}