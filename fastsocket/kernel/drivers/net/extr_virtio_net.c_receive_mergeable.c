#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct virtnet_info {int /*<<< orphan*/  num; int /*<<< orphan*/  rvq; } ;
struct TYPE_5__ {int num_buffers; } ;
struct skb_vnet_hdr {TYPE_1__ mhdr; } ;
struct sk_buff {TYPE_3__* dev; } ;
struct page {int dummy; } ;
struct TYPE_8__ {int nr_frags; } ;
struct TYPE_6__ {int /*<<< orphan*/  rx_length_errors; } ;
struct TYPE_7__ {TYPE_2__ stats; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int MAX_SKB_FRAGS ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  set_skb_frag (struct sk_buff*,struct page*,int /*<<< orphan*/ ,int*) ; 
 TYPE_4__* skb_shinfo (struct sk_buff*) ; 
 struct skb_vnet_hdr* skb_vnet_hdr (struct sk_buff*) ; 
 struct page* virtqueue_get_buf (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int receive_mergeable(struct virtnet_info *vi, struct sk_buff *skb)
{
	struct skb_vnet_hdr *hdr = skb_vnet_hdr(skb);
	struct page *page;
	int num_buf, i, len;

	num_buf = hdr->mhdr.num_buffers;
	while (--num_buf) {
		i = skb_shinfo(skb)->nr_frags;
		if (i >= MAX_SKB_FRAGS) {
			pr_debug("%s: packet too long\n", skb->dev->name);
			skb->dev->stats.rx_length_errors++;
			return -EINVAL;
		}

		page = virtqueue_get_buf(vi->rvq, &len);
		if (!page) {
			pr_debug("%s: rx error: %d buffers missing\n",
				 skb->dev->name, hdr->mhdr.num_buffers);
			skb->dev->stats.rx_length_errors++;
			return -EINVAL;
		}
		if (len > PAGE_SIZE)
			len = PAGE_SIZE;

		set_skb_frag(skb, page, 0, &len);

		--vi->num;
	}
	return 0;
}