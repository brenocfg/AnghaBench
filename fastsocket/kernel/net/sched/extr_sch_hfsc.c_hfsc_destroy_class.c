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
struct hfsc_class {int /*<<< orphan*/  rate_est; int /*<<< orphan*/  bstats; int /*<<< orphan*/  qdisc; int /*<<< orphan*/  filter_list; } ;
struct hfsc_sched {struct hfsc_class root; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gen_kill_estimator (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct hfsc_class*) ; 
 int /*<<< orphan*/  qdisc_destroy (int /*<<< orphan*/ ) ; 
 struct hfsc_sched* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  tcf_destroy_chain (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
hfsc_destroy_class(struct Qdisc *sch, struct hfsc_class *cl)
{
	struct hfsc_sched *q = qdisc_priv(sch);

	tcf_destroy_chain(&cl->filter_list);
	qdisc_destroy(cl->qdisc);
	gen_kill_estimator(&cl->bstats, &cl->rate_est);
	if (cl != &q->root)
		kfree(cl);
}