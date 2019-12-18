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
struct splice_pipe_desc {int dummy; } ;
struct sock {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;
struct TYPE_3__ {unsigned long page_offset; int /*<<< orphan*/  size; int /*<<< orphan*/  page; } ;
typedef  TYPE_1__ skb_frag_t ;
struct TYPE_4__ {int nr_frags; TYPE_1__* frags; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 scalar_t__ __splice_segment (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,unsigned int*,unsigned int*,struct sk_buff*,struct splice_pipe_desc*,int,struct sock*) ; 
 int /*<<< orphan*/  skb_headlen (struct sk_buff*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  virt_to_page (scalar_t__) ; 

__attribute__((used)) static int __skb_splice_bits(struct sk_buff *skb, unsigned int *offset,
			     unsigned int *len, struct splice_pipe_desc *spd,
			     struct sock *sk)
{
	int seg;

	/*
	 * map the linear part
	 */
	if (__splice_segment(virt_to_page(skb->data),
			     (unsigned long) skb->data & (PAGE_SIZE - 1),
			     skb_headlen(skb),
			     offset, len, skb, spd, 1, sk))
		return 1;

	/*
	 * then map the fragments
	 */
	for (seg = 0; seg < skb_shinfo(skb)->nr_frags; seg++) {
		const skb_frag_t *f = &skb_shinfo(skb)->frags[seg];

		if (__splice_segment(f->page, f->page_offset, f->size,
				     offset, len, skb, spd, 0, sk))
			return 1;
	}

	return 0;
}