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
struct sk_buff {struct net_device* dev; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,struct sk_buff*) ; 
 int ENABLE_COMMON_SKB_POOL ; 
 scalar_t__ NET_SKB_PAD ; 
 int /*<<< orphan*/  NUMA_NO_NODE ; 
 int /*<<< orphan*/  POOL_SKB ; 
 int /*<<< orphan*/  SLAB_SKB ; 
 struct sk_buff* __alloc_skb (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int enable_skb_pool ; 
 struct sk_buff* in_softirq () ; 
 scalar_t__ likely (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 

struct sk_buff *__netdev_alloc_skb(struct net_device *dev,
		unsigned int length, gfp_t gfp_mask)
{
	struct sk_buff *skb;

	if ((enable_skb_pool & ENABLE_COMMON_SKB_POOL) && likely(in_softirq())) {
		skb = __alloc_skb(length + NET_SKB_PAD, gfp_mask, POOL_SKB, NUMA_NO_NODE);
		DPRINTK("Allocate pool skb 0x%p\n", skb);
	} else {
		skb = __alloc_skb(length + NET_SKB_PAD, gfp_mask, SLAB_SKB, NUMA_NO_NODE);
		DPRINTK("Allocate regular skb 0x%p\n", skb);
	}
	if (likely(skb)) {
		skb_reserve(skb, NET_SKB_PAD);
		skb->dev = dev;
	}
	return skb;
}