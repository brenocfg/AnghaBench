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
struct htb_sched {int dummy; } ;
struct TYPE_6__ {TYPE_4__* feed; int /*<<< orphan*/ ** ptr; int /*<<< orphan*/ * last_ptr_id; } ;
struct TYPE_7__ {TYPE_2__ inner; } ;
struct TYPE_5__ {int /*<<< orphan*/  classid; } ;
struct htb_class {long prio_activity; scalar_t__ cmode; struct htb_class* parent; TYPE_3__ un; int /*<<< orphan*/ * node; TYPE_1__ common; } ;
struct TYPE_8__ {int /*<<< orphan*/  rb_node; } ;

/* Variables and functions */
 scalar_t__ HTB_CAN_SEND ; 
 scalar_t__ HTB_MAY_BORROW ; 
 int ffz (long) ; 
 int /*<<< orphan*/  htb_remove_class_from_row (struct htb_sched*,struct htb_class*,long) ; 
 int /*<<< orphan*/  htb_safe_rb_erase (int /*<<< orphan*/ *,TYPE_4__*) ; 

__attribute__((used)) static void htb_deactivate_prios(struct htb_sched *q, struct htb_class *cl)
{
	struct htb_class *p = cl->parent;
	long m, mask = cl->prio_activity;

	while (cl->cmode == HTB_MAY_BORROW && p && mask) {
		m = mask;
		mask = 0;
		while (m) {
			int prio = ffz(~m);
			m &= ~(1 << prio);

			if (p->un.inner.ptr[prio] == cl->node + prio) {
				/* we are removing child which is pointed to from
				   parent feed - forget the pointer but remember
				   classid */
				p->un.inner.last_ptr_id[prio] = cl->common.classid;
				p->un.inner.ptr[prio] = NULL;
			}

			htb_safe_rb_erase(cl->node + prio, p->un.inner.feed + prio);

			if (!p->un.inner.feed[prio].rb_node)
				mask |= 1 << prio;
		}

		p->prio_activity &= ~mask;
		cl = p;
		p = cl->parent;

	}
	if (cl->cmode == HTB_CAN_SEND && mask)
		htb_remove_class_from_row(q, cl, mask);
}