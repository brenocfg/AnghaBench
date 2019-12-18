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
struct sk_buff {int /*<<< orphan*/  dev; } ;
struct iphdr {int /*<<< orphan*/  tos; int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;

/* Variables and functions */
 int NET_RX_DROP ; 
 int dst_input (struct sk_buff*) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 scalar_t__ ip_route_input (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/ * skb_dst (struct sk_buff*) ; 

__attribute__((used)) static inline int xfrm4_rcv_encap_finish(struct sk_buff *skb)
{
	if (skb_dst(skb) == NULL) {
		const struct iphdr *iph = ip_hdr(skb);

		if (ip_route_input(skb, iph->daddr, iph->saddr, iph->tos,
				   skb->dev))
			goto drop;
	}
	return dst_input(skb);
drop:
	kfree_skb(skb);
	return NET_RX_DROP;
}