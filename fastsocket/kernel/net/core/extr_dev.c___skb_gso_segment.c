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
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mac_offset; } ;

/* Variables and functions */
 struct sk_buff* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 TYPE_1__* SKB_GSO_CB (struct sk_buff*) ; 
 int pskb_expand_head (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_header_cloned (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_headroom (struct sk_buff*) ; 
 struct sk_buff* skb_mac_gso_segment (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_needs_check (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_mac_len (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_warn_bad_offload (struct sk_buff*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

struct sk_buff *__skb_gso_segment(struct sk_buff *skb,
				  int features, bool tx_path)
{
	if (unlikely(skb_needs_check(skb, tx_path))) {
		int err;

		skb_warn_bad_offload(skb);

		if (skb_header_cloned(skb) &&
		    (err = pskb_expand_head(skb, 0, 0, GFP_ATOMIC)))
			return ERR_PTR(err);
	}

	SKB_GSO_CB(skb)->mac_offset = skb_headroom(skb);
	skb_reset_mac_header(skb);
	skb_reset_mac_len(skb);

	return skb_mac_gso_segment(skb, features);
}