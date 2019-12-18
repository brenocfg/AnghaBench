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
typedef  int u16 ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_ctrl {int id; int /*<<< orphan*/  val; } ;
struct ivtv {TYPE_2__* card; } ;
struct TYPE_3__ {int mask; int mute; } ;
struct TYPE_4__ {TYPE_1__ gpio_audio_mute; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IVTV_REG_GPIO_OUT ; 
#define  V4L2_CID_AUDIO_MUTE 128 
 int read_reg (int /*<<< orphan*/ ) ; 
 struct ivtv* sd_to_ivtv (struct v4l2_subdev*) ; 
 struct v4l2_subdev* to_sd (struct v4l2_ctrl*) ; 
 int /*<<< orphan*/  write_reg (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int subdev_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct v4l2_subdev *sd = to_sd(ctrl);
	struct ivtv *itv = sd_to_ivtv(sd);
	u16 mask, data;

	switch (ctrl->id) {
	case V4L2_CID_AUDIO_MUTE:
		mask = itv->card->gpio_audio_mute.mask;
		data = ctrl->val ? itv->card->gpio_audio_mute.mute : 0;
		if (mask)
			write_reg((read_reg(IVTV_REG_GPIO_OUT) & ~mask) |
					(data & mask), IVTV_REG_GPIO_OUT);
		return 0;
	}
	return -EINVAL;
}