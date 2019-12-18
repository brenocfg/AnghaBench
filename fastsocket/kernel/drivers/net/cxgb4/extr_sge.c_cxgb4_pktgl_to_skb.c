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
struct sk_buff {unsigned int len; unsigned int data_len; int /*<<< orphan*/  truesize; } ;
struct pkt_gl {unsigned int tot_len; int /*<<< orphan*/  va; } ;

/* Variables and functions */
 unsigned int RX_COPY_THRES ; 
 int /*<<< orphan*/  __skb_put (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  copy_frags (int /*<<< orphan*/ ,struct pkt_gl const*,unsigned int) ; 
 struct sk_buff* dev_alloc_skb (unsigned int) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  skb_shinfo (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

struct sk_buff *cxgb4_pktgl_to_skb(const struct pkt_gl *gl,
				   unsigned int skb_len, unsigned int pull_len)
{
	struct sk_buff *skb;

	/*
	 * Below we rely on RX_COPY_THRES being less than the smallest Rx buffer
	 * size, which is expected since buffers are at least PAGE_SIZEd.
	 * In this case packets up to RX_COPY_THRES have only one fragment.
	 */
	if (gl->tot_len <= RX_COPY_THRES) {
		skb = dev_alloc_skb(gl->tot_len);
		if (unlikely(!skb))
			goto out;
		__skb_put(skb, gl->tot_len);
		skb_copy_to_linear_data(skb, gl->va, gl->tot_len);
	} else {
		skb = dev_alloc_skb(skb_len);
		if (unlikely(!skb))
			goto out;
		__skb_put(skb, pull_len);
		skb_copy_to_linear_data(skb, gl->va, pull_len);

		copy_frags(skb_shinfo(skb), gl, pull_len);
		skb->len = gl->tot_len;
		skb->data_len = skb->len - pull_len;
		skb->truesize += skb->data_len;
	}
out:	return skb;
}