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
struct sk_buff {scalar_t__ pkt_type; scalar_t__ dev; TYPE_2__* nf_bridge; } ;
struct dst_entry {TYPE_1__* neighbour; scalar_t__ hh; } ;
struct TYPE_4__ {int /*<<< orphan*/  mask; } ;
struct TYPE_3__ {int (* output ) (struct sk_buff*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BRNF_NF_BRIDGE_PREROUTING ; 
 int /*<<< orphan*/  BRNF_PKT_TYPE ; 
 scalar_t__ PACKET_HOST ; 
 scalar_t__ PACKET_OTHERHOST ; 
 scalar_t__ bridge_parent (scalar_t__) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int neigh_hh_output (scalar_t__,struct sk_buff*) ; 
 int /*<<< orphan*/  nf_bridge_pull_encap_header (struct sk_buff*) ; 
 struct dst_entry* skb_dst (struct sk_buff*) ; 
 int stub1 (struct sk_buff*) ; 

__attribute__((used)) static int br_nf_pre_routing_finish_bridge(struct sk_buff *skb)
{
	if (skb->pkt_type == PACKET_OTHERHOST) {
		skb->pkt_type = PACKET_HOST;
		skb->nf_bridge->mask |= BRNF_PKT_TYPE;
	}
	skb->nf_bridge->mask ^= BRNF_NF_BRIDGE_PREROUTING;

	skb->dev = bridge_parent(skb->dev);
	if (skb->dev) {
		struct dst_entry *dst = skb_dst(skb);

		nf_bridge_pull_encap_header(skb);

		if (dst->hh)
			return neigh_hh_output(dst->hh, skb);
		else if (dst->neighbour)
			return dst->neighbour->output(skb);
	}
	kfree_skb(skb);
	return 0;
}