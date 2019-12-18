#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tc_netem_qopt {int /*<<< orphan*/  duplicate; int /*<<< orphan*/  loss; scalar_t__ gap; int /*<<< orphan*/  limit; int /*<<< orphan*/  jitter; int /*<<< orphan*/  latency; } ;
struct nlattr {int dummy; } ;
struct netem_sched_data {int /*<<< orphan*/  reorder; scalar_t__ gap; int /*<<< orphan*/  duplicate; int /*<<< orphan*/  loss; scalar_t__ counter; int /*<<< orphan*/  limit; int /*<<< orphan*/  jitter; int /*<<< orphan*/  latency; int /*<<< orphan*/  qdisc; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t TCA_NETEM_CORR ; 
 size_t TCA_NETEM_CORRUPT ; 
 size_t TCA_NETEM_DELAY_DIST ; 
 int /*<<< orphan*/  TCA_NETEM_MAX ; 
 size_t TCA_NETEM_REORDER ; 
 int fifo_set_limit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_correlation (struct Qdisc*,struct nlattr*) ; 
 int /*<<< orphan*/  get_corrupt (struct Qdisc*,struct nlattr*) ; 
 int get_dist_table (struct Qdisc*,struct nlattr*) ; 
 int /*<<< orphan*/  get_reorder (struct Qdisc*,struct nlattr*) ; 
 int /*<<< orphan*/  netem_policy ; 
 struct tc_netem_qopt* nla_data (struct nlattr*) ; 
 int parse_attr (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 struct netem_sched_data* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static int netem_change(struct Qdisc *sch, struct nlattr *opt)
{
	struct netem_sched_data *q = qdisc_priv(sch);
	struct nlattr *tb[TCA_NETEM_MAX + 1];
	struct tc_netem_qopt *qopt;
	int ret;

	if (opt == NULL)
		return -EINVAL;

	qopt = nla_data(opt);
	ret = parse_attr(tb, TCA_NETEM_MAX, opt, netem_policy, sizeof(*qopt));
	if (ret < 0)
		return ret;

	ret = fifo_set_limit(q->qdisc, qopt->limit);
	if (ret) {
		pr_debug("netem: can't set fifo limit\n");
		return ret;
	}

	q->latency = qopt->latency;
	q->jitter = qopt->jitter;
	q->limit = qopt->limit;
	q->gap = qopt->gap;
	q->counter = 0;
	q->loss = qopt->loss;
	q->duplicate = qopt->duplicate;

	/* for compatibility with earlier versions.
	 * if gap is set, need to assume 100% probability
	 */
	if (q->gap)
		q->reorder = ~0;

	if (tb[TCA_NETEM_CORR])
		get_correlation(sch, tb[TCA_NETEM_CORR]);

	if (tb[TCA_NETEM_DELAY_DIST]) {
		ret = get_dist_table(sch, tb[TCA_NETEM_DELAY_DIST]);
		if (ret)
			return ret;
	}

	if (tb[TCA_NETEM_REORDER])
		get_reorder(sch, tb[TCA_NETEM_REORDER]);

	if (tb[TCA_NETEM_CORRUPT])
		get_corrupt(sch, tb[TCA_NETEM_CORRUPT]);

	return 0;
}