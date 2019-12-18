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
struct sk_buff {int encapsulation; scalar_t__ ip_summed; } ;
struct TYPE_2__ {int /*<<< orphan*/  gso_type; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_NONE ; 
 scalar_t__ CHECKSUM_PARTIAL ; 
 struct sk_buff* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  SKB_GSO_GRE ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ likely (int) ; 
 int skb_checksum_help (struct sk_buff*) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 int skb_unclone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

struct sk_buff *gre_handle_offloads(struct sk_buff *skb, bool gre_csum)
{
	int err;

	if (likely(!skb->encapsulation)) {
		/* skb_reset_inner_headers(skb); */
		skb->encapsulation = 1;
	}

	if (skb_is_gso(skb)) {
		err = skb_unclone(skb, GFP_ATOMIC);
		if (unlikely(err))
			goto error;
		skb_shinfo(skb)->gso_type |= SKB_GSO_GRE;
		return skb;
	} else if (skb->ip_summed == CHECKSUM_PARTIAL && gre_csum) {
		err = skb_checksum_help(skb);
		if (unlikely(err))
			goto error;
	} else if (skb->ip_summed != CHECKSUM_PARTIAL)
		skb->ip_summed = CHECKSUM_NONE;

	return skb;
error:
	kfree_skb(skb);
	return ERR_PTR(err);
}