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
struct qdisc_size_table {int dummy; } ;
struct nlattr {int dummy; } ;
struct Qdisc {int flags; int /*<<< orphan*/  rate_est; int /*<<< orphan*/  bstats; struct qdisc_size_table* stab; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* change ) (struct Qdisc*,struct nlattr*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct qdisc_size_table*) ; 
 int PTR_ERR (struct qdisc_size_table*) ; 
 size_t TCA_OPTIONS ; 
 size_t TCA_RATE ; 
 size_t TCA_STAB ; 
 int TCQ_F_MQROOT ; 
 int /*<<< orphan*/  gen_replace_estimator (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nlattr*) ; 
 struct qdisc_size_table* qdisc_get_stab (struct nlattr*) ; 
 int /*<<< orphan*/  qdisc_put_stab (struct qdisc_size_table*) ; 
 int /*<<< orphan*/  qdisc_root_sleeping_lock (struct Qdisc*) ; 
 int stub1 (struct Qdisc*,struct nlattr*) ; 

__attribute__((used)) static int qdisc_change(struct Qdisc *sch, struct nlattr **tca)
{
	struct qdisc_size_table *stab = NULL;
	int err = 0;

	if (tca[TCA_OPTIONS]) {
		if (sch->ops->change == NULL)
			return -EINVAL;
		err = sch->ops->change(sch, tca[TCA_OPTIONS]);
		if (err)
			return err;
	}

	if (tca[TCA_STAB]) {
		stab = qdisc_get_stab(tca[TCA_STAB]);
		if (IS_ERR(stab))
			return PTR_ERR(stab);
	}

	qdisc_put_stab(sch->stab);
	sch->stab = stab;

	if (tca[TCA_RATE]) {
		/* NB: ignores errors from replace_estimator
		   because change can't be undone. */
		if (sch->flags & TCQ_F_MQROOT)
			goto out;
		gen_replace_estimator(&sch->bstats, &sch->rate_est,
					    qdisc_root_sleeping_lock(sch),
					    tca[TCA_RATE]);
	}
out:
	return 0;
}