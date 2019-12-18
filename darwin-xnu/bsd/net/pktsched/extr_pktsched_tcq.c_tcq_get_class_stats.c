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
typedef  int /*<<< orphan*/  u_int32_t ;
struct tcq_if {int /*<<< orphan*/  tif_ifq; } ;
struct tcq_classstats {int /*<<< orphan*/  sfb; int /*<<< orphan*/  qstate; int /*<<< orphan*/  qtype; int /*<<< orphan*/  dropcnt; int /*<<< orphan*/  xmitcnt; int /*<<< orphan*/  period; int /*<<< orphan*/  qlimit; int /*<<< orphan*/  qlength; int /*<<< orphan*/  priority; int /*<<< orphan*/  class_handle; } ;
struct tcq_class {int /*<<< orphan*/ * cl_sfb; int /*<<< orphan*/  cl_q; int /*<<< orphan*/  cl_dropcnt; int /*<<< orphan*/  cl_xmitcnt; int /*<<< orphan*/  cl_period; int /*<<< orphan*/  cl_pri; int /*<<< orphan*/  cl_handle; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IFCQ_LOCK_ASSERT_HELD (int /*<<< orphan*/ ) ; 
 scalar_t__ q_is_sfb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qlimit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qstate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qtype (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sfb_getstats (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct tcq_class* tcq_clh_to_clp (struct tcq_if*,int /*<<< orphan*/ ) ; 

int
tcq_get_class_stats(struct tcq_if *tif, u_int32_t qid,
    struct tcq_classstats *sp)
{
	struct tcq_class *cl;

	IFCQ_LOCK_ASSERT_HELD(tif->tif_ifq);

	if ((cl = tcq_clh_to_clp(tif, qid)) == NULL)
		return (EINVAL);

	sp->class_handle = cl->cl_handle;
	sp->priority = cl->cl_pri;
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