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
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct tc_service_curve {scalar_t__ m1; scalar_t__ m2; } ;
struct nlattr {int dummy; } ;
struct TYPE_8__ {scalar_t__ classid; } ;
struct hfsc_class {int cl_flags; int refcnt; scalar_t__ level; int /*<<< orphan*/  cl_cvtoff; int /*<<< orphan*/  cl_pcvtoff; int /*<<< orphan*/  children; int /*<<< orphan*/  siblings; TYPE_4__ cl_common; void* cf_tree; void* vt_tree; TYPE_2__* qdisc; struct hfsc_class* cl_parent; struct hfsc_sched* sched; int /*<<< orphan*/  rate_est; int /*<<< orphan*/  bstats; } ;
struct hfsc_sched {int /*<<< orphan*/  clhash; struct hfsc_class root; } ;
struct Qdisc {scalar_t__ handle; int /*<<< orphan*/  dev_queue; } ;
struct TYPE_6__ {scalar_t__ qlen; } ;
struct TYPE_7__ {TYPE_1__ q; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int ENOBUFS ; 
 int ENOENT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HFSC_FSC ; 
 int HFSC_RSC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 void* RB_ROOT ; 
 size_t TCA_HFSC_FSC ; 
 int /*<<< orphan*/  TCA_HFSC_MAX ; 
 size_t TCA_HFSC_RSC ; 
 size_t TCA_HFSC_USC ; 
 size_t TCA_OPTIONS ; 
 size_t TCA_RATE ; 
 scalar_t__ TC_H_MAJ (scalar_t__) ; 
 scalar_t__ TC_H_ROOT ; 
 int gen_new_estimator (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nlattr*) ; 
 int gen_replace_estimator (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nlattr*) ; 
 int /*<<< orphan*/  hfsc_adjust_levels (struct hfsc_class*) ; 
 int /*<<< orphan*/  hfsc_change_fsc (struct hfsc_class*,struct tc_service_curve*) ; 
 int /*<<< orphan*/  hfsc_change_rsc (struct hfsc_class*,struct tc_service_curve*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfsc_change_usc (struct hfsc_class*,struct tc_service_curve*,int /*<<< orphan*/ ) ; 
 struct hfsc_class* hfsc_find_class (scalar_t__,struct Qdisc*) ; 
 int /*<<< orphan*/  hfsc_policy ; 
 int /*<<< orphan*/  hfsc_purge_queue (struct Qdisc*,struct hfsc_class*) ; 
 int /*<<< orphan*/  kfree (struct hfsc_class*) ; 
 struct hfsc_class* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct tc_service_curve* nla_data (struct nlattr*) ; 
 int nla_parse_nested (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ) ; 
 TYPE_2__ noop_qdisc ; 
 int /*<<< orphan*/  pfifo_qdisc_ops ; 
 int /*<<< orphan*/  psched_get_time () ; 
 int /*<<< orphan*/  qdisc_class_hash_grow (struct Qdisc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qdisc_class_hash_insert (int /*<<< orphan*/ *,TYPE_4__*) ; 
 TYPE_2__* qdisc_create_dflt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  qdisc_dev (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_peek_len (TYPE_2__*) ; 
 struct hfsc_sched* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_root_sleeping_lock (struct Qdisc*) ; 
 int /*<<< orphan*/  sch_tree_lock (struct Qdisc*) ; 
 int /*<<< orphan*/  sch_tree_unlock (struct Qdisc*) ; 
 int /*<<< orphan*/  update_ed (struct hfsc_class*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_vf (struct hfsc_class*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hfsc_change_class(struct Qdisc *sch, u32 classid, u32 parentid,
		  struct nlattr **tca, unsigned long *arg)
{
	struct hfsc_sched *q = qdisc_priv(sch);
	struct hfsc_class *cl = (struct hfsc_class *)*arg;
	struct hfsc_class *parent = NULL;
	struct nlattr *opt = tca[TCA_OPTIONS];
	struct nlattr *tb[TCA_HFSC_MAX + 1];
	struct tc_service_curve *rsc = NULL, *fsc = NULL, *usc = NULL;
	u64 cur_time;
	int err;

	if (opt == NULL)
		return -EINVAL;

	err = nla_parse_nested(tb, TCA_HFSC_MAX, opt, hfsc_policy);
	if (err < 0)
		return err;

	if (tb[TCA_HFSC_RSC]) {
		rsc = nla_data(tb[TCA_HFSC_RSC]);
		if (rsc->m1 == 0 && rsc->m2 == 0)
			rsc = NULL;
	}

	if (tb[TCA_HFSC_FSC]) {
		fsc = nla_data(tb[TCA_HFSC_FSC]);
		if (fsc->m1 == 0 && fsc->m2 == 0)
			fsc = NULL;
	}

	if (tb[TCA_HFSC_USC]) {
		usc = nla_data(tb[TCA_HFSC_USC]);
		if (usc->m1 == 0 && usc->m2 == 0)
			usc = NULL;
	}

	if (cl != NULL) {
		if (parentid) {
			if (cl->cl_parent &&
			    cl->cl_parent->cl_common.classid != parentid)
				return -EINVAL;
			if (cl->cl_parent == NULL && parentid != TC_H_ROOT)
				return -EINVAL;
		}
		cur_time = psched_get_time();

		if (tca[TCA_RATE]) {
			err = gen_replace_estimator(&cl->bstats, &cl->rate_est,
					      qdisc_root_sleeping_lock(sch),
					      tca[TCA_RATE]);
			if (err)
				return err;
		}

		sch_tree_lock(sch);
		if (rsc != NULL)
			hfsc_change_rsc(cl, rsc, cur_time);
		if (fsc != NULL)
			hfsc_change_fsc(cl, fsc);
		if (usc != NULL)
			hfsc_change_usc(cl, usc, cur_time);

		if (cl->qdisc->q.qlen != 0) {
			if (cl->cl_flags & HFSC_RSC)
				update_ed(cl, qdisc_peek_len(cl->qdisc));
			if (cl->cl_flags & HFSC_FSC)
				update_vf(cl, 0, cur_time);
		}
		sch_tree_unlock(sch);

		return 0;
	}

	if (parentid == TC_H_ROOT)
		return -EEXIST;

	parent = &q->root;
	if (parentid) {
		parent = hfsc_find_class(parentid, sch);
		if (parent == NULL)
			return -ENOENT;
	}

	if (classid == 0 || TC_H_MAJ(classid ^ sch->handle) != 0)
		return -EINVAL;
	if (hfsc_find_class(classid, sch))
		return -EEXIST;

	if (rsc == NULL && fsc == NULL)
		return -EINVAL;

	cl = kzalloc(sizeof(struct hfsc_class), GFP_KERNEL);
	if (cl == NULL)
		return -ENOBUFS;

	if (tca[TCA_RATE]) {
		err = gen_new_estimator(&cl->bstats, &cl->rate_est,
					qdisc_root_sleeping_lock(sch),
					tca[TCA_RATE]);
		if (err) {
			kfree(cl);
			return err;
		}
	}

	if (rsc != NULL)
		hfsc_change_rsc(cl, rsc, 0);
	if (fsc != NULL)
		hfsc_change_fsc(cl, fsc);
	if (usc != NULL)
		hfsc_change_usc(cl, usc, 0);

	cl->cl_common.classid = classid;
	cl->refcnt    = 1;
	cl->sched     = q;
	cl->cl_parent = parent;
	cl->qdisc = qdisc_create_dflt(qdisc_dev(sch), sch->dev_queue,
				      &pfifo_qdisc_ops, classid);
	if (cl->qdisc == NULL)
		cl->qdisc = &noop_qdisc;
	INIT_LIST_HEAD(&cl->children);
	cl->vt_tree = RB_ROOT;
	cl->cf_tree = RB_ROOT;

	sch_tree_lock(sch);
	qdisc_class_hash_insert(&q->clhash, &cl->cl_common);
	list_add_tail(&cl->siblings, &parent->children);
	if (parent->level == 0)
		hfsc_purge_queue(sch, parent);
	hfsc_adjust_levels(parent);
	cl->cl_pcvtoff = parent->cl_cvtoff;
	sch_tree_unlock(sch);

	qdisc_class_hash_grow(sch, &q->clhash);

	*arg = (unsigned long)cl;
	return 0;
}