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
struct Qdisc_ops {struct Qdisc_ops* next; struct Qdisc_class_ops* cl_ops; int /*<<< orphan*/ * dequeue; int /*<<< orphan*/ * peek; int /*<<< orphan*/ * enqueue; int /*<<< orphan*/  id; } ;
struct Qdisc_class_ops {scalar_t__ unbind_tcf; scalar_t__ bind_tcf; scalar_t__ tcf_chain; scalar_t__ put; scalar_t__ get; } ;
struct TYPE_2__ {int /*<<< orphan*/ * dequeue; int /*<<< orphan*/ * peek; int /*<<< orphan*/ * enqueue; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 TYPE_1__ noop_qdisc_ops ; 
 struct Qdisc_ops* qdisc_base ; 
 int /*<<< orphan*/  qdisc_mod_lock ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

int register_qdisc(struct Qdisc_ops *qops)
{
	struct Qdisc_ops *q, **qp;
	int rc = -EEXIST;

	write_lock(&qdisc_mod_lock);
	for (qp = &qdisc_base; (q = *qp) != NULL; qp = &q->next)
		if (!strcmp(qops->id, q->id))
			goto out;

	if (qops->enqueue == NULL)
		qops->enqueue = noop_qdisc_ops.enqueue;
	if (qops->peek == NULL) {
		if (qops->dequeue == NULL)
			qops->peek = noop_qdisc_ops.peek;
		else
			goto out_einval;
	}
	if (qops->dequeue == NULL)
		qops->dequeue = noop_qdisc_ops.dequeue;

	if (qops->cl_ops) {
		const struct Qdisc_class_ops *cops = qops->cl_ops;

		if (!(cops->get && cops->put))
			goto out_einval;

		if (cops->tcf_chain && !(cops->bind_tcf && cops->unbind_tcf))
			goto out_einval;
	}

	qops->next = NULL;
	*qp = qops;
	rc = 0;
out:
	write_unlock(&qdisc_mod_lock);
	return rc;

out_einval:
	rc = -EINVAL;
	goto out;
}