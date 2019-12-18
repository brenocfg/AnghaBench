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
struct vfe_color_correction_cfg {int /*<<< orphan*/  coefQFactor; int /*<<< orphan*/  k2; int /*<<< orphan*/  k1; int /*<<< orphan*/  k0; int /*<<< orphan*/  c8; int /*<<< orphan*/  c7; int /*<<< orphan*/  c6; int /*<<< orphan*/  c5; int /*<<< orphan*/  c4; int /*<<< orphan*/  c3; int /*<<< orphan*/  c2; int /*<<< orphan*/  c1; int /*<<< orphan*/  c0; } ;
struct vfe_cmd_color_correction_config {int /*<<< orphan*/  coefQFactor; int /*<<< orphan*/  K2; int /*<<< orphan*/  K1; int /*<<< orphan*/  K0; int /*<<< orphan*/  C8; int /*<<< orphan*/  C7; int /*<<< orphan*/  C6; int /*<<< orphan*/  C5; int /*<<< orphan*/  C4; int /*<<< orphan*/  C3; int /*<<< orphan*/  C2; int /*<<< orphan*/  C1; int /*<<< orphan*/  C0; int /*<<< orphan*/  enable; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_3__ {int /*<<< orphan*/  colorCorrectionEnable; } ;
struct TYPE_4__ {scalar_t__ vfebase; TYPE_1__ vfeModuleEnableLocal; } ;

/* Variables and functions */
 scalar_t__ VFE_COLOR_CORRECT_COEFF_0 ; 
 TYPE_2__* ctrl ; 
 int /*<<< orphan*/  memset (struct vfe_color_correction_cfg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vfe_prog_hw (scalar_t__,int /*<<< orphan*/ *,int) ; 

void vfe_color_correction_config(
	struct vfe_cmd_color_correction_config *in)
{
	struct vfe_color_correction_cfg cmd;

	memset(&cmd, 0, sizeof(cmd));
	ctrl->vfeModuleEnableLocal.colorCorrectionEnable = in->enable;

	cmd.c0 = in->C0;
	cmd.c1 = in->C1;
	cmd.c2 = in->C2;
	cmd.c3 = in->C3;
	cmd.c4 = in->C4;
	cmd.c5 = in->C5;
	cmd.c6 = in->C6;
	cmd.c7 = in->C7;
	cmd.c8 = in->C8;

	cmd.k0 = in->K0;
	cmd.k1 = in->K1;
	cmd.k2 = in->K2;

	cmd.coefQFactor = in->coefQFactor;

	vfe_prog_hw(ctrl->vfebase + VFE_COLOR_CORRECT_COEFF_0,
		(uint32_t *)&cmd, sizeof(cmd));
}