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
struct sky2_port {unsigned int rx_data_size; TYPE_1__* hw; } ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct rx_ring_info {struct sk_buff* skb; } ;
struct TYPE_4__ {scalar_t__ nr_frags; } ;
struct TYPE_3__ {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  prefetch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  skb_put_frags (struct sk_buff*,unsigned int,unsigned int) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 struct sk_buff* sky2_rx_alloc (struct sky2_port*) ; 
 scalar_t__ sky2_rx_map_skb (int /*<<< orphan*/ ,struct rx_ring_info*,unsigned int) ; 
 int /*<<< orphan*/  sky2_rx_unmap_skb (int /*<<< orphan*/ ,struct rx_ring_info*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct sk_buff *receive_new(struct sky2_port *sky2,
				   struct rx_ring_info *re,
				   unsigned int length)
{
	struct sk_buff *skb, *nskb;
	unsigned hdr_space = sky2->rx_data_size;

	/* Don't be tricky about reusing pages (yet) */
	nskb = sky2_rx_alloc(sky2);
	if (unlikely(!nskb))
		return NULL;

	skb = re->skb;
	sky2_rx_unmap_skb(sky2->hw->pdev, re);

	prefetch(skb->data);
	re->skb = nskb;
	if (sky2_rx_map_skb(sky2->hw->pdev, re, hdr_space)) {
		dev_kfree_skb(nskb);
		re->skb = skb;
		return NULL;
	}

	if (skb_shinfo(skb)->nr_frags)
		skb_put_frags(skb, hdr_space, length);
	else
		skb_put(skb, length);
	return skb;
}