#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  port_id; } ;
struct TYPE_4__ {TYPE_1__ ioc; } ;
struct bfad_s {int /*<<< orphan*/  bfad_lock; TYPE_2__ bfa; } ;
struct bfad_hal_comp {scalar_t__ status; int /*<<< orphan*/  comp; } ;
struct bfa_ethboot_cfg_s {int dummy; } ;
struct bfa_bsg_ethboot_s {scalar_t__ status; int /*<<< orphan*/  cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FLASH (TYPE_2__*) ; 
 int /*<<< orphan*/  BFA_FLASH_PART_PXECFG ; 
 scalar_t__ BFA_STATUS_OK ; 
 scalar_t__ bfa_flash_read_part (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bfad_hal_comp*) ; 
 int /*<<< orphan*/  bfad_hcb_comp ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

int
bfad_iocmd_ethboot_query(struct bfad_s *bfad, void *cmd)
{
	struct bfa_bsg_ethboot_s *iocmd = (struct bfa_bsg_ethboot_s *)cmd;
	struct bfad_hal_comp fcomp;
	unsigned long	flags;

	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_flash_read_part(BFA_FLASH(&bfad->bfa),
				BFA_FLASH_PART_PXECFG,
				bfad->bfa.ioc.port_id, &iocmd->cfg,
				sizeof(struct bfa_ethboot_cfg_s), 0,
				bfad_hcb_comp, &fcomp);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	if (iocmd->status != BFA_STATUS_OK)
		goto out;
	wait_for_completion(&fcomp.comp);
	iocmd->status = fcomp.status;
out:
	return 0;
}