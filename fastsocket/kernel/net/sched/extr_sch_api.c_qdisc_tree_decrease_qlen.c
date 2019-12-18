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
typedef  scalar_t__ u32 ;
struct Qdisc_class_ops {unsigned long (* get ) (struct Qdisc*,scalar_t__) ;int /*<<< orphan*/  (* put ) (struct Qdisc*,unsigned long) ;int /*<<< orphan*/  (* qlen_notify ) (struct Qdisc*,unsigned long) ;} ;
struct TYPE_4__ {unsigned int qlen; } ;
struct Qdisc {scalar_t__ parent; TYPE_2__ q; TYPE_1__* ops; } ;
struct TYPE_3__ {struct Qdisc_class_ops* cl_ops; } ;

/* Variables and functions */
 scalar_t__ TC_H_INGRESS ; 
 scalar_t__ TC_H_MAJ (scalar_t__) ; 
 scalar_t__ TC_H_ROOT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  qdisc_dev (struct Qdisc*) ; 
 struct Qdisc* qdisc_lookup (int /*<<< orphan*/ ,scalar_t__) ; 
 unsigned long stub1 (struct Qdisc*,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (struct Qdisc*,unsigned long) ; 
 int /*<<< orphan*/  stub3 (struct Qdisc*,unsigned long) ; 

void qdisc_tree_decrease_qlen(struct Qdisc *sch, unsigned int n)
{
	const struct Qdisc_class_ops *cops;
	unsigned long cl;
	u32 parentid;

	if (n == 0)
		return;
	while ((parentid = sch->parent)) {
		if (TC_H_MAJ(parentid) == TC_H_MAJ(TC_H_INGRESS))
			return;

		sch = qdisc_lookup(qdisc_dev(sch), TC_H_MAJ(parentid));
		if (sch == NULL) {
			WARN_ON(parentid != TC_H_ROOT);
			return;
		}
		cops = sch->ops->cl_ops;
		if (cops->qlen_notify) {
			cl = cops->get(sch, parentid);
			cops->qlen_notify(sch, cl);
			cops->put(sch, cl);
		}
		sch->q.qlen -= n;
	}
}