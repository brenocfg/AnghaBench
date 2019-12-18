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
struct sk_buff {int dummy; } ;
struct fifo_sched_data {scalar_t__ limit; } ;
struct Qdisc {int /*<<< orphan*/  q; } ;

/* Variables and functions */
 scalar_t__ likely (int) ; 
 int qdisc_enqueue_tail (struct sk_buff*,struct Qdisc*) ; 
 struct fifo_sched_data* qdisc_priv (struct Qdisc*) ; 
 int qdisc_reshape_fail (struct sk_buff*,struct Qdisc*) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pfifo_enqueue(struct sk_buff *skb, struct Qdisc* sch)
{
	struct fifo_sched_data *q = qdisc_priv(sch);

	if (likely(skb_queue_len(&sch->q) < q->limit))
		return qdisc_enqueue_tail(skb, sch);

	return qdisc_reshape_fail(skb, sch);
}