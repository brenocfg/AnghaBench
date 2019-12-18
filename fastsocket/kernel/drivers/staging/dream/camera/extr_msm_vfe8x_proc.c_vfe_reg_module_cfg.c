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
typedef  int /*<<< orphan*/  uint32_t ;
struct vfe_module_enable {int /*<<< orphan*/  scaler2CbcrEnable; int /*<<< orphan*/  scaler2YEnable; int /*<<< orphan*/  chromaSubsampleEnable; int /*<<< orphan*/  chromaSuppressionEnable; int /*<<< orphan*/  asfEnable; int /*<<< orphan*/  chromaEnhanEnable; int /*<<< orphan*/  rgbLUTEnable; int /*<<< orphan*/  lumaAdaptationEnable; int /*<<< orphan*/  skinToneEnable; int /*<<< orphan*/  yHistEnable; int /*<<< orphan*/  colorCorrectionEnable; int /*<<< orphan*/  whiteBalanceEnable; int /*<<< orphan*/  mainScalerEnable; int /*<<< orphan*/  cropEnable; int /*<<< orphan*/  statsEnable; int /*<<< orphan*/  demosaicEnable; int /*<<< orphan*/  chromaUpsampleEnable; int /*<<< orphan*/  demuxEnable; int /*<<< orphan*/  lensRollOffEnable; int /*<<< orphan*/  blackLevelCorrectionEnable; } ;
struct vfe_mod_enable {int /*<<< orphan*/  scaler2CbcrEnable; int /*<<< orphan*/  scaler2YEnable; int /*<<< orphan*/  chromaSubsampleEnable; int /*<<< orphan*/  chromaSuppressionEnable; int /*<<< orphan*/  asfEnable; int /*<<< orphan*/  chromaEnhanEnable; int /*<<< orphan*/  rgbLUTEnable; int /*<<< orphan*/  lumaAdaptationEnable; int /*<<< orphan*/  skinToneEnable; int /*<<< orphan*/  yHistEnable; int /*<<< orphan*/  colorCorrectionEnable; int /*<<< orphan*/  whiteBalanceEnable; int /*<<< orphan*/  mainScalerEnable; int /*<<< orphan*/  cropEnable; int /*<<< orphan*/  statsEnable; int /*<<< orphan*/  demosaicEnable; int /*<<< orphan*/  chromaUpsampleEnable; int /*<<< orphan*/  demuxEnable; int /*<<< orphan*/  lensRollOffEnable; int /*<<< orphan*/  blackLevelCorrectionEnable; } ;
typedef  int /*<<< orphan*/  ena ;
struct TYPE_2__ {scalar_t__ vfebase; } ;

/* Variables and functions */
 scalar_t__ VFE_MODULE_CFG ; 
 TYPE_1__* ctrl ; 
 int /*<<< orphan*/  memset (struct vfe_mod_enable*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void vfe_reg_module_cfg(struct vfe_module_enable *in)
{
	struct vfe_mod_enable ena;

	memset(&ena, 0, sizeof(ena));

	ena.blackLevelCorrectionEnable = in->blackLevelCorrectionEnable;
	ena.lensRollOffEnable          = in->lensRollOffEnable;
	ena.demuxEnable                = in->demuxEnable;
	ena.chromaUpsampleEnable       = in->chromaUpsampleEnable;
	ena.demosaicEnable             = in->demosaicEnable;
	ena.statsEnable                = in->statsEnable;
	ena.cropEnable                 = in->cropEnable;
	ena.mainScalerEnable           = in->mainScalerEnable;
	ena.whiteBalanceEnable         = in->whiteBalanceEnable;
	ena.colorCorrectionEnable      = in->colorCorrectionEnable;
	ena.yHistEnable                = in->yHistEnable;
	ena.skinToneEnable             = in->skinToneEnable;
	ena.lumaAdaptationEnable       = in->lumaAdaptationEnable;
	ena.rgbLUTEnable               = in->rgbLUTEnable;
	ena.chromaEnhanEnable          = in->chromaEnhanEnable;
	ena.asfEnable                  = in->asfEnable;
	ena.chromaSuppressionEnable    = in->chromaSuppressionEnable;
	ena.chromaSubsampleEnable      = in->chromaSubsampleEnable;
	ena.scaler2YEnable             = in->scaler2YEnable;
	ena.scaler2CbcrEnable          = in->scaler2CbcrEnable;

	writel(*((uint32_t *)&ena), ctrl->vfebase + VFE_MODULE_CFG);
}