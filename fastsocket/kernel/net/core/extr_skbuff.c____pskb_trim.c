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
struct sk_buff {int len; unsigned int data_len; struct sk_buff* next; } ;
struct TYPE_4__ {int nr_frags; struct sk_buff* frag_list; TYPE_1__* frags; } ;
struct TYPE_3__ {int size; int /*<<< orphan*/  page; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int pskb_expand_head (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pskb_trim (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_cloned (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_drop_fraglist (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_drop_list (struct sk_buff**) ; 
 scalar_t__ skb_has_frag_list (struct sk_buff*) ; 
 unsigned int skb_headlen (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_tail_pointer (struct sk_buff*,unsigned int) ; 
 scalar_t__ skb_shared (struct sk_buff*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

int ___pskb_trim(struct sk_buff *skb, unsigned int len)
{
	struct sk_buff **fragp;
	struct sk_buff *frag;
	int offset = skb_headlen(skb);
	int nfrags = skb_shinfo(skb)->nr_frags;
	int i;
	int err;

	if (skb_cloned(skb) &&
	    unlikely((err = pskb_expand_head(skb, 0, 0, GFP_ATOMIC))))
		return err;

	i = 0;
	if (offset >= len)
		goto drop_pages;

	for (; i < nfrags; i++) {
		int end = offset + skb_shinfo(skb)->frags[i].size;

		if (end < len) {
			offset = end;
			continue;
		}

		skb_shinfo(skb)->frags[i++].size = len - offset;

drop_pages:
		skb_shinfo(skb)->nr_frags = i;

		for (; i < nfrags; i++)
			put_page(skb_shinfo(skb)->frags[i].page);

		if (skb_has_frag_list(skb))
			skb_drop_fraglist(skb);
		goto done;
	}

	for (fragp = &skb_shinfo(skb)->frag_list; (frag = *fragp);
	     fragp = &frag->next) {
		int end = offset + frag->len;

		if (skb_shared(frag)) {
			struct sk_buff *nfrag;

			nfrag = skb_clone(frag, GFP_ATOMIC);
			if (unlikely(!nfrag))
				return -ENOMEM;

			nfrag->next = frag->next;
			kfree_skb(frag);
			frag = nfrag;
			*fragp = frag;
		}

		if (end < len) {
			offset = end;
			continue;
		}

		if (end > len &&
		    unlikely((err = pskb_trim(frag, len - offset))))
			return err;

		if (frag->next)
			skb_drop_list(&frag->next);
		break;
	}

done:
	if (len > skb_headlen(skb)) {
		skb->data_len -= skb->len - len;
		skb->len       = len;
	} else {
		skb->len       = len;
		skb->data_len  = 0;
		skb_set_tail_pointer(skb, len);
	}

	return 0;
}