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
struct sk_buff {unsigned char* data; int /*<<< orphan*/  dev; } ;
struct dn_skb_cb {int /*<<< orphan*/  hops; void* src; void* dst; } ;

/* Variables and functions */
 struct dn_skb_cb* DN_SKB_CB (struct sk_buff*) ; 
 int NET_RX_DROP ; 
 int /*<<< orphan*/  NF_DN_PRE_ROUTING ; 
 int NF_HOOK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PF_DECnet ; 
 void* dn_eth2dn (unsigned char*) ; 
 int /*<<< orphan*/  dn_hiord_addr ; 
 int /*<<< orphan*/  dn_route_rx_packet ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ memcmp (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 

__attribute__((used)) static int dn_route_rx_long(struct sk_buff *skb)
{
	struct dn_skb_cb *cb = DN_SKB_CB(skb);
	unsigned char *ptr = skb->data;

	if (!pskb_may_pull(skb, 21)) /* 20 for long header, 1 for shortest nsp */
		goto drop_it;

	skb_pull(skb, 20);
	skb_reset_transport_header(skb);

	/* Destination info */
	ptr += 2;
	cb->dst = dn_eth2dn(ptr);
	if (memcmp(ptr, dn_hiord_addr, 4) != 0)
		goto drop_it;
	ptr += 6;


	/* Source info */
	ptr += 2;
	cb->src = dn_eth2dn(ptr);
	if (memcmp(ptr, dn_hiord_addr, 4) != 0)
		goto drop_it;
	ptr += 6;
	/* Other junk */
	ptr++;
	cb->hops = *ptr++; /* Visit Count */

	return NF_HOOK(PF_DECnet, NF_DN_PRE_ROUTING, skb, skb->dev, NULL, dn_route_rx_packet);

drop_it:
	kfree_skb(skb);
	return NET_RX_DROP;
}