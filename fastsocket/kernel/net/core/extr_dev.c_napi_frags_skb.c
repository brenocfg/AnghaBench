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
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct napi_struct {struct sk_buff* skb; } ;
struct ethhdr {int /*<<< orphan*/  h_proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  napi_reuse_skb (struct napi_struct*,struct sk_buff*) ; 
 struct ethhdr* skb_gro_header_fast (struct sk_buff*,unsigned int) ; 
 scalar_t__ skb_gro_header_hard (struct sk_buff*,unsigned int) ; 
 struct ethhdr* skb_gro_header_slow (struct sk_buff*,unsigned int,unsigned int) ; 
 unsigned int skb_gro_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_gro_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_gro_reset_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

struct sk_buff *napi_frags_skb(struct napi_struct *napi)
{
	struct sk_buff *skb = napi->skb;
	struct ethhdr *eth;
	unsigned int hlen;
	unsigned int off;

	napi->skb = NULL;

	skb_reset_mac_header(skb);
	skb_gro_reset_offset(skb);

	off = skb_gro_offset(skb);
	hlen = off + sizeof(*eth);
	eth = skb_gro_header_fast(skb, off);
	if (skb_gro_header_hard(skb, hlen)) {
		eth = skb_gro_header_slow(skb, hlen, off);
		if (unlikely(!eth)) {
			napi_reuse_skb(napi, skb);
			skb = NULL;
			goto out;
		}
	}

	skb_gro_pull(skb, sizeof(*eth));

	/*
	 * This works because the only protocols we care about don't require
	 * special handling.  We'll fix it up properly at the end.
	 */
	skb->protocol = eth->h_proto;

out:
	return skb;
}