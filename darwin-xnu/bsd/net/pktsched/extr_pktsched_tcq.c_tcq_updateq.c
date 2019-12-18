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
struct tcq_if {int /*<<< orphan*/  tif_ifq; } ;
struct tcq_class {int /*<<< orphan*/ * cl_sfb; int /*<<< orphan*/  cl_q; int /*<<< orphan*/  cl_pri; int /*<<< orphan*/  cl_handle; } ;
typedef  int /*<<< orphan*/  cqev_t ;

/* Variables and functions */
 int /*<<< orphan*/  IFCQ_LOCK_ASSERT_HELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  TCQIF_IFP (struct tcq_if*) ; 
 int /*<<< orphan*/  if_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifclassq_ev2str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pktsched_verbose ; 
 scalar_t__ q_is_sfb (int /*<<< orphan*/ *) ; 
 void sfb_updateq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcq_style (struct tcq_if*) ; 

__attribute__((used)) static void
tcq_updateq(struct tcq_if *tif, struct tcq_class *cl, cqev_t ev)
{
	IFCQ_LOCK_ASSERT_HELD(tif->tif_ifq);

	if (pktsched_verbose) {
		log(LOG_DEBUG, "%s: %s update qid=%d pri=%d event=%s\n",
		    if_name(TCQIF_IFP(tif)), tcq_style(tif),
		    cl->cl_handle, cl->cl_pri, ifclassq_ev2str(ev));
	}

	if (q_is_sfb(&cl->cl_q) && cl->cl_sfb != NULL)
		return (sfb_updateq(cl->cl_sfb, ev));
}