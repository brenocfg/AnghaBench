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
struct sk_buff {int /*<<< orphan*/  users; int /*<<< orphan*/  pool_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,int /*<<< orphan*/ ,struct sk_buff*,int) ; 
 int /*<<< orphan*/  __kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  trace_consume_skb (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

void consume_skb(struct sk_buff *skb)
{
	if (unlikely(!skb))
		return;
	DPRINTK("Try to consum skb[%d] 0x%p with user reference %d\n", skb->pool_id, skb, atomic_read(&skb->users));
	if (likely(atomic_read(&skb->users) == 1))
		smp_rmb();
	else if (likely(!atomic_dec_and_test(&skb->users)))
		return;
	trace_consume_skb(skb);
	__kfree_skb(skb);
}