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
struct sk_buff {int /*<<< orphan*/  dev; int /*<<< orphan*/  pkt_type; struct nf_bridge_info* nf_bridge; } ;
struct TYPE_2__ {int /*<<< orphan*/  dst; } ;
struct rtable {TYPE_1__ u; } ;
struct nf_bridge_info {int mask; int /*<<< orphan*/  physindev; } ;

/* Variables and functions */
 int BRNF_NF_BRIDGE_PREROUTING ; 
 int BRNF_PKT_TYPE ; 
 int /*<<< orphan*/  NF_BR_PRE_ROUTING ; 
 int /*<<< orphan*/  NF_HOOK_THRESH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PACKET_OTHERHOST ; 
 int /*<<< orphan*/  PF_BRIDGE ; 
 int /*<<< orphan*/  br_handle_frame_finish ; 
 struct rtable* bridge_parent_rtable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dst_hold (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  nf_bridge_push_encap_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int br_nf_pre_routing_finish_ipv6(struct sk_buff *skb)
{
	struct nf_bridge_info *nf_bridge = skb->nf_bridge;
	struct rtable *rt;

	if (nf_bridge->mask & BRNF_PKT_TYPE) {
		skb->pkt_type = PACKET_OTHERHOST;
		nf_bridge->mask ^= BRNF_PKT_TYPE;
	}
	nf_bridge->mask ^= BRNF_NF_BRIDGE_PREROUTING;

	rt = bridge_parent_rtable(nf_bridge->physindev);
	if (!rt) {
		kfree_skb(skb);
		return 0;
	}
	dst_hold(&rt->u.dst);
	skb_dst_set(skb, &rt->u.dst);

	skb->dev = nf_bridge->physindev;
	nf_bridge_push_encap_header(skb);
	NF_HOOK_THRESH(PF_BRIDGE, NF_BR_PRE_ROUTING, skb, skb->dev, NULL,
		       br_handle_frame_finish, 1);

	return 0;
}