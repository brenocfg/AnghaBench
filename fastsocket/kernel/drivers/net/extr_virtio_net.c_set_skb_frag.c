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
struct sk_buff {int /*<<< orphan*/  truesize; int /*<<< orphan*/  len; int /*<<< orphan*/  data_len; } ;
struct page {int dummy; } ;
struct TYPE_4__ {unsigned int page_offset; scalar_t__ size; struct page* page; } ;
typedef  TYPE_1__ skb_frag_t ;
struct TYPE_6__ {int nr_frags; TYPE_1__* frags; } ;
struct TYPE_5__ {int shared_frag; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ min (unsigned int,unsigned int) ; 
 TYPE_3__* skb_shinfo (struct sk_buff*) ; 
 TYPE_2__* skb_tx (struct sk_buff*) ; 

__attribute__((used)) static void set_skb_frag(struct sk_buff *skb, struct page *page,
			 unsigned int offset, unsigned int *len)
{
	int i = skb_shinfo(skb)->nr_frags;
	skb_frag_t *f;

	f = &skb_shinfo(skb)->frags[i];
	f->size = min((unsigned)PAGE_SIZE - offset, *len);
	f->page_offset = offset;
	f->page = page;

	skb->data_len += f->size;
	skb->len += f->size;
	skb->truesize += PAGE_SIZE;
	skb_shinfo(skb)->nr_frags++;
	skb_tx(skb)->shared_frag = 1;
	*len -= f->size;
}