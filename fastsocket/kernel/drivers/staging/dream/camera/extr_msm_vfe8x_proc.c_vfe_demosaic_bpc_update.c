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
typedef  int /*<<< orphan*/  uint32_t ;
struct vfe_demosaic_cfg {int /*<<< orphan*/  fmaxThreshold; int /*<<< orphan*/  fminThreshold; int /*<<< orphan*/  badPixelCorrEnable; } ;
struct vfe_demosaic_bpc_cfg {int /*<<< orphan*/  greenDiffThreshold; int /*<<< orphan*/  redDiffThreshold; int /*<<< orphan*/  blueDiffThreshold; } ;
struct TYPE_3__ {int /*<<< orphan*/  greenDiffThreshold; int /*<<< orphan*/  redDiffThreshold; int /*<<< orphan*/  blueDiffThreshold; int /*<<< orphan*/  fmaxThreshold; int /*<<< orphan*/  fminThreshold; int /*<<< orphan*/  enable; } ;
struct vfe_cmd_demosaic_bpc_update {TYPE_1__ bpcUpdate; } ;
typedef  int /*<<< orphan*/  cmdbpc ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_4__ {scalar_t__ vfebase; } ;

/* Variables and functions */
 scalar_t__ VFE_DEMOSAIC_BPC_CFG_0 ; 
 scalar_t__ VFE_DEMOSAIC_CFG ; 
 TYPE_2__* ctrl ; 
 int /*<<< orphan*/  memset (struct vfe_demosaic_cfg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  vfe_prog_hw (scalar_t__,int /*<<< orphan*/ *,int) ; 

void vfe_demosaic_bpc_update(struct vfe_cmd_demosaic_bpc_update *in)
{
	struct vfe_demosaic_cfg cmd;
	struct vfe_demosaic_bpc_cfg cmdbpc;
	uint32_t temp;

	memset(&cmd, 0, sizeof(cmd));

	temp = readl(ctrl->vfebase + VFE_DEMOSAIC_CFG);

	cmd = *((struct vfe_demosaic_cfg *)(&temp));
	cmd.badPixelCorrEnable = in->bpcUpdate.enable;
	cmd.fminThreshold      = in->bpcUpdate.fminThreshold;
	cmd.fmaxThreshold      = in->bpcUpdate.fmaxThreshold;

	vfe_prog_hw(ctrl->vfebase + VFE_DEMOSAIC_CFG,
		(uint32_t *)&cmd, sizeof(cmd));

	cmdbpc.blueDiffThreshold  = in->bpcUpdate.blueDiffThreshold;
	cmdbpc.redDiffThreshold   = in->bpcUpdate.redDiffThreshold;
	cmdbpc.greenDiffThreshold = in->bpcUpdate.greenDiffThreshold;

	vfe_prog_hw(ctrl->vfebase + VFE_DEMOSAIC_BPC_CFG_0,
		(uint32_t *)&cmdbpc, sizeof(cmdbpc));
}