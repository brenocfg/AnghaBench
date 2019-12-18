#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tbf_sched_data {scalar_t__ max_size; int /*<<< orphan*/  qdisc; } ;
struct sk_buff {scalar_t__ len; struct sk_buff* next; } ;
struct TYPE_5__ {int qlen; } ;
struct TYPE_4__ {int /*<<< orphan*/  drops; } ;
struct Qdisc {TYPE_2__ q; TYPE_1__ qstats; } ;
struct TYPE_6__ {scalar_t__ pkt_len; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct sk_buff*) ; 
 int NETIF_F_GSO_MASK ; 
 int NET_XMIT_DROP ; 
 int NET_XMIT_SUCCESS ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ net_xmit_drop_count (int) ; 
 int netif_skb_features (struct sk_buff*) ; 
 int qdisc_enqueue (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct tbf_sched_data* qdisc_priv (struct Qdisc*) ; 
 int qdisc_reshape_fail (struct sk_buff*,struct Qdisc*) ; 
 TYPE_3__* qdisc_skb_cb (struct sk_buff*) ; 
 int /*<<< orphan*/  qdisc_tree_decrease_qlen (struct Qdisc*,int) ; 
 struct sk_buff* skb_gso_segment (struct sk_buff*,int) ; 

__attribute__((used)) static int tbf_segment(struct sk_buff *skb, struct Qdisc *sch)
{
	struct tbf_sched_data *q = qdisc_priv(sch);
	struct sk_buff *segs, *nskb;
	int features = netif_skb_features(skb);
	int ret, nb;

	segs = skb_gso_segment(skb, features & ~NETIF_F_GSO_MASK);

	if (IS_ERR_OR_NULL(segs))
		return qdisc_reshape_fail(skb, sch);

	nb = 0;
	while (segs) {
		nskb = segs->next;
		segs->next = NULL;
		if (likely(segs->len <= q->max_size)) {
			qdisc_skb_cb(segs)->pkt_len = segs->len;
			ret = qdisc_enqueue(segs, q->qdisc);
		} else {
			ret = qdisc_reshape_fail(skb, sch);
		}
		if (ret != NET_XMIT_SUCCESS) {
			if (net_xmit_drop_count(ret))
				sch->qstats.drops++;
		} else {
			nb++;
		}
		segs = nskb;
	}
	sch->q.qlen += nb;
	if (nb > 1)
		qdisc_tree_decrease_qlen(sch, 1 - nb);
	consume_skb(skb);
	return nb > 0 ? NET_XMIT_SUCCESS : NET_XMIT_DROP;
}