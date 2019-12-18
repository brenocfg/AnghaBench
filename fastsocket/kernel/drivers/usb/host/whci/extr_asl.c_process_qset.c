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
typedef  int uint32_t ;
struct whc_qtd {int /*<<< orphan*/  status; } ;
struct whc_qset {scalar_t__ ntds; int td_start; scalar_t__ remove; struct whc_qtd* qtd; } ;
struct whc {int dummy; } ;
typedef  enum whc_update { ____Placeholder_whc_update } whc_update ;

/* Variables and functions */
 int QTD_STS_ACTIVE ; 
 int QTD_STS_HALTED ; 
 int WHC_UPDATE_REMOVED ; 
 int WHC_UPDATE_UPDATED ; 
 int /*<<< orphan*/  asl_qset_remove (struct whc*,struct whc_qset*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_halted_qtd (struct whc*,struct whc_qset*,struct whc_qtd*) ; 
 int /*<<< orphan*/  process_inactive_qtd (struct whc*,struct whc_qset*,struct whc_qtd*) ; 
 int qset_add_qtds (struct whc*,struct whc_qset*) ; 

__attribute__((used)) static uint32_t process_qset(struct whc *whc, struct whc_qset *qset)
{
	enum whc_update update = 0;
	uint32_t status = 0;

	while (qset->ntds) {
		struct whc_qtd *td;
		int t;

		t = qset->td_start;
		td = &qset->qtd[qset->td_start];
		status = le32_to_cpu(td->status);

		/*
		 * Nothing to do with a still active qTD.
		 */
		if (status & QTD_STS_ACTIVE)
			break;

		if (status & QTD_STS_HALTED) {
			/* Ug, an error. */
			process_halted_qtd(whc, qset, td);
			/* A halted qTD always triggers an update
			   because the qset was either removed or
			   reactivated. */
			update |= WHC_UPDATE_UPDATED;
			goto done;
		}

		/* Mmm, a completed qTD. */
		process_inactive_qtd(whc, qset, td);
	}

	if (!qset->remove)
		update |= qset_add_qtds(whc, qset);

done:
	/*
	 * Remove this qset from the ASL if requested, but only if has
	 * no qTDs.
	 */
	if (qset->remove && qset->ntds == 0) {
		asl_qset_remove(whc, qset);
		update |= WHC_UPDATE_REMOVED;
	}
	return update;
}