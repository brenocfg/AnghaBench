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
typedef  int /*<<< orphan*/  u_int32_t ;
struct qfq_if {int /*<<< orphan*/  qif_ifq; } ;
struct qfq_classstats {int weight; int /*<<< orphan*/  sfb; int /*<<< orphan*/  qstate; int /*<<< orphan*/  qtype; int /*<<< orphan*/  dropcnt; int /*<<< orphan*/  xmitcnt; int /*<<< orphan*/  period; int /*<<< orphan*/  qlimit; int /*<<< orphan*/  qlength; int /*<<< orphan*/  lmax; int /*<<< orphan*/  index; int /*<<< orphan*/  class_handle; } ;
struct qfq_class {int cl_inv_w; int /*<<< orphan*/ * cl_sfb; int /*<<< orphan*/  cl_q; int /*<<< orphan*/  cl_dropcnt; int /*<<< orphan*/  cl_xmitcnt; int /*<<< orphan*/  cl_period; int /*<<< orphan*/  cl_lmax; TYPE_1__* cl_grp; int /*<<< orphan*/  cl_handle; } ;
struct TYPE_2__ {int /*<<< orphan*/  qfg_index; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IFCQ_LOCK_ASSERT_HELD (int /*<<< orphan*/ ) ; 
 int QFQ_ONE_FP ; 
 scalar_t__ q_is_sfb (int /*<<< orphan*/ *) ; 
 struct qfq_class* qfq_clh_to_clp (struct qfq_if*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qlimit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qstate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qtype (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sfb_getstats (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
qfq_get_class_stats(struct qfq_if *qif, u_int32_t qid,
    struct qfq_classstats *sp)
{
	struct qfq_class *cl;

	IFCQ_LOCK_ASSERT_HELD(qif->qif_ifq);

	if ((cl = qfq_clh_to_clp(qif, qid)) == NULL)
		return (EINVAL);

	sp->class_handle = cl->cl_handle;
	sp->index = cl->cl_grp->qfg_index;
	sp->weight = (QFQ_ONE_FP / cl->cl_inv_w);
	sp->lmax = cl->cl_lmax;
	sp->qlength = qlen(&cl->cl_q);
	sp->qlimit = qlimit(&cl->cl_q);
	sp->period = cl->cl_period;
	sp->xmitcnt = cl->cl_xmitcnt;
	sp->dropcnt = cl->cl_dropcnt;

	sp->qtype = qtype(&cl->cl_q);
	sp->qstate = qstate(&cl->cl_q);

	if (q_is_sfb(&cl->cl_q) && cl->cl_sfb != NULL)
		sfb_getstats(cl->cl_sfb, &sp->sfb);

	return (0);
}