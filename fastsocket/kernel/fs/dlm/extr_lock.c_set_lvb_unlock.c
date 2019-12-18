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
struct dlm_rsb {int /*<<< orphan*/  res_lvbseq; TYPE_1__* res_ls; scalar_t__ res_lvbptr; } ;
struct dlm_lkb {scalar_t__ lkb_grmode; int lkb_exflags; int /*<<< orphan*/  lkb_lvbptr; } ;
struct TYPE_2__ {int /*<<< orphan*/  ls_lvblen; } ;

/* Variables and functions */
 int DLM_LKF_IVVALBLK ; 
 int DLM_LKF_VALBLK ; 
 scalar_t__ DLM_LOCK_PW ; 
 int /*<<< orphan*/  RSB_VALNOTVALID ; 
 scalar_t__ dlm_allocate_lvb (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsb_clear_flag (struct dlm_rsb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsb_set_flag (struct dlm_rsb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_lvb_unlock(struct dlm_rsb *r, struct dlm_lkb *lkb)
{
	if (lkb->lkb_grmode < DLM_LOCK_PW)
		return;

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

	memcpy(r->res_lvbptr, lkb->lkb_lvbptr, r->res_ls->ls_lvblen);
	r->res_lvbseq++;
	rsb_clear_flag(r, RSB_VALNOTVALID);
}