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
struct vmxnet3_rx_buf_info {int /*<<< orphan*/  page; } ;
struct skb_frag_struct {scalar_t__ page_offset; } ;
struct sk_buff {int /*<<< orphan*/  truesize; int /*<<< orphan*/  data_len; } ;
struct Vmxnet3_RxCompDesc {int /*<<< orphan*/  len; } ;
struct TYPE_2__ {int nr_frags; struct skb_frag_struct* frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ MAX_SKB_FRAGS ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  __skb_frag_set_page (struct skb_frag_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_frag_size_set (struct skb_frag_struct*,int /*<<< orphan*/ ) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static void
vmxnet3_append_frag(struct sk_buff *skb, struct Vmxnet3_RxCompDesc *rcd,
		    struct vmxnet3_rx_buf_info *rbi)
{
	struct skb_frag_struct *frag = skb_shinfo(skb)->frags +
		skb_shinfo(skb)->nr_frags;

	BUG_ON(skb_shinfo(skb)->nr_frags >= MAX_SKB_FRAGS);

	__skb_frag_set_page(frag, rbi->page);
	frag->page_offset = 0;
	skb_frag_size_set(frag, rcd->len);
	skb->data_len += rcd->len;
	skb->truesize += PAGE_SIZE;
	skb_shinfo(skb)->nr_frags++;
}