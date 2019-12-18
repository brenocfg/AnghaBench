#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ tv64; } ;
struct sk_buff {TYPE_2__ tstamp; int /*<<< orphan*/  tc_verd; } ;
struct netem_skb_cb {scalar_t__ time_to_send; } ;
struct netem_sched_data {int /*<<< orphan*/  watchdog; TYPE_4__* qdisc; } ;
struct TYPE_8__ {int /*<<< orphan*/  qlen; } ;
struct Qdisc {int flags; TYPE_3__ q; } ;
typedef  scalar_t__ psched_time_t ;
struct TYPE_9__ {TYPE_1__* ops; } ;
struct TYPE_6__ {struct sk_buff* (* peek ) (TYPE_4__*) ;} ;

/* Variables and functions */
 int AT_INGRESS ; 
 int G_TC_FROM (int /*<<< orphan*/ ) ; 
 int TCQ_F_THROTTLED ; 
 struct netem_skb_cb* netem_skb_cb (struct sk_buff*) ; 
 int /*<<< orphan*/  pr_debug (char*,struct sk_buff*) ; 
 scalar_t__ psched_get_time () ; 
 struct sk_buff* qdisc_dequeue_peeked (TYPE_4__*) ; 
 struct netem_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_watchdog_schedule (int /*<<< orphan*/ *,scalar_t__) ; 
 struct sk_buff* stub1 (TYPE_4__*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct sk_buff *netem_dequeue(struct Qdisc *sch)
{
	struct netem_sched_data *q = qdisc_priv(sch);
	struct sk_buff *skb;

	if (sch->flags & TCQ_F_THROTTLED)
		return NULL;

	skb = q->qdisc->ops->peek(q->qdisc);
	if (skb) {
		const struct netem_skb_cb *cb = netem_skb_cb(skb);
		psched_time_t now = psched_get_time();

		/* if more time remaining? */
		if (cb->time_to_send <= now) {
			skb = qdisc_dequeue_peeked(q->qdisc);
			if (unlikely(!skb))
				return NULL;

#ifdef CONFIG_NET_CLS_ACT
			/*
			 * If it's at ingress let's pretend the delay is
			 * from the network (tstamp will be updated).
			 */
			if (G_TC_FROM(skb->tc_verd) & AT_INGRESS)
				skb->tstamp.tv64 = 0;
#endif
			pr_debug("netem_dequeue: return skb=%p\n", skb);
			sch->q.qlen--;
			return skb;
		}

		qdisc_watchdog_schedule(&q->watchdog, cb->time_to_send);
	}

	return NULL;
}