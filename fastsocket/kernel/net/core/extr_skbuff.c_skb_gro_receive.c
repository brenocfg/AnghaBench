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
struct skb_shared_info {int nr_frags; unsigned int gso_size; TYPE_1__* frags; struct sk_buff* frag_list; } ;
struct sk_buff {unsigned int len; unsigned int truesize; unsigned int data_len; struct sk_buff* prev; struct sk_buff* next; scalar_t__ data; int /*<<< orphan*/  mac_len; } ;
struct TYPE_3__ {unsigned int page_offset; unsigned int size; } ;
typedef  TYPE_1__ skb_frag_t ;
struct TYPE_4__ {int free; int same_flow; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int E2BIG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int MAX_SKB_FRAGS ; 
 TYPE_2__* NAPI_GRO_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  __copy_skb_header (struct sk_buff*,struct sk_buff*) ; 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  __skb_put (struct sk_buff*,unsigned int) ; 
 struct sk_buff* alloc_skb (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,scalar_t__) ; 
 unsigned int skb_gro_len (struct sk_buff*) ; 
 unsigned int skb_gro_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_header_release (struct sk_buff*) ; 
 unsigned int skb_headlen (struct sk_buff*) ; 
 unsigned int skb_headroom (struct sk_buff*) ; 
 scalar_t__ skb_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_network_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  skb_set_mac_header (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_set_network_header (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_set_transport_header (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct skb_shared_info* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_transport_offset (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

int skb_gro_receive(struct sk_buff **head, struct sk_buff *skb)
{
	struct sk_buff *p = *head;
	struct sk_buff *nskb;
	struct skb_shared_info *skbinfo = skb_shinfo(skb);
	struct skb_shared_info *pinfo = skb_shinfo(p);
	unsigned int headroom;
	unsigned int len = skb_gro_len(skb);
	unsigned int offset = skb_gro_offset(skb);
	unsigned int headlen = skb_headlen(skb);

	if (p->len + len >= 65536)
		return -E2BIG;

	if (pinfo->frag_list)
		goto merge;
	else if (headlen <= offset) {
		skb_frag_t *frag;
		skb_frag_t *frag2;
		int i = skbinfo->nr_frags;
		int nr_frags = pinfo->nr_frags + i;

		offset -= headlen;

		if (nr_frags > MAX_SKB_FRAGS)
			return -E2BIG;

		pinfo->nr_frags = nr_frags;
		skbinfo->nr_frags = 0;

		frag = pinfo->frags + nr_frags;
		frag2 = skbinfo->frags + i;
		do {
			*--frag = *--frag2;
		} while (--i);

		frag->page_offset += offset;
		frag->size -= offset;

		skb->truesize -= skb->data_len;
		skb->len -= skb->data_len;
		skb->data_len = 0;

		NAPI_GRO_CB(skb)->free = 1;
		goto done;
	} else if (skb_gro_len(p) != pinfo->gso_size)
		return -E2BIG;

	headroom = skb_headroom(p);
	nskb = alloc_skb(headroom + skb_gro_offset(p), GFP_ATOMIC);
	if (unlikely(!nskb))
		return -ENOMEM;

	__copy_skb_header(nskb, p);
	nskb->mac_len = p->mac_len;

	skb_reserve(nskb, headroom);
	__skb_put(nskb, skb_gro_offset(p));

	skb_set_mac_header(nskb, skb_mac_header(p) - p->data);
	skb_set_network_header(nskb, skb_network_offset(p));
	skb_set_transport_header(nskb, skb_transport_offset(p));

	__skb_pull(p, skb_gro_offset(p));
	memcpy(skb_mac_header(nskb), skb_mac_header(p),
	       p->data - skb_mac_header(p));

	*NAPI_GRO_CB(nskb) = *NAPI_GRO_CB(p);
	skb_shinfo(nskb)->frag_list = p;
	skb_shinfo(nskb)->gso_size = pinfo->gso_size;
	pinfo->gso_size = 0;
	skb_header_release(p);
	nskb->prev = p;

	nskb->data_len += p->len;
	nskb->truesize += p->len;
	nskb->len += p->len;

	*head = nskb;
	nskb->next = p->next;
	p->next = NULL;

	p = nskb;

merge:
	if (offset > headlen) {
		unsigned int eat = offset - headlen;

		skbinfo->frags[0].page_offset += eat;
		skbinfo->frags[0].size -= eat;
		skb->data_len -= eat;
		skb->len -= eat;
		offset = headlen;
	}

	__skb_pull(skb, offset);

	p->prev->next = skb;
	p->prev = skb;
	skb_header_release(skb);

done:
	NAPI_GRO_CB(p)->count++;
	p->data_len += len;
	p->truesize += len;
	p->len += len;

	NAPI_GRO_CB(skb)->same_flow = 1;
	return 0;
}