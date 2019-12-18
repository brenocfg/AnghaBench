#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct htb_sched {scalar_t__ drops; } ;
struct TYPE_5__ {int /*<<< orphan*/  drop_list; TYPE_3__* q; } ;
struct TYPE_6__ {TYPE_1__ leaf; } ;
struct htb_class {int prio_activity; int prio; TYPE_2__ un; scalar_t__ level; } ;
struct TYPE_8__ {int /*<<< orphan*/  qlen; } ;
struct TYPE_7__ {TYPE_4__ q; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  htb_activate_prios (struct htb_sched*,struct htb_class*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static inline void htb_activate(struct htb_sched *q, struct htb_class *cl)
{
	WARN_ON(cl->level || !cl->un.leaf.q || !cl->un.leaf.q->q.qlen);

	if (!cl->prio_activity) {
		cl->prio_activity = 1 << cl->prio;
		htb_activate_prios(q, cl);
		list_add_tail(&cl->un.leaf.drop_list,
			      q->drops + cl->prio);
	}
}