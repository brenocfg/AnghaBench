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
struct bfad_s {int /*<<< orphan*/  enable_comp; int /*<<< orphan*/  bfad_lock; TYPE_1__ bfa; } ;
struct bfa_bsg_gen_s {void* status; } ;

/* Variables and functions */
 void* BFA_STATUS_OK ; 
 int /*<<< orphan*/  bfa_ioc_is_disabled (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_iocfc_enable (TYPE_1__*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

int
bfad_iocmd_ioc_enable(struct bfad_s *bfad, void *cmd)
{
	struct bfa_bsg_gen_s *iocmd = (struct bfa_bsg_gen_s *)cmd;
	int	rc = 0;
	unsigned long	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	/* If IOC is not in disabled state - return */
	if (!bfa_ioc_is_disabled(&bfad->bfa.ioc)) {
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		iocmd->status = BFA_STATUS_OK;
		return rc;
	}

	init_completion(&bfad->enable_comp);
	bfa_iocfc_enable(&bfad->bfa);
	iocmd->status = BFA_STATUS_OK;
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	wait_for_completion(&bfad->enable_comp);

	return rc;
}