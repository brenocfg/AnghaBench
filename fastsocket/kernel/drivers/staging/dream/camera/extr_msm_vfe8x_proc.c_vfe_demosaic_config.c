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
struct vfe_demosaic_cfg {int /*<<< orphan*/  greenDiffThreshold; int /*<<< orphan*/  redDiffThreshold; int /*<<< orphan*/  blueDiffThreshold; int /*<<< orphan*/  maxValue; int /*<<< orphan*/  minValue; int /*<<< orphan*/  ratio; int /*<<< orphan*/  lpThreshold; int /*<<< orphan*/  slopeShift; int /*<<< orphan*/  fmaxThreshold; int /*<<< orphan*/  fminThreshold; int /*<<< orphan*/  abfShift; int /*<<< orphan*/  forceAbfOn; int /*<<< orphan*/  badPixelCorrEnable; int /*<<< orphan*/  abfEnable; } ;
struct vfe_demosaic_bpc_cfg {int /*<<< orphan*/  greenDiffThreshold; int /*<<< orphan*/  redDiffThreshold; int /*<<< orphan*/  blueDiffThreshold; int /*<<< orphan*/  maxValue; int /*<<< orphan*/  minValue; int /*<<< orphan*/  ratio; int /*<<< orphan*/  lpThreshold; int /*<<< orphan*/  slopeShift; int /*<<< orphan*/  fmaxThreshold; int /*<<< orphan*/  fminThreshold; int /*<<< orphan*/  abfShift; int /*<<< orphan*/  forceAbfOn; int /*<<< orphan*/  badPixelCorrEnable; int /*<<< orphan*/  abfEnable; } ;
struct vfe_demosaic_abf_cfg {int /*<<< orphan*/  greenDiffThreshold; int /*<<< orphan*/  redDiffThreshold; int /*<<< orphan*/  blueDiffThreshold; int /*<<< orphan*/  maxValue; int /*<<< orphan*/  minValue; int /*<<< orphan*/  ratio; int /*<<< orphan*/  lpThreshold; int /*<<< orphan*/  slopeShift; int /*<<< orphan*/  fmaxThreshold; int /*<<< orphan*/  fminThreshold; int /*<<< orphan*/  abfShift; int /*<<< orphan*/  forceAbfOn; int /*<<< orphan*/  badPixelCorrEnable; int /*<<< orphan*/  abfEnable; } ;
struct TYPE_7__ {int /*<<< orphan*/  greenDiffThreshold; int /*<<< orphan*/  redDiffThreshold; int /*<<< orphan*/  blueDiffThreshold; int /*<<< orphan*/  fmaxThreshold; int /*<<< orphan*/  fminThreshold; int /*<<< orphan*/  enable; } ;
struct TYPE_6__ {int /*<<< orphan*/  max; int /*<<< orphan*/  min; int /*<<< orphan*/  ratio; int /*<<< orphan*/  lpThreshold; int /*<<< orphan*/  shift; int /*<<< orphan*/  forceOn; int /*<<< orphan*/  enable; } ;
struct vfe_cmd_demosaic_config {TYPE_3__ bpcConfig; TYPE_2__ abfConfig; int /*<<< orphan*/  slopeShift; int /*<<< orphan*/  enable; } ;
typedef  int /*<<< orphan*/  cmd_bpc ;
typedef  int /*<<< orphan*/  cmd_abf ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_5__ {int /*<<< orphan*/  demosaicEnable; } ;
struct TYPE_8__ {scalar_t__ vfebase; TYPE_1__ vfeModuleEnableLocal; } ;

/* Variables and functions */
 scalar_t__ VFE_DEMOSAIC_ABF_CFG_0 ; 
 scalar_t__ VFE_DEMOSAIC_BPC_CFG_0 ; 
 scalar_t__ VFE_DEMOSAIC_CFG ; 
 TYPE_4__* ctrl ; 
 int /*<<< orphan*/  memset (struct vfe_demosaic_cfg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vfe_prog_hw (scalar_t__,int /*<<< orphan*/ *,int) ; 

void vfe_demosaic_config(struct vfe_cmd_demosaic_config *in)
{
	struct vfe_demosaic_cfg cmd;
	struct vfe_demosaic_bpc_cfg cmd_bpc;
	struct vfe_demosaic_abf_cfg cmd_abf;

	memset(&cmd, 0, sizeof(cmd));
	memset(&cmd_bpc, 0, sizeof(cmd_bpc));
	memset(&cmd_abf, 0, sizeof(cmd_abf));

	ctrl->vfeModuleEnableLocal.demosaicEnable = in->enable;

	cmd.abfEnable          = in->abfConfig.enable;
	cmd.badPixelCorrEnable = in->bpcConfig.enable;
	cmd.forceAbfOn         = in->abfConfig.forceOn;
	cmd.abfShift           = in->abfConfig.shift;
	cmd.fminThreshold      = in->bpcConfig.fminThreshold;
	cmd.fmaxThreshold      = in->bpcConfig.fmaxThreshold;
	cmd.slopeShift         = in->slopeShift;

	vfe_prog_hw(ctrl->vfebase + VFE_DEMOSAIC_CFG,
		(uint32_t *)&cmd, sizeof(cmd));

	cmd_abf.lpThreshold = in->abfConfig.lpThreshold;
	cmd_abf.ratio       = in->abfConfig.ratio;
	cmd_abf.minValue    = in->abfConfig.min;
	cmd_abf.maxValue    = in->abfConfig.max;

	vfe_prog_hw(ctrl->vfebase + VFE_DEMOSAIC_ABF_CFG_0,
		(uint32_t *)&cmd_abf, sizeof(cmd_abf));

	cmd_bpc.blueDiffThreshold   = in->bpcConfig.blueDiffThreshold;
	cmd_bpc.redDiffThreshold    = in->bpcConfig.redDiffThreshold;
	cmd_bpc.greenDiffThreshold  = in->bpcConfig.greenDiffThreshold;

	vfe_prog_hw(ctrl->vfebase + VFE_DEMOSAIC_BPC_CFG_0,
		(uint32_t *)&cmd_bpc, sizeof(cmd_bpc));
}