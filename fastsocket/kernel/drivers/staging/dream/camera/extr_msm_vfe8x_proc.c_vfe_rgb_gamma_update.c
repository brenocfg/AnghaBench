#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vfe_cmd_rgb_gamma_config {int channelSelect; int /*<<< orphan*/  table; int /*<<< orphan*/  enable; } ;
struct TYPE_5__ {int ch0BankSelect; int ch1BankSelect; int ch2BankSelect; } ;
struct TYPE_4__ {int /*<<< orphan*/  rgbLUTEnable; } ;
struct TYPE_6__ {TYPE_2__ vfeGammaLutSel; TYPE_1__ vfeModuleEnableLocal; } ;

/* Variables and functions */
 int EINVAL ; 
#define  RGB_GAMMA_CH0_CH1_CH2_SELECTED 134 
#define  RGB_GAMMA_CH0_CH1_SELECTED 133 
#define  RGB_GAMMA_CH0_CH2_SELECTED 132 
#define  RGB_GAMMA_CH0_SELECTED 131 
#define  RGB_GAMMA_CH1_CH2_SELECTED 130 
#define  RGB_GAMMA_CH1_SELECTED 129 
#define  RGB_GAMMA_CH2_SELECTED 128 
 TYPE_3__* ctrl ; 
 int /*<<< orphan*/  vfe_program_lut_bank_sel (TYPE_2__*) ; 
 int /*<<< orphan*/  vfe_write_gamma_table (int,int,int /*<<< orphan*/ ) ; 

int vfe_rgb_gamma_update(struct vfe_cmd_rgb_gamma_config *in)
{
	int rc = 0;

	ctrl->vfeModuleEnableLocal.rgbLUTEnable = in->enable;

	switch (in->channelSelect) {
	case RGB_GAMMA_CH0_SELECTED:
		ctrl->vfeGammaLutSel.ch0BankSelect ^= 1;
		vfe_write_gamma_table(0,
			ctrl->vfeGammaLutSel.ch0BankSelect, in->table);
		break;

	case RGB_GAMMA_CH1_SELECTED:
		ctrl->vfeGammaLutSel.ch1BankSelect ^= 1;
		vfe_write_gamma_table(1,
			ctrl->vfeGammaLutSel.ch1BankSelect, in->table);
		break;

	case RGB_GAMMA_CH2_SELECTED:
		ctrl->vfeGammaLutSel.ch2BankSelect ^= 1;
		vfe_write_gamma_table(2,
			ctrl->vfeGammaLutSel.ch2BankSelect, in->table);
		break;

	case RGB_GAMMA_CH0_CH1_SELECTED:
		ctrl->vfeGammaLutSel.ch0BankSelect ^= 1;
		ctrl->vfeGammaLutSel.ch1BankSelect ^= 1;
		vfe_write_gamma_table(0, ctrl->vfeGammaLutSel.ch0BankSelect,
			in->table);
		vfe_write_gamma_table(1, ctrl->vfeGammaLutSel.ch1BankSelect,
			in->table);
		break;

	case RGB_GAMMA_CH0_CH2_SELECTED:
		ctrl->vfeGammaLutSel.ch0BankSelect ^= 1;
		ctrl->vfeGammaLutSel.ch2BankSelect ^= 1;
		vfe_write_gamma_table(0, ctrl->vfeGammaLutSel.ch0BankSelect,
			in->table);
		vfe_write_gamma_table(2, ctrl->vfeGammaLutSel.ch2BankSelect,
			in->table);
		break;

	case RGB_GAMMA_CH1_CH2_SELECTED:
		ctrl->vfeGammaLutSel.ch1BankSelect ^= 1;
		ctrl->vfeGammaLutSel.ch2BankSelect ^= 1;
		vfe_write_gamma_table(1, ctrl->vfeGammaLutSel.ch1BankSelect,
			in->table);
		vfe_write_gamma_table(2, ctrl->vfeGammaLutSel.ch2BankSelect,
			in->table);
		break;

	case RGB_GAMMA_CH0_CH1_CH2_SELECTED:
		ctrl->vfeGammaLutSel.ch0BankSelect ^= 1;
		ctrl->vfeGammaLutSel.ch1BankSelect ^= 1;
		ctrl->vfeGammaLutSel.ch2BankSelect ^= 1;
		vfe_write_gamma_table(0, ctrl->vfeGammaLutSel.ch0BankSelect,
			in->table);
		vfe_write_gamma_table(1, ctrl->vfeGammaLutSel.ch1BankSelect,
			in->table);
		vfe_write_gamma_table(2, ctrl->vfeGammaLutSel.ch2BankSelect,
			in->table);
		break;

	default:
		return -EINVAL;
	} /* switch */

	/* update the gammaLutSel register. */
	vfe_program_lut_bank_sel(&ctrl->vfeGammaLutSel);

	return rc;
}