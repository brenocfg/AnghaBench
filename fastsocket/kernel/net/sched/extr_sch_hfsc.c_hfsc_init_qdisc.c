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
struct tc_hfsc_qopt {int /*<<< orphan*/  defcls; } ;
struct nlattr {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  classid; } ;
struct TYPE_3__ {int refcnt; TYPE_2__ cl_common; void* cf_tree; void* vt_tree; int /*<<< orphan*/  children; int /*<<< orphan*/ * qdisc; struct hfsc_sched* sched; } ;
struct hfsc_sched {int /*<<< orphan*/  watchdog; int /*<<< orphan*/  clhash; TYPE_1__ root; int /*<<< orphan*/  droplist; void* eligible; int /*<<< orphan*/  defcls; } ;
struct Qdisc {int /*<<< orphan*/  handle; int /*<<< orphan*/  dev_queue; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 void* RB_ROOT ; 
 struct tc_hfsc_qopt* nla_data (struct nlattr*) ; 
 int nla_len (struct nlattr*) ; 
 int /*<<< orphan*/  noop_qdisc ; 
 int /*<<< orphan*/  pfifo_qdisc_ops ; 
 int /*<<< orphan*/  qdisc_class_hash_grow (struct Qdisc*,int /*<<< orphan*/ *) ; 
 int qdisc_class_hash_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qdisc_class_hash_insert (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/ * qdisc_create_dflt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qdisc_dev (struct Qdisc*) ; 
 struct hfsc_sched* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_watchdog_init (int /*<<< orphan*/ *,struct Qdisc*) ; 

__attribute__((used)) static int
hfsc_init_qdisc(struct Qdisc *sch, struct nlattr *opt)
{
	struct hfsc_sched *q = qdisc_priv(sch);
	struct tc_hfsc_qopt *qopt;
	int err;

	if (opt == NULL || nla_len(opt) < sizeof(*qopt))
		return -EINVAL;
	qopt = nla_data(opt);

	q->defcls = qopt->defcls;
	err = qdisc_class_hash_init(&q->clhash);
	if (err < 0)
		return err;
	q->eligible = RB_ROOT;
	INIT_LIST_HEAD(&q->droplist);

	q->root.cl_common.classid = sch->handle;
	q->root.refcnt  = 1;
	q->root.sched   = q;
	q->root.qdisc = qdisc_create_dflt(qdisc_dev(sch), sch->dev_queue,
					  &pfifo_qdisc_ops,
					  sch->handle);
	if (q->root.qdisc == NULL)
		q->root.qdisc = &noop_qdisc;
	INIT_LIST_HEAD(&q->root.children);
	q->root.vt_tree = RB_ROOT;
	q->root.cf_tree = RB_ROOT;

	qdisc_class_hash_insert(&q->clhash, &q->root.cl_common);
	qdisc_class_hash_grow(sch, &q->clhash);

	qdisc_watchdog_init(&q->watchdog, sch);

	return 0;
}