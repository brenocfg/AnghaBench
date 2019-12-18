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
struct vfe_cmd_rgb_gamma_config {int channelSelect; int /*<<< orphan*/  table; int /*<<< orphan*/  enable; } ;
struct TYPE_3__ {int /*<<< orphan*/  rgbLUTEnable; } ;
struct TYPE_4__ {TYPE_1__ vfeModuleEnableLocal; } ;

/* Variables and functions */
 int EINVAL ; 
#define  RGB_GAMMA_CH0_CH1_CH2_SELECTED 134 
#define  RGB_GAMMA_CH0_CH1_SELECTED 133 
#define  RGB_GAMMA_CH0_CH2_SELECTED 132 
#define  RGB_GAMMA_CH0_SELECTED 131 
#define  RGB_GAMMA_CH1_CH2_SELECTED 130 
#define  RGB_GAMMA_CH1_SELECTED 129 
#define  RGB_GAMMA_CH2_SELECTED 128 
 TYPE_2__* ctrl ; 
 int /*<<< orphan*/  vfe_write_gamma_table (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int vfe_rgb_gamma_config(struct vfe_cmd_rgb_gamma_config *in)
{
	int rc = 0;

	ctrl->vfeModuleEnableLocal.rgbLUTEnable = in->enable;

	switch (in->channelSelect) {
	case RGB_GAMMA_CH0_SELECTED:
vfe_write_gamma_table(0, 0, in->table);
break;

	case RGB_GAMMA_CH1_SELECTED:
		vfe_write_gamma_table(1, 0, in->table);
		break;

	case RGB_GAMMA_CH2_SELECTED:
		vfe_write_gamma_table(2, 0, in->table);
		break;

	case RGB_GAMMA_CH0_CH1_SELECTED:
		vfe_write_gamma_table(0, 0, in->table);
		vfe_write_gamma_table(1, 0, in->table);
		break;

	case RGB_GAMMA_CH0_CH2_SELECTED:
		vfe_write_gamma_table(0, 0, in->table);
		vfe_write_gamma_table(2, 0, in->table);
		break;

	case RGB_GAMMA_CH1_CH2_SELECTED:
		vfe_write_gamma_table(1, 0, in->table);
		vfe_write_gamma_table(2, 0, in->table);
		break;

	case RGB_GAMMA_CH0_CH1_CH2_SELECTED:
		vfe_write_gamma_table(0, 0, in->table);
		vfe_write_gamma_table(1, 0, in->table);
		vfe_write_gamma_table(2, 0, in->table);
		break;

	default:
		rc = -EINVAL;
		break;
	} /* switch */

	return rc;
}