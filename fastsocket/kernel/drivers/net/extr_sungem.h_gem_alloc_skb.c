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
struct sk_buff {int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 scalar_t__ ALIGNED_RX_SKB_ADDR (int /*<<< orphan*/ ) ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

__attribute__((used)) static __inline__ struct sk_buff *gem_alloc_skb(int size,
						gfp_t gfp_flags)
{
	struct sk_buff *skb = alloc_skb(size + 64, gfp_flags);

	if (skb) {
		int offset = (int) ALIGNED_RX_SKB_ADDR(skb->data);
		if (offset)
			skb_reserve(skb, offset);
	}

	return skb;
}