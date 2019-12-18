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
struct skb_pool {int /*<<< orphan*/  recyc_list; int /*<<< orphan*/  free_list; } ;
struct sk_buff {scalar_t__ pool_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DPRINTK (char*,scalar_t__,struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  __skb_queue_head (int /*<<< orphan*/ *,struct sk_buff*) ; 
 scalar_t__ in_softirq () ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 struct skb_pool* per_cpu_ptr (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  skb_pools ; 
 int /*<<< orphan*/  skb_queue_head (int /*<<< orphan*/ *,struct sk_buff*) ; 
 scalar_t__ smp_processor_id () ; 

__attribute__((used)) static inline void kfree_pool_skb(struct sk_buff *skb)
{
	struct skb_pool *skb_pool;

	BUG_ON(skb->pool_id < 0);

	skb_pool = per_cpu_ptr(skb_pools, skb->pool_id);

	if (likely(skb->pool_id == smp_processor_id())) {
		if (in_softirq()) {
			__skb_queue_head(&skb_pool->free_list, skb);
		} else {
			local_bh_disable();
			__skb_queue_head(&skb_pool->free_list, skb);
			local_bh_enable();
		}
		DPRINTK("Free pool skb[%d] 0x%p on CPU %d into free list\n", skb->pool_id, skb, smp_processor_id());
	} else {
		skb_queue_head(&skb_pool->recyc_list, skb);
		DPRINTK("Free pool skb[%d] 0x%p on CPU %d into recycle list\n", skb->pool_id, skb, smp_processor_id());
	}
}