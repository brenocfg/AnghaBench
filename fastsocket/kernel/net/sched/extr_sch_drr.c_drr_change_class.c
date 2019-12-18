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
typedef  scalar_t__ u32 ;
struct nlattr {int dummy; } ;
struct drr_sched {int /*<<< orphan*/  clhash; } ;
struct TYPE_2__ {scalar_t__ classid; } ;
struct drr_class {int refcnt; TYPE_1__ common; int /*<<< orphan*/ * qdisc; int /*<<< orphan*/  rate_est; int /*<<< orphan*/  bstats; scalar_t__ quantum; } ;
struct Qdisc {int /*<<< orphan*/  dev_queue; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  TCA_DRR_MAX ; 
 size_t TCA_DRR_QUANTUM ; 
 size_t TCA_OPTIONS ; 
 size_t TCA_RATE ; 
 int /*<<< orphan*/  drr_policy ; 
 int gen_replace_estimator (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nlattr*) ; 
 int /*<<< orphan*/  kfree (struct drr_class*) ; 
 struct drr_class* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_get_u32 (struct nlattr*) ; 
 int nla_parse_nested (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  noop_qdisc ; 
 int /*<<< orphan*/  pfifo_qdisc_ops ; 
 scalar_t__ psched_mtu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qdisc_class_hash_grow (struct Qdisc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qdisc_class_hash_insert (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * qdisc_create_dflt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  qdisc_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qdisc_dev (struct Qdisc*) ; 
 struct drr_sched* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_root_sleeping_lock (struct Qdisc*) ; 
 int /*<<< orphan*/  sch_tree_lock (struct Qdisc*) ; 
 int /*<<< orphan*/  sch_tree_unlock (struct Qdisc*) ; 

__attribute__((used)) static int drr_change_class(struct Qdisc *sch, u32 classid, u32 parentid,
			    struct nlattr **tca, unsigned long *arg)
{
	struct drr_sched *q = qdisc_priv(sch);
	struct drr_class *cl = (struct drr_class *)*arg;
	struct nlattr *opt = tca[TCA_OPTIONS];
	struct nlattr *tb[TCA_DRR_MAX + 1];
	u32 quantum;
	int err;

	if (!opt)
		return -EINVAL;

	err = nla_parse_nested(tb, TCA_DRR_MAX, opt, drr_policy);
	if (err < 0)
		return err;

	if (tb[TCA_DRR_QUANTUM]) {
		quantum = nla_get_u32(tb[TCA_DRR_QUANTUM]);
		if (quantum == 0)
			return -EINVAL;
	} else
		quantum = psched_mtu(qdisc_dev(sch));

	if (cl != NULL) {
		if (tca[TCA_RATE]) {
			err = gen_replace_estimator(&cl->bstats, &cl->rate_est,
						    qdisc_root_sleeping_lock(sch),
						    tca[TCA_RATE]);
			if (err)
				return err;
		}

		sch_tree_lock(sch);
		if (tb[TCA_DRR_QUANTUM])
			cl->quantum = quantum;
		sch_tree_unlock(sch);

		return 0;
	}

	cl = kzalloc(sizeof(struct drr_class), GFP_KERNEL);
	if (cl == NULL)
		return -ENOBUFS;

	cl->refcnt	   = 1;
	cl->common.classid = classid;
	cl->quantum	   = quantum;
	cl->qdisc	   = qdisc_create_dflt(qdisc_dev(sch), sch->dev_queue,
					       &pfifo_qdisc_ops, classid);
	if (cl->qdisc == NULL)
		cl->qdisc = &noop_qdisc;

	if (tca[TCA_RATE]) {
		err = gen_replace_estimator(&cl->bstats, &cl->rate_est,
					    qdisc_root_sleeping_lock(sch),
					    tca[TCA_RATE]);
		if (err) {
			qdisc_destroy(cl->qdisc);
			kfree(cl);
			return err;
		}
	}

	sch_tree_lock(sch);
	qdisc_class_hash_insert(&q->clhash, &cl->common);
	sch_tree_unlock(sch);

	qdisc_class_hash_grow(sch, &q->clhash);

	*arg = (unsigned long)cl;
	return 0;
}