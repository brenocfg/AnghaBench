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
struct sk_buff {int /*<<< orphan*/  dev; int /*<<< orphan*/  pkt_type; struct nf_bridge_info* nf_bridge; } ;
struct nf_bridge_info {int mask; struct net_device* physindev; int /*<<< orphan*/  physoutdev; } ;
struct net_device {int dummy; } ;
struct inet_skb_parm {int dummy; } ;

/* Variables and functions */
 int BRNF_BRIDGED_DNAT ; 
 int BRNF_PKT_TYPE ; 
 int /*<<< orphan*/  IPCB (struct sk_buff*) ; 
 unsigned int NF_ACCEPT ; 
 int /*<<< orphan*/  NF_BR_FORWARD ; 
 unsigned int NF_DROP ; 
 int /*<<< orphan*/  NF_HOOK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*,struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int NF_STOLEN ; 
 int /*<<< orphan*/  PACKET_OTHERHOST ; 
 int /*<<< orphan*/  PF_BRIDGE ; 
 int /*<<< orphan*/  br_forward_finish ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nf_bridge_push_encap_header (struct sk_buff*) ; 
 int /*<<< orphan*/  nf_bridge_unshare (struct sk_buff*) ; 

__attribute__((used)) static unsigned int br_nf_local_out(unsigned int hook, struct sk_buff *skb,
				    const struct net_device *in,
				    const struct net_device *out,
				    int (*okfn)(struct sk_buff *))
{
	struct net_device *realindev;
	struct nf_bridge_info *nf_bridge;

	if (!skb->nf_bridge)
		return NF_ACCEPT;

	/* Need exclusive nf_bridge_info since we might have multiple
	 * different physoutdevs. */
	if (!nf_bridge_unshare(skb))
		return NF_DROP;

	nf_bridge = skb->nf_bridge;
	if (!(nf_bridge->mask & BRNF_BRIDGED_DNAT))
		return NF_ACCEPT;

	/* Bridged, take PF_BRIDGE/FORWARD.
	 * (see big note in front of br_nf_pre_routing_finish) */
	nf_bridge->physoutdev = skb->dev;
	realindev = nf_bridge->physindev;

	if (nf_bridge->mask & BRNF_PKT_TYPE) {
		skb->pkt_type = PACKET_OTHERHOST;
		nf_bridge->mask ^= BRNF_PKT_TYPE;
	}
	nf_bridge_push_encap_header(skb);

	/* BUG: Should really parse the IP options here. */
	memset(IPCB(skb), 0, sizeof(struct inet_skb_parm));

	NF_HOOK(PF_BRIDGE, NF_BR_FORWARD, skb, realindev, skb->dev,
		br_forward_finish);
	return NF_STOLEN;
}