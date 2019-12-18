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
typedef  int /*<<< orphan*/  u32 ;
struct skb_frag_struct {int size; int page_offset; } ;
struct sk_buff {int len; int data_len; int truesize; int tail; int /*<<< orphan*/  protocol; int /*<<< orphan*/  csum; int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  data; } ;
struct net_lro_mgr {int /*<<< orphan*/  dev; int /*<<< orphan*/  frag_align_pad; } ;
typedef  int /*<<< orphan*/  __wsum ;
struct TYPE_2__ {struct skb_frag_struct* frags; int /*<<< orphan*/  nr_frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int) ; 
 int min (int,int) ; 
 struct sk_buff* netdev_alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int /*<<< orphan*/ ) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *lro_gen_skb(struct net_lro_mgr *lro_mgr,
				   struct skb_frag_struct *frags,
				   int len, int true_size,
				   void *mac_hdr,
				   int hlen, __wsum sum,
				   u32 ip_summed)
{
	struct sk_buff *skb;
	struct skb_frag_struct *skb_frags;
	int data_len = len;
	int hdr_len = min(len, hlen);

	skb = netdev_alloc_skb(lro_mgr->dev, hlen + lro_mgr->frag_align_pad);
	if (!skb)
		return NULL;

	skb_reserve(skb, lro_mgr->frag_align_pad);
	skb->len = len;
	skb->data_len = len - hdr_len;
	skb->truesize += true_size;
	skb->tail += hdr_len;

	memcpy(skb->data, mac_hdr, hdr_len);

	skb_frags = skb_shinfo(skb)->frags;
	while (data_len > 0) {
		*skb_frags = *frags;
		data_len -= frags->size;
		skb_frags++;
		frags++;
		skb_shinfo(skb)->nr_frags++;
	}

	skb_shinfo(skb)->frags[0].page_offset += hdr_len;
	skb_shinfo(skb)->frags[0].size -= hdr_len;

	skb->ip_summed = ip_summed;
	skb->csum = sum;
	skb->protocol = eth_type_trans(skb, lro_mgr->dev);
	return skb;
}