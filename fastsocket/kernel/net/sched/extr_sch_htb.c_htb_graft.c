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
struct TYPE_6__ {struct Qdisc* q; } ;
struct TYPE_7__ {TYPE_2__ leaf; } ;
struct TYPE_5__ {int /*<<< orphan*/  classid; } ;
struct htb_class {TYPE_3__ un; TYPE_1__ common; scalar_t__ level; } ;
struct TYPE_8__ {int /*<<< orphan*/  qlen; } ;
struct Qdisc {TYPE_4__ q; int /*<<< orphan*/  dev_queue; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  pfifo_qdisc_ops ; 
 struct Qdisc* qdisc_create_dflt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qdisc_dev (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_reset (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_tree_decrease_qlen (struct Qdisc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sch_tree_lock (struct Qdisc*) ; 
 int /*<<< orphan*/  sch_tree_unlock (struct Qdisc*) ; 

__attribute__((used)) static int htb_graft(struct Qdisc *sch, unsigned long arg, struct Qdisc *new,
		     struct Qdisc **old)
{
	struct htb_class *cl = (struct htb_class *)arg;

	if (cl->level)
		return -EINVAL;
	if (new == NULL &&
	    (new = qdisc_create_dflt(qdisc_dev(sch), sch->dev_queue,
				     &pfifo_qdisc_ops,
				     cl->common.classid)) == NULL)
		return -ENOBUFS;

	sch_tree_lock(sch);
	*old = cl->un.leaf.q;
	cl->un.leaf.q = new;
	if (*old != NULL) {
		qdisc_tree_decrease_qlen(*old, (*old)->q.qlen);
		qdisc_reset(*old);
	}
	sch_tree_unlock(sch);
	return 0;
}