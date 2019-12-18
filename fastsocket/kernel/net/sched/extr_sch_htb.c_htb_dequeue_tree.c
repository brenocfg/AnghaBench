#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct htb_sched {int* row_mask; scalar_t__* ptr; scalar_t__* last_ptr_id; scalar_t__* row; } ;
struct TYPE_13__ {scalar_t__* deficit; TYPE_7__* q; } ;
struct TYPE_14__ {TYPE_5__ leaf; } ;
struct htb_class {scalar_t__ quantum; TYPE_6__ un; TYPE_3__* parent; } ;
struct TYPE_12__ {scalar_t__ qlen; } ;
struct TYPE_15__ {TYPE_4__ q; struct sk_buff* (* dequeue ) (TYPE_7__*) ;} ;
struct TYPE_9__ {scalar_t__ ptr; } ;
struct TYPE_10__ {TYPE_1__ inner; } ;
struct TYPE_11__ {TYPE_2__ un; } ;

/* Variables and functions */
 int /*<<< orphan*/  htb_charge_class (struct htb_sched*,struct htb_class*,int,struct sk_buff*) ; 
 int /*<<< orphan*/  htb_deactivate (struct htb_sched*,struct htb_class*) ; 
 struct htb_class* htb_lookup_leaf (scalar_t__,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  htb_next_rb_node (scalar_t__) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 scalar_t__ qdisc_pkt_len (struct sk_buff*) ; 
 int /*<<< orphan*/  qdisc_warn_nonwc (char*,TYPE_7__*) ; 
 struct sk_buff* stub1 (TYPE_7__*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct sk_buff *htb_dequeue_tree(struct htb_sched *q, int prio,
					int level)
{
	struct sk_buff *skb = NULL;
	struct htb_class *cl, *start;
	/* look initial class up in the row */
	start = cl = htb_lookup_leaf(q->row[level] + prio, prio,
				     q->ptr[level] + prio,
				     q->last_ptr_id[level] + prio);

	do {
next:
		if (unlikely(!cl))
			return NULL;

		/* class can be empty - it is unlikely but can be true if leaf
		   qdisc drops packets in enqueue routine or if someone used
		   graft operation on the leaf since last dequeue;
		   simply deactivate and skip such class */
		if (unlikely(cl->un.leaf.q->q.qlen == 0)) {
			struct htb_class *next;
			htb_deactivate(q, cl);

			/* row/level might become empty */
			if ((q->row_mask[level] & (1 << prio)) == 0)
				return NULL;

			next = htb_lookup_leaf(q->row[level] + prio,
					       prio, q->ptr[level] + prio,
					       q->last_ptr_id[level] + prio);

			if (cl == start)	/* fix start if we just deleted it */
				start = next;
			cl = next;
			goto next;
		}

		skb = cl->un.leaf.q->dequeue(cl->un.leaf.q);
		if (likely(skb != NULL))
			break;

		qdisc_warn_nonwc("htb", cl->un.leaf.q);
		htb_next_rb_node((level ? cl->parent->un.inner.ptr : q->
				  ptr[0]) + prio);
		cl = htb_lookup_leaf(q->row[level] + prio, prio,
				     q->ptr[level] + prio,
				     q->last_ptr_id[level] + prio);

	} while (cl != start);

	if (likely(skb != NULL)) {
		cl->un.leaf.deficit[level] -= qdisc_pkt_len(skb);
		if (cl->un.leaf.deficit[level] < 0) {
			cl->un.leaf.deficit[level] += cl->quantum;
			htb_next_rb_node((level ? cl->parent->un.inner.ptr : q->
					  ptr[0]) + prio);
		}
		/* this used to be after charge_class but this constelation
		   gives us slightly better performance */
		if (!cl->un.leaf.q->q.qlen)
			htb_deactivate(q, cl);
		htb_charge_class(q, cl, level, skb);
	}
	return skb;
}