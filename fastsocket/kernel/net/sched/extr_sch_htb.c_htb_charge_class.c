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
struct sk_buff {int dummy; } ;
struct htb_sched {scalar_t__ wait_pq; int /*<<< orphan*/  now; } ;
struct TYPE_5__ {int bytes; int packets; } ;
struct TYPE_4__ {int /*<<< orphan*/  borrows; int /*<<< orphan*/  lends; } ;
struct htb_class {int level; long tokens; int cmode; struct htb_class* parent; TYPE_2__ bstats; int /*<<< orphan*/  pq_node; int /*<<< orphan*/  t_c; TYPE_1__ xstats; int /*<<< orphan*/  mbuffer; } ;
typedef  enum htb_cmode { ____Placeholder_htb_cmode } htb_cmode ;
struct TYPE_6__ {int gso_segs; } ;

/* Variables and functions */
 int HTB_CAN_SEND ; 
 int /*<<< orphan*/  htb_accnt_ctokens (struct htb_class*,int,long) ; 
 int /*<<< orphan*/  htb_accnt_tokens (struct htb_class*,int,long) ; 
 int /*<<< orphan*/  htb_add_to_wait_tree (struct htb_sched*,struct htb_class*,long) ; 
 int /*<<< orphan*/  htb_change_class_mode (struct htb_sched*,struct htb_class*,long*) ; 
 int /*<<< orphan*/  htb_safe_rb_erase (int /*<<< orphan*/ *,scalar_t__) ; 
 long psched_tdiff_bounded (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qdisc_pkt_len (struct sk_buff*) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 TYPE_3__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static void htb_charge_class(struct htb_sched *q, struct htb_class *cl,
			     int level, struct sk_buff *skb)
{
	int bytes = qdisc_pkt_len(skb);
	enum htb_cmode old_mode;
	long diff;

	while (cl) {
		diff = psched_tdiff_bounded(q->now, cl->t_c, cl->mbuffer);
		if (cl->level >= level) {
			if (cl->level == level)
				cl->xstats.lends++;
			htb_accnt_tokens(cl, bytes, diff);
		} else {
			cl->xstats.borrows++;
			cl->tokens += diff;	/* we moved t_c; update tokens */
		}
		htb_accnt_ctokens(cl, bytes, diff);
		cl->t_c = q->now;

		old_mode = cl->cmode;
		diff = 0;
		htb_change_class_mode(q, cl, &diff);
		if (old_mode != cl->cmode) {
			if (old_mode != HTB_CAN_SEND)
				htb_safe_rb_erase(&cl->pq_node, q->wait_pq + cl->level);
			if (cl->cmode != HTB_CAN_SEND)
				htb_add_to_wait_tree(q, cl, diff);
		}

		/* update byte stats except for leaves which are already updated */
		if (cl->level) {
			cl->bstats.bytes += bytes;
			cl->bstats.packets += skb_is_gso(skb)?
					skb_shinfo(skb)->gso_segs:1;
		}
		cl = cl->parent;
	}
}