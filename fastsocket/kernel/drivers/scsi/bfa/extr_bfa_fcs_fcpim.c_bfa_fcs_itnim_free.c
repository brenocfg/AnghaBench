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
struct bfa_fcs_itnim_s {int /*<<< orphan*/  itnim_drv; TYPE_1__* fcs; int /*<<< orphan*/ * bfa_itnim; } ;
struct TYPE_2__ {int /*<<< orphan*/  bfad; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_fcb_itnim_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_itnim_delete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bfa_fcs_itnim_free(struct bfa_fcs_itnim_s *itnim)
{
	if (itnim->bfa_itnim) {
		bfa_itnim_delete(itnim->bfa_itnim);
		itnim->bfa_itnim = NULL;
	}

	bfa_fcb_itnim_free(itnim->fcs->bfad, itnim->itnim_drv);
}