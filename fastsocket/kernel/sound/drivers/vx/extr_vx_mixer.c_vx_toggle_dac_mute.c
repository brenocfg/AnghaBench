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
struct vx_core {TYPE_2__* ops; TYPE_1__* hw; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* akm_write ) (struct vx_core*,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_3__ {unsigned int num_codecs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAC_ATTEN_MAX ; 
 int /*<<< orphan*/  DAC_ATTEN_MIN ; 
 int /*<<< orphan*/  XX_CODEC_DAC_CONTROL_REGISTER ; 
 int /*<<< orphan*/  stub1 (struct vx_core*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vx_set_codec_reg (struct vx_core*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void vx_toggle_dac_mute(struct vx_core *chip, int mute)
{
	unsigned int i;
	for (i = 0; i < chip->hw->num_codecs; i++) {
		if (chip->ops->akm_write)
			chip->ops->akm_write(chip, XX_CODEC_DAC_CONTROL_REGISTER, mute); /* XXX */
		else
			vx_set_codec_reg(chip, i, XX_CODEC_DAC_CONTROL_REGISTER,
					 mute ? DAC_ATTEN_MAX : DAC_ATTEN_MIN);
	}
}