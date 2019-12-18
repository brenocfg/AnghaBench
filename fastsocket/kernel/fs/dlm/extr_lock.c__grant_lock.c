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
struct dlm_rsb {int dummy; } ;
struct dlm_lkb {scalar_t__ lkb_grmode; scalar_t__ lkb_rqmode; scalar_t__ lkb_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_LKSTS_GRANTED ; 
 scalar_t__ DLM_LOCK_IV ; 
 int /*<<< orphan*/  add_lkb (struct dlm_rsb*,struct dlm_lkb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  move_lkb (struct dlm_rsb*,struct dlm_lkb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _grant_lock(struct dlm_rsb *r, struct dlm_lkb *lkb)
{
	if (lkb->lkb_grmode != lkb->lkb_rqmode) {
		lkb->lkb_grmode = lkb->lkb_rqmode;
		if (lkb->lkb_status)
			move_lkb(r, lkb, DLM_LKSTS_GRANTED);
		else
			add_lkb(r, lkb, DLM_LKSTS_GRANTED);
	}

	lkb->lkb_rqmode = DLM_LOCK_IV;
}