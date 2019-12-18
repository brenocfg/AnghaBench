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
struct sk_buff_head {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 struct sk_buff* __skb_dequeue (struct sk_buff_head*) ; 
 scalar_t__ in_softirq () ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 

__attribute__((used)) static inline struct sk_buff *pool_skb_dequeue(struct sk_buff_head *list)
{
	struct sk_buff *skb;

	if (in_softirq()) {
		skb = __skb_dequeue(list);
	} else {
		local_bh_disable();
		skb = __skb_dequeue(list);
		local_bh_enable();
	}

	return skb;
}