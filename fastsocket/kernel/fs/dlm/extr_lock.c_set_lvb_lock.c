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
struct dlm_rsb {scalar_t__ res_lvbseq; scalar_t__ res_lvbptr; TYPE_1__* res_ls; } ;
struct dlm_lkb {int lkb_grmode; int lkb_rqmode; int lkb_exflags; int /*<<< orphan*/  lkb_sbflags; scalar_t__ lkb_lvbseq; scalar_t__ lkb_lvbptr; } ;
struct TYPE_2__ {int ls_lvblen; } ;

/* Variables and functions */
 int DLM_LKF_IVVALBLK ; 
 int DLM_LKF_VALBLK ; 
 int /*<<< orphan*/  DLM_SBF_VALNOTVALID ; 
 int /*<<< orphan*/  RSB_VALNOTVALID ; 
 scalar_t__ dlm_allocate_lvb (TYPE_1__*) ; 
 int** dlm_lvb_operations ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  rsb_clear_flag (struct dlm_rsb*,int /*<<< orphan*/ ) ; 
 scalar_t__ rsb_flag (struct dlm_rsb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsb_set_flag (struct dlm_rsb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_lvb_lock(struct dlm_rsb *r, struct dlm_lkb *lkb)
{
	int b, len = r->res_ls->ls_lvblen;

	/* b=1 lvb returned to caller
	   b=0 lvb written to rsb or invalidated
	   b=-1 do nothing */

	b =  dlm_lvb_operations[lkb->lkb_grmode + 1][lkb->lkb_rqmode + 1];

	if (b == 1) {
		if (!lkb->lkb_lvbptr)
			return;

		if (!(lkb->lkb_exflags & DLM_LKF_VALBLK))
			return;

		if (!r->res_lvbptr)
			return;

		memcpy(lkb->lkb_lvbptr, r->res_lvbptr, len);
		lkb->lkb_lvbseq = r->res_lvbseq;

	} else if (b == 0) {
		if (lkb->lkb_exflags & DLM_LKF_IVVALBLK) {
			rsb_set_flag(r, RSB_VALNOTVALID);
			return;
		}

		if (!lkb->lkb_lvbptr)
			return;

		if (!(lkb->lkb_exflags & DLM_LKF_VALBLK))
			return;

		if (!r->res_lvbptr)
			r->res_lvbptr = dlm_allocate_lvb(r->res_ls);

		if (!r->res_lvbptr)
			return;

		memcpy(r->res_lvbptr, lkb->lkb_lvbptr, len);
		r->res_lvbseq++;
		lkb->lkb_lvbseq = r->res_lvbseq;
		rsb_clear_flag(r, RSB_VALNOTVALID);
	}

	if (rsb_flag(r, RSB_VALNOTVALID))
		lkb->lkb_sbflags |= DLM_SBF_VALNOTVALID;
}