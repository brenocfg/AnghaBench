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
struct qfq_if {int /*<<< orphan*/  qif_ifq; } ;
struct qfq_class {int cl_inv_w; int /*<<< orphan*/ * cl_sfb; int /*<<< orphan*/  cl_q; int /*<<< orphan*/  cl_handle; } ;
typedef  int /*<<< orphan*/  cqev_t ;

/* Variables and functions */
 int /*<<< orphan*/  IFCQ_LOCK_ASSERT_HELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  QFQIF_IFP (struct qfq_if*) ; 
 int QFQ_ONE_FP ; 
 int /*<<< orphan*/  if_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifclassq_ev2str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pktsched_verbose ; 
 scalar_t__ q_is_sfb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qfq_style (struct qfq_if*) ; 
 void sfb_updateq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
qfq_updateq(struct qfq_if *qif, struct qfq_class *cl, cqev_t ev)
{
	IFCQ_LOCK_ASSERT_HELD(qif->qif_ifq);

	if (pktsched_verbose) {
		log(LOG_DEBUG, "%s: %s update qid=%d weight=%d event=%s\n",
		    if_name(QFQIF_IFP(qif)), qfq_style(qif),
		    cl->cl_handle, (u_int32_t)(QFQ_ONE_FP / cl->cl_inv_w),
		    ifclassq_ev2str(ev));
	}

	if (q_is_sfb(&cl->cl_q) && cl->cl_sfb != NULL)
		return (sfb_updateq(cl->cl_sfb, ev));
}