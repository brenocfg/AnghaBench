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
struct TYPE_2__ {int /*<<< orphan*/  ioc; } ;
struct bfad_s {scalar_t__ disable_active; int /*<<< orphan*/  disable_comp; int /*<<< orphan*/  bfad_lock; TYPE_1__ bfa; } ;
struct bfa_bsg_gen_s {void* status; } ;

/* Variables and functions */
 scalar_t__ BFA_FALSE ; 
 void* BFA_STATUS_OK ; 
 scalar_t__ BFA_TRUE ; 
 int EBUSY ; 
 scalar_t__ bfa_ioc_is_disabled (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_iocfc_disable (TYPE_1__*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

int
bfad_iocmd_ioc_disable(struct bfad_s *bfad, void *cmd)
{
	struct bfa_bsg_gen_s *iocmd = (struct bfa_bsg_gen_s *)cmd;
	int	rc = 0;
	unsigned long	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	if (bfa_ioc_is_disabled(&bfad->bfa.ioc)) {
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		iocmd->status = BFA_STATUS_OK;
		return rc;
	}

	if (bfad->disable_active) {
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		return -EBUSY;
	}

	bfad->disable_active = BFA_TRUE;
	init_completion(&bfad->disable_comp);
	bfa_iocfc_disable(&bfad->bfa);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	wait_for_completion(&bfad->disable_comp);
	bfad->disable_active = BFA_FALSE;
	iocmd->status = BFA_STATUS_OK;

	return rc;
}