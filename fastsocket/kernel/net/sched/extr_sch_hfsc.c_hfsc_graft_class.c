#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  classid; } ;
struct hfsc_class {scalar_t__ level; struct Qdisc* qdisc; TYPE_1__ cl_common; } ;
struct Qdisc {int /*<<< orphan*/  dev_queue; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  hfsc_purge_queue (struct Qdisc*,struct hfsc_class*) ; 
 struct Qdisc noop_qdisc ; 
 int /*<<< orphan*/  pfifo_qdisc_ops ; 
 struct Qdisc* qdisc_create_dflt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qdisc_dev (struct Qdisc*) ; 
 int /*<<< orphan*/  sch_tree_lock (struct Qdisc*) ; 
 int /*<<< orphan*/  sch_tree_unlock (struct Qdisc*) ; 

__attribute__((used)) static int
hfsc_graft_class(struct Qdisc *sch, unsigned long arg, struct Qdisc *new,
		 struct Qdisc **old)
{
	struct hfsc_class *cl = (struct hfsc_class *)arg;

	if (cl->level > 0)
		return -EINVAL;
	if (new == NULL) {
		new = qdisc_create_dflt(qdisc_dev(sch), sch->dev_queue,
					&pfifo_qdisc_ops,
					cl->cl_common.classid);
		if (new == NULL)
			new = &noop_qdisc;
	}

	sch_tree_lock(sch);
	hfsc_purge_queue(sch, cl);
	*old = cl->qdisc;
	cl->qdisc = new;
	sch_tree_unlock(sch);
	return 0;
}