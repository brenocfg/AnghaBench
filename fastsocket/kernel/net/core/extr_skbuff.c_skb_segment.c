#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {unsigned int data; unsigned int len; int head; unsigned int truesize; scalar_t__ ip_summed; unsigned int data_len; struct sk_buff* next; int /*<<< orphan*/  csum; scalar_t__ network_header; scalar_t__ transport_header; int /*<<< orphan*/  mac_len; int /*<<< orphan*/  csum_start; } ;
struct TYPE_4__ {int size; unsigned int page_offset; int /*<<< orphan*/  page; } ;
typedef  TYPE_1__ skb_frag_t ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_6__ {unsigned int gso_size; int nr_frags; struct sk_buff* frag_list; TYPE_1__* frags; } ;
struct TYPE_5__ {int /*<<< orphan*/  shared_frag; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 void* CHECKSUM_NONE ; 
 scalar_t__ CHECKSUM_PARTIAL ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct sk_buff* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int NETIF_F_SG ; 
 int /*<<< orphan*/  SKB_FRAG_ASSERT (struct sk_buff*) ; 
 int /*<<< orphan*/  __copy_skb_header (struct sk_buff*,struct sk_buff*) ; 
 int /*<<< orphan*/  __skb_push (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  __skb_put (struct sk_buff*,unsigned int) ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  can_checksum_protocol (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_checksum (struct sk_buff*,unsigned int,int,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_copy_and_csum_bits (struct sk_buff*,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data_offset (struct sk_buff*,unsigned int,unsigned int,int) ; 
 scalar_t__ skb_cow_head (struct sk_buff*,unsigned int) ; 
 int skb_end_pointer (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_get (struct sk_buff*) ; 
 unsigned int skb_headlen (struct sk_buff*) ; 
 unsigned int skb_headroom (struct sk_buff*) ; 
 unsigned int skb_mac_header (struct sk_buff*) ; 
 scalar_t__ skb_network_header_len (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_network_protocol (struct sk_buff*) ; 
 unsigned int skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_release_head_state (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_network_header (struct sk_buff*,int /*<<< orphan*/ ) ; 
 TYPE_3__* skb_shinfo (struct sk_buff*) ; 
 unsigned int skb_tnl_header_len (struct sk_buff*) ; 
 TYPE_2__* skb_tx (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

struct sk_buff *skb_segment(struct sk_buff *skb, int features)
{
	struct sk_buff *segs = NULL;
	struct sk_buff *tail = NULL;
	struct sk_buff *fskb = skb_shinfo(skb)->frag_list;
	unsigned int mss = skb_shinfo(skb)->gso_size;
	unsigned int doffset = skb->data - skb_mac_header(skb);
	unsigned int offset = doffset;
	unsigned int tnl_hlen = skb_tnl_header_len(skb);
	unsigned int headroom;
	unsigned int len;
	__be16 proto;
	bool csum;
	int sg = !!(features & NETIF_F_SG);
	int nfrags = skb_shinfo(skb)->nr_frags;
	int err = -ENOMEM;
	int i = 0;
	int pos;

	proto = skb_network_protocol(skb);
	if (unlikely(!proto))
		return ERR_PTR(-EINVAL);

	csum = !!can_checksum_protocol(features, proto);
	__skb_push(skb, doffset);
	headroom = skb_headroom(skb);
	pos = skb_headlen(skb);

	do {
		struct sk_buff *nskb;
		skb_frag_t *frag;
		int hsize;
		int size;

		len = skb->len - offset;
		if (len > mss)
			len = mss;

		hsize = skb_headlen(skb) - offset;
		if (hsize < 0)
			hsize = 0;
		if (hsize > len || !sg)
			hsize = len;

		if (!hsize && i >= nfrags) {
			BUG_ON(fskb->len != len);

			pos += len;
			nskb = skb_clone(fskb, GFP_ATOMIC);
			fskb = fskb->next;

			if (unlikely(!nskb))
				goto err;

			hsize = skb_end_pointer(nskb) - nskb->head;
			if (skb_cow_head(nskb, doffset + headroom)) {
				kfree_skb(nskb);
				goto err;
			}

			nskb->truesize += skb_end_pointer(nskb) - nskb->head -
					  hsize;
			skb_release_head_state(nskb);
			__skb_push(nskb, doffset);
		} else {
			nskb = alloc_skb(hsize + doffset + headroom,
					 GFP_ATOMIC);

			if (unlikely(!nskb))
				goto err;

			skb_reserve(nskb, headroom);
			__skb_put(nskb, doffset);
		}

		if (segs)
			tail->next = nskb;
		else
			segs = nskb;
		tail = nskb;

		__copy_skb_header(nskb, skb);
		nskb->mac_len = skb->mac_len;

		/* nskb and skb might have different headroom */
		if (nskb->ip_summed == CHECKSUM_PARTIAL)
			nskb->csum_start += skb_headroom(nskb) - headroom;

		skb_reset_mac_header(nskb);
		skb_set_network_header(nskb, skb->mac_len);
		nskb->transport_header = (nskb->network_header +
					  skb_network_header_len(skb));

		skb_copy_from_linear_data_offset(skb, -tnl_hlen,
						 nskb->data - tnl_hlen,
						 doffset + tnl_hlen);

		if (fskb != skb_shinfo(skb)->frag_list)
			goto perform_csum_check;

		if (!sg) {
			nskb->ip_summed = CHECKSUM_NONE;
			nskb->csum = skb_copy_and_csum_bits(skb, offset,
							    skb_put(nskb, len),
							    len, 0);
			continue;
		}

		frag = skb_shinfo(nskb)->frags;

		skb_copy_from_linear_data_offset(skb, offset,
						 skb_put(nskb, hsize), hsize);

		skb_tx(nskb)->shared_frag = skb_tx(skb)->shared_frag;

		while (pos < offset + len && i < nfrags) {
			*frag = skb_shinfo(skb)->frags[i];
			get_page(frag->page);
			size = frag->size;

			if (pos < offset) {
				frag->page_offset += offset - pos;
				frag->size -= offset - pos;
			}

			skb_shinfo(nskb)->nr_frags++;

			if (pos + size <= offset + len) {
				i++;
				pos += size;
			} else {
				frag->size -= pos + size - (offset + len);
				goto skip_fraglist;
			}

			frag++;
		}

		if (pos < offset + len) {
			struct sk_buff *fskb2 = fskb;

			BUG_ON(pos + fskb->len != offset + len);

			pos += fskb->len;
			fskb = fskb->next;

			if (fskb2->next) {
				fskb2 = skb_clone(fskb2, GFP_ATOMIC);
				if (!fskb2)
					goto err;
			} else
				skb_get(fskb2);

			SKB_FRAG_ASSERT(nskb);
			skb_shinfo(nskb)->frag_list = fskb2;
		}

skip_fraglist:
		nskb->data_len = len - hsize;
		nskb->len += nskb->data_len;
		nskb->truesize += nskb->data_len;

perform_csum_check:
		if (!csum) {
			nskb->csum = skb_checksum(nskb, doffset,
						  nskb->len - doffset, 0);
			nskb->ip_summed = CHECKSUM_NONE;
		}
	} while ((offset += len) < skb->len);

	return segs;

err:
	while ((skb = segs)) {
		segs = skb->next;
		kfree_skb(skb);
	}
	return ERR_PTR(err);
}