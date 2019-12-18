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
struct v4l2_tuner {int audmode; } ;
struct v4l2_subdev {int dummy; } ;
struct ivtv {TYPE_1__* card; } ;
struct TYPE_4__ {int mask; int lang1; int lang2; int mono; int stereo; } ;
struct TYPE_3__ {TYPE_2__ gpio_audio_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  IVTV_REG_GPIO_OUT ; 
#define  V4L2_TUNER_MODE_LANG1 132 
#define  V4L2_TUNER_MODE_LANG1_LANG2 131 
#define  V4L2_TUNER_MODE_LANG2 130 
#define  V4L2_TUNER_MODE_MONO 129 
#define  V4L2_TUNER_MODE_STEREO 128 
 int read_reg (int /*<<< orphan*/ ) ; 
 struct ivtv* sd_to_ivtv (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  write_reg (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int subdev_s_tuner(struct v4l2_subdev *sd, struct v4l2_tuner *vt)
{
	struct ivtv *itv = sd_to_ivtv(sd);
	u16 mask, data;

	mask = itv->card->gpio_audio_mode.mask;
	switch (vt->audmode) {
	case V4L2_TUNER_MODE_LANG1:
		data = itv->card->gpio_audio_mode.lang1;
		break;
	case V4L2_TUNER_MODE_LANG2:
		data = itv->card->gpio_audio_mode.lang2;
		break;
	case V4L2_TUNER_MODE_MONO:
		data = itv->card->gpio_audio_mode.mono;
		break;
	case V4L2_TUNER_MODE_STEREO:
	case V4L2_TUNER_MODE_LANG1_LANG2:
	default:
		data = itv->card->gpio_audio_mode.stereo;
		break;
	}
	if (mask)
		write_reg((read_reg(IVTV_REG_GPIO_OUT) & ~mask) | (data & mask), IVTV_REG_GPIO_OUT);
	return 0;
}