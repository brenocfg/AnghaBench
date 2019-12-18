#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct vfe_scaler2_cfg {int /*<<< orphan*/  vertInterResolution; int /*<<< orphan*/  vertPhaseMult; int /*<<< orphan*/  outHeight; int /*<<< orphan*/  inHeight; int /*<<< orphan*/  horizInterResolution; int /*<<< orphan*/  horizPhaseMult; int /*<<< orphan*/  outWidth; int /*<<< orphan*/  inWidth; int /*<<< orphan*/  vEnable; int /*<<< orphan*/  hEnable; } ;
struct TYPE_7__ {int /*<<< orphan*/  interpolationResolution; int /*<<< orphan*/  phaseMultiplicationFactor; int /*<<< orphan*/  outputSize; int /*<<< orphan*/  inputSize; int /*<<< orphan*/  enable; } ;
struct TYPE_6__ {int /*<<< orphan*/  interpolationResolution; int /*<<< orphan*/  phaseMultiplicationFactor; int /*<<< orphan*/  outputSize; int /*<<< orphan*/  inputSize; int /*<<< orphan*/  enable; } ;
struct vfe_cmd_scaler2_config {TYPE_3__ vconfig; TYPE_2__ hconfig; int /*<<< orphan*/  enable; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_5__ {int /*<<< orphan*/  scaler2YEnable; } ;
struct TYPE_8__ {scalar_t__ vfebase; TYPE_1__ vfeModuleEnableLocal; } ;

/* Variables and functions */
 scalar_t__ VFE_SCALE_Y_CFG ; 
 TYPE_4__* ctrl ; 
 int /*<<< orphan*/  memset (struct vfe_scaler2_cfg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vfe_prog_hw (scalar_t__,int /*<<< orphan*/ *,int) ; 

void vfe_scaler2y_config(struct vfe_cmd_scaler2_config *in)
{
	struct vfe_scaler2_cfg cmd;

	memset(&cmd, 0, sizeof(cmd));

	ctrl->vfeModuleEnableLocal.scaler2YEnable = in->enable;

	cmd.hEnable               = in->hconfig.enable;
	cmd.vEnable               = in->vconfig.enable;
	cmd.inWidth               = in->hconfig.inputSize;
	cmd.outWidth              = in->hconfig.outputSize;
	cmd.horizPhaseMult        = in->hconfig.phaseMultiplicationFactor;
	cmd.horizInterResolution  = in->hconfig.interpolationResolution;
	cmd.inHeight              = in->vconfig.inputSize;
	cmd.outHeight             = in->vconfig.outputSize;
	cmd.vertPhaseMult         = in->vconfig.phaseMultiplicationFactor;
	cmd.vertInterResolution   = in->vconfig.interpolationResolution;

	vfe_prog_hw(ctrl->vfebase + VFE_SCALE_Y_CFG,
		(uint32_t *)&cmd, sizeof(cmd));
}