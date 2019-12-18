#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct sk_buff {int dummy; } ;
struct hfsc_sched {int /*<<< orphan*/  root; } ;
struct hfsc_class {int cl_flags; TYPE_4__* qdisc; int /*<<< orphan*/  cl_cumul; } ;
struct TYPE_9__ {scalar_t__ qlen; } ;
struct TYPE_7__ {int /*<<< orphan*/  overlimits; } ;
struct Qdisc {TYPE_3__ q; int /*<<< orphan*/  flags; TYPE_1__ qstats; } ;
struct TYPE_8__ {scalar_t__ qlen; } ;
struct TYPE_10__ {TYPE_2__ q; } ;

/* Variables and functions */
 int HFSC_RSC ; 
 int /*<<< orphan*/  TCQ_F_THROTTLED ; 
 struct hfsc_class* eltree_get_mindl (struct hfsc_sched*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfsc_schedule_watchdog (struct Qdisc*) ; 
 int /*<<< orphan*/  psched_get_time () ; 
 struct sk_buff* qdisc_dequeue_peeked (TYPE_4__*) ; 
 unsigned int qdisc_peek_len (TYPE_4__*) ; 
 scalar_t__ qdisc_pkt_len (struct sk_buff*) ; 
 struct hfsc_sched* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_warn_nonwc (char*,TYPE_4__*) ; 
 int /*<<< orphan*/  set_passive (struct hfsc_class*) ; 
 int /*<<< orphan*/  update_d (struct hfsc_class*,unsigned int) ; 
 int /*<<< orphan*/  update_ed (struct hfsc_class*,unsigned int) ; 
 int /*<<< orphan*/  update_vf (struct hfsc_class*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct hfsc_class* vttree_get_minvt (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *
hfsc_dequeue(struct Qdisc *sch)
{
	struct hfsc_sched *q = qdisc_priv(sch);
	struct hfsc_class *cl;
	struct sk_buff *skb;
	u64 cur_time;
	unsigned int next_len;
	int realtime = 0;

	if (sch->q.qlen == 0)
		return NULL;

	cur_time = psched_get_time();

	/*
	 * if there are eligible classes, use real-time criteria.
	 * find the class with the minimum deadline among
	 * the eligible classes.
	 */
	if ((cl = eltree_get_mindl(q, cur_time)) != NULL) {
		realtime = 1;
	} else {
		/*
		 * use link-sharing criteria
		 * get the class with the minimum vt in the hierarchy
		 */
		cl = vttree_get_minvt(&q->root, cur_time);
		if (cl == NULL) {
			sch->qstats.overlimits++;
			hfsc_schedule_watchdog(sch);
			return NULL;
		}
	}

	skb = qdisc_dequeue_peeked(cl->qdisc);
	if (skb == NULL) {
		qdisc_warn_nonwc("HFSC", cl->qdisc);
		return NULL;
	}

	update_vf(cl, qdisc_pkt_len(skb), cur_time);
	if (realtime)
		cl->cl_cumul += qdisc_pkt_len(skb);

	if (cl->qdisc->q.qlen != 0) {
		if (cl->cl_flags & HFSC_RSC) {
			/* update ed */
			next_len = qdisc_peek_len(cl->qdisc);
			if (realtime)
				update_ed(cl, next_len);
			else
				update_d(cl, next_len);
		}
	} else {
		/* the class becomes passive */
		set_passive(cl);
	}

	sch->flags &= ~TCQ_F_THROTTLED;
	sch->q.qlen--;

	return skb;
}