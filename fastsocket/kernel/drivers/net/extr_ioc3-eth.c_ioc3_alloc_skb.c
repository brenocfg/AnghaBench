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
struct sk_buff {scalar_t__ data; } ;

/* Variables and functions */
 scalar_t__ IOC3_CACHELINE ; 
 int aligned_rx_skb_addr (unsigned long) ; 
 struct sk_buff* alloc_skb (scalar_t__,unsigned int) ; 
 scalar_t__ likely (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

__attribute__((used)) static inline struct sk_buff * ioc3_alloc_skb(unsigned long length,
	unsigned int gfp_mask)
{
	struct sk_buff *skb;

	skb = alloc_skb(length + IOC3_CACHELINE - 1, gfp_mask);
	if (likely(skb)) {
		int offset = aligned_rx_skb_addr((unsigned long) skb->data);
		if (offset)
			skb_reserve(skb, offset);
	}

	return skb;
}