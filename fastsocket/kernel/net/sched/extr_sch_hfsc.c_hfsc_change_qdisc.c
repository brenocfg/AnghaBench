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
struct tc_hfsc_qopt {int /*<<< orphan*/  defcls; } ;
struct nlattr {int dummy; } ;
struct hfsc_sched {int /*<<< orphan*/  defcls; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct tc_hfsc_qopt* nla_data (struct nlattr*) ; 
 int nla_len (struct nlattr*) ; 
 struct hfsc_sched* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  sch_tree_lock (struct Qdisc*) ; 
 int /*<<< orphan*/  sch_tree_unlock (struct Qdisc*) ; 

__attribute__((used)) static int
hfsc_change_qdisc(struct Qdisc *sch, struct nlattr *opt)
{
	struct hfsc_sched *q = qdisc_priv(sch);
	struct tc_hfsc_qopt *qopt;

	if (opt == NULL || nla_len(opt) < sizeof(*qopt))
		return -EINVAL;
	qopt = nla_data(opt);

	sch_tree_lock(sch);
	q->defcls = qopt->defcls;
	sch_tree_unlock(sch);

	return 0;
}