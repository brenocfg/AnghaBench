#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct htb_sched {scalar_t__ wait_pq; } ;
struct TYPE_3__ {struct Qdisc* q; int /*<<< orphan*/  drop_list; } ;
struct TYPE_4__ {TYPE_1__ leaf; int /*<<< orphan*/  inner; } ;
struct htb_class {scalar_t__ cmode; int /*<<< orphan*/  t_c; int /*<<< orphan*/  cbuffer; int /*<<< orphan*/  ctokens; int /*<<< orphan*/  buffer; int /*<<< orphan*/  tokens; TYPE_2__ un; scalar_t__ level; int /*<<< orphan*/  pq_node; scalar_t__ prio_activity; struct htb_class* parent; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 scalar_t__ HTB_CAN_SEND ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  htb_safe_rb_erase (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct Qdisc noop_qdisc ; 
 int /*<<< orphan*/  psched_get_time () ; 

__attribute__((used)) static void htb_parent_to_leaf(struct htb_sched *q, struct htb_class *cl,
			       struct Qdisc *new_q)
{
	struct htb_class *parent = cl->parent;

	WARN_ON(cl->level || !cl->un.leaf.q || cl->prio_activity);

	if (parent->cmode != HTB_CAN_SEND)
		htb_safe_rb_erase(&parent->pq_node, q->wait_pq + parent->level);

	parent->level = 0;
	memset(&parent->un.inner, 0, sizeof(parent->un.inner));
	INIT_LIST_HEAD(&parent->un.leaf.drop_list);
	parent->un.leaf.q = new_q ? new_q : &noop_qdisc;
	parent->tokens = parent->buffer;
	parent->ctokens = parent->cbuffer;
	parent->t_c = psched_get_time();
	parent->cmode = HTB_CAN_SEND;
}