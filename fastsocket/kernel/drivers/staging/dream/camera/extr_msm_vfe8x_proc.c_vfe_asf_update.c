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
struct vfe_cmd_asf_update {int /*<<< orphan*/ * filter2Coefficients; int /*<<< orphan*/ * filter1Coefficients; int /*<<< orphan*/  sharpThreshE5; int /*<<< orphan*/  sharpThreshE4; int /*<<< orphan*/  sharpThreshE3; int /*<<< orphan*/  sharpThreshE2; int /*<<< orphan*/  normalizeFactor; int /*<<< orphan*/  sharpK2; int /*<<< orphan*/  sharpK1; int /*<<< orphan*/  sharpThreshE1; int /*<<< orphan*/  cropEnable; int /*<<< orphan*/  smoothCoefSurr; int /*<<< orphan*/  smoothCoefCenter; int /*<<< orphan*/  sharpMode; int /*<<< orphan*/  smoothFilterEnabled; int /*<<< orphan*/  enable; } ;
struct vfe_asf_update {int /*<<< orphan*/  F2Coeff8; int /*<<< orphan*/  F2Coeff7; int /*<<< orphan*/  F2Coeff6; int /*<<< orphan*/  F2Coeff5; int /*<<< orphan*/  F2Coeff4; int /*<<< orphan*/  F2Coeff3; int /*<<< orphan*/  F2Coeff2; int /*<<< orphan*/  F2Coeff1; int /*<<< orphan*/  F2Coeff0; int /*<<< orphan*/  F1Coeff8; int /*<<< orphan*/  F1Coeff7; int /*<<< orphan*/  F1Coeff6; int /*<<< orphan*/  F1Coeff5; int /*<<< orphan*/  F1Coeff4; int /*<<< orphan*/  F1Coeff3; int /*<<< orphan*/  F1Coeff2; int /*<<< orphan*/  F1Coeff1; int /*<<< orphan*/  F1Coeff0; int /*<<< orphan*/  sharpThresholdE5; int /*<<< orphan*/  sharpThresholdE4; int /*<<< orphan*/  sharpThresholdE3; int /*<<< orphan*/  sharpThresholdE2; int /*<<< orphan*/  normalizeFactor; int /*<<< orphan*/  sharpDegreeK2; int /*<<< orphan*/  sharpDegreeK1; int /*<<< orphan*/  sharpThresholdE1; int /*<<< orphan*/  cropEnable; int /*<<< orphan*/  smoothCoeff0; int /*<<< orphan*/  smoothCoeff1; int /*<<< orphan*/  sharpMode; int /*<<< orphan*/  smoothEnable; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_3__ {int /*<<< orphan*/  asfEnable; } ;
struct TYPE_4__ {scalar_t__ vfebase; TYPE_1__ vfeModuleEnableLocal; } ;

/* Variables and functions */
 scalar_t__ VFE_ASF_CFG ; 
 TYPE_2__* ctrl ; 
 int /*<<< orphan*/  memset (struct vfe_asf_update*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vfe_prog_hw (scalar_t__,int /*<<< orphan*/ *,int) ; 

void vfe_asf_update(struct vfe_cmd_asf_update *in)
{
	struct vfe_asf_update cmd;
	memset(&cmd, 0, sizeof(cmd));

	ctrl->vfeModuleEnableLocal.asfEnable = in->enable;

	cmd.smoothEnable     = in->smoothFilterEnabled;
	cmd.sharpMode        = in->sharpMode;
	cmd.smoothCoeff1     = in->smoothCoefCenter;
	cmd.smoothCoeff0     = in->smoothCoefSurr;
	cmd.cropEnable       = in->cropEnable;
	cmd.sharpThresholdE1 = in->sharpThreshE1;
	cmd.sharpDegreeK1    = in->sharpK1;
	cmd.sharpDegreeK2    = in->sharpK2;
	cmd.normalizeFactor  = in->normalizeFactor;
	cmd.sharpThresholdE2 = in->sharpThreshE2;
	cmd.sharpThresholdE3 = in->sharpThreshE3;
	cmd.sharpThresholdE4 = in->sharpThreshE4;
	cmd.sharpThresholdE5 = in->sharpThreshE5;
	cmd.F1Coeff0         = in->filter1Coefficients[0];
	cmd.F1Coeff1         = in->filter1Coefficients[1];
	cmd.F1Coeff2         = in->filter1Coefficients[2];
	cmd.F1Coeff3         = in->filter1Coefficients[3];
	cmd.F1Coeff4         = in->filter1Coefficients[4];
	cmd.F1Coeff5         = in->filter1Coefficients[5];
	cmd.F1Coeff6         = in->filter1Coefficients[6];
	cmd.F1Coeff7         = in->filter1Coefficients[7];
	cmd.F1Coeff8         = in->filter1Coefficients[8];
	cmd.F2Coeff0         = in->filter2Coefficients[0];
	cmd.F2Coeff1         = in->filter2Coefficients[1];
	cmd.F2Coeff2         = in->filter2Coefficients[2];
	cmd.F2Coeff3         = in->filter2Coefficients[3];
	cmd.F2Coeff4         = in->filter2Coefficients[4];
	cmd.F2Coeff5         = in->filter2Coefficients[5];
	cmd.F2Coeff6         = in->filter2Coefficients[6];
	cmd.F2Coeff7         = in->filter2Coefficients[7];
	cmd.F2Coeff8         = in->filter2Coefficients[8];

	vfe_prog_hw(ctrl->vfebase + VFE_ASF_CFG,
		(uint32_t *)&cmd, sizeof(cmd));
}