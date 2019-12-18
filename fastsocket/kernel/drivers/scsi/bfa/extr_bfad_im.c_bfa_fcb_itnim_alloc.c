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
struct bfad_s {int /*<<< orphan*/  bfad_flags; int /*<<< orphan*/  im; } ;
struct bfa_fcs_itnim_s {int dummy; } ;
struct bfad_itnim_s {int /*<<< orphan*/  itnim_work; int /*<<< orphan*/  state; struct bfa_fcs_itnim_s fcs_itnim; int /*<<< orphan*/  im; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFAD_RPORT_ONLINE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ITNIM_STATE_NONE ; 
 int /*<<< orphan*/  bfad_im_itnim_work_handler ; 
 struct bfad_itnim_s* kzalloc (int,int /*<<< orphan*/ ) ; 

void
bfa_fcb_itnim_alloc(struct bfad_s *bfad, struct bfa_fcs_itnim_s **itnim,
		    struct bfad_itnim_s **itnim_drv)
{
	*itnim_drv = kzalloc(sizeof(struct bfad_itnim_s), GFP_ATOMIC);
	if (*itnim_drv == NULL)
		return;

	(*itnim_drv)->im = bfad->im;
	*itnim = &(*itnim_drv)->fcs_itnim;
	(*itnim_drv)->state = ITNIM_STATE_NONE;

	/*
	 * Initiaze the itnim_work
	 */
	INIT_WORK(&(*itnim_drv)->itnim_work, bfad_im_itnim_work_handler);
	bfad->bfad_flags |= BFAD_RPORT_ONLINE;
}