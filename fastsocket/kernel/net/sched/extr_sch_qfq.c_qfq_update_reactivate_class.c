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
typedef  int /*<<< orphan*/  u32 ;
struct qfq_sched {int /*<<< orphan*/ * groups; } ;
struct qfq_class {TYPE_2__* qdisc; int /*<<< orphan*/  S; int /*<<< orphan*/  F; int /*<<< orphan*/ * grp; } ;
struct TYPE_3__ {scalar_t__ qlen; } ;
struct TYPE_4__ {TYPE_1__ q; } ;

/* Variables and functions */
 int /*<<< orphan*/  qdisc_peek_len (TYPE_2__*) ; 
 int /*<<< orphan*/  qfq_activate_class (struct qfq_sched*,struct qfq_class*,int /*<<< orphan*/ ) ; 
 int qfq_calc_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qfq_deactivate_class (struct qfq_sched*,struct qfq_class*) ; 
 int /*<<< orphan*/  qfq_update_class_params (struct qfq_sched*,struct qfq_class*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void qfq_update_reactivate_class(struct qfq_sched *q,
					struct qfq_class *cl,
					u32 inv_w, u32 lmax, int delta_w)
{
	bool need_reactivation = false;
	int i = qfq_calc_index(inv_w, lmax);

	if (&q->groups[i] != cl->grp && cl->qdisc->q.qlen > 0) {
		/*
		 * shift cl->F back, to not charge the
		 * class for the not-yet-served head
		 * packet
		 */
		cl->F = cl->S;
		/* remove class from its slot in the old group */
		qfq_deactivate_class(q, cl);
		need_reactivation = true;
	}

	qfq_update_class_params(q, cl, lmax, inv_w, delta_w);

	if (need_reactivation) /* activate in new group */
		qfq_activate_class(q, cl, qdisc_peek_len(cl->qdisc));
}