#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct vfe_main_scaler_cfg {int /*<<< orphan*/  vertPhaseInit; int /*<<< orphan*/  vertMNInit; int /*<<< orphan*/  vertInterResolution; int /*<<< orphan*/  vertPhaseMult; int /*<<< orphan*/  outHeight; int /*<<< orphan*/  inHeight; int /*<<< orphan*/  horizPhaseInit; int /*<<< orphan*/  horizMNInit; int /*<<< orphan*/  horizInterResolution; int /*<<< orphan*/  horizPhaseMult; int /*<<< orphan*/  outWidth; int /*<<< orphan*/  inWidth; int /*<<< orphan*/  vEnable; int /*<<< orphan*/  hEnable; } ;
struct TYPE_11__ {int /*<<< orphan*/  phaseInit; int /*<<< orphan*/  MNCounterInit; } ;
struct TYPE_10__ {int /*<<< orphan*/  interpolationResolution; int /*<<< orphan*/  phaseMultiplicationFactor; int /*<<< orphan*/  outputSize; int /*<<< orphan*/  inputSize; int /*<<< orphan*/  enable; } ;
struct TYPE_9__ {int /*<<< orphan*/  phaseInit; int /*<<< orphan*/  MNCounterInit; } ;
struct TYPE_8__ {int /*<<< orphan*/  interpolationResolution; int /*<<< orphan*/  phaseMultiplicationFactor; int /*<<< orphan*/  outputSize; int /*<<< orphan*/  inputSize; int /*<<< orphan*/  enable; } ;
struct vfe_cmd_main_scaler_config {TYPE_5__ MNInitV; TYPE_4__ vconfig; TYPE_3__ MNInitH; TYPE_2__ hconfig; int /*<<< orphan*/  enable; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_7__ {int /*<<< orphan*/  mainScalerEnable; } ;
struct TYPE_12__ {scalar_t__ vfebase; TYPE_1__ vfeModuleEnableLocal; } ;

/* Variables and functions */
 scalar_t__ VFE_SCALE_CFG ; 
 TYPE_6__* ctrl ; 
 int /*<<< orphan*/  memset (struct vfe_main_scaler_cfg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vfe_prog_hw (scalar_t__,int /*<<< orphan*/ *,int) ; 

void vfe_main_scaler_config(struct vfe_cmd_main_scaler_config *in)
{
	struct vfe_main_scaler_cfg cmd;

	memset(&cmd, 0, sizeof(cmd));

	ctrl->vfeModuleEnableLocal.mainScalerEnable = in->enable;

	cmd.hEnable              = in->hconfig.enable;
	cmd.vEnable              = in->vconfig.enable;
	cmd.inWidth              = in->hconfig.inputSize;
	cmd.outWidth             = in->hconfig.outputSize;
	cmd.horizPhaseMult       = in->hconfig.phaseMultiplicationFactor;
	cmd.horizInterResolution = in->hconfig.interpolationResolution;
	cmd.horizMNInit          = in->MNInitH.MNCounterInit;
	cmd.horizPhaseInit       = in->MNInitH.phaseInit;
	cmd.inHeight             = in->vconfig.inputSize;
	cmd.outHeight            = in->vconfig.outputSize;
	cmd.vertPhaseMult        = in->vconfig.phaseMultiplicationFactor;
	cmd.vertInterResolution  = in->vconfig.interpolationResolution;
	cmd.vertMNInit           = in->MNInitV.MNCounterInit;
	cmd.vertPhaseInit        = in->MNInitV.phaseInit;

	vfe_prog_hw(ctrl->vfebase + VFE_SCALE_CFG,
		(uint32_t *)&cmd, sizeof(cmd));
}