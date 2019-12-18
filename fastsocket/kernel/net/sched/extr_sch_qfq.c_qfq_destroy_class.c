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
struct qfq_sched {int wsum; } ;
struct qfq_class {int inv_w; int /*<<< orphan*/  qdisc; int /*<<< orphan*/  rate_est; int /*<<< orphan*/  bstats; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int ONE_FP ; 
 int /*<<< orphan*/  gen_kill_estimator (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct qfq_class*) ; 
 int /*<<< orphan*/  qdisc_destroy (int /*<<< orphan*/ ) ; 
 struct qfq_sched* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static void qfq_destroy_class(struct Qdisc *sch, struct qfq_class *cl)
{
	struct qfq_sched *q = qdisc_priv(sch);

	if (cl->inv_w) {
		q->wsum -= ONE_FP / cl->inv_w;
		cl->inv_w = 0;
	}

	gen_kill_estimator(&cl->bstats, &cl->rate_est);
	qdisc_destroy(cl->qdisc);
	kfree(cl);
}