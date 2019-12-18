#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct v4l2_control {scalar_t__ id; scalar_t__ value; } ;
struct em28xx {scalar_t__ mute; scalar_t__ volume; } ;
struct TYPE_3__ {scalar_t__ id; scalar_t__ minimum; scalar_t__ maximum; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int ERANGE ; 
#define  V4L2_CID_AUDIO_MUTE 129 
#define  V4L2_CID_AUDIO_VOLUME 128 
 TYPE_1__* ac97_qctrl ; 
 int em28xx_audio_analog_set (struct em28xx*) ; 

__attribute__((used)) static int ac97_set_ctrl(struct em28xx *dev, const struct v4l2_control *ctrl)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(ac97_qctrl); i++)
		if (ctrl->id == ac97_qctrl[i].id)
			goto handle;

	/* Announce that hasn't handle it */
	return 1;

handle:
	if (ctrl->value < ac97_qctrl[i].minimum ||
	    ctrl->value > ac97_qctrl[i].maximum)
		return -ERANGE;

	switch (ctrl->id) {
	case V4L2_CID_AUDIO_MUTE:
		dev->mute = ctrl->value;
		break;
	case V4L2_CID_AUDIO_VOLUME:
		dev->volume = ctrl->value;
		break;
	}

	return em28xx_audio_analog_set(dev);
}