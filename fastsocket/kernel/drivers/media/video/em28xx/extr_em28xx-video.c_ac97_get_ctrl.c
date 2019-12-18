#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct v4l2_control {int id; int /*<<< orphan*/  value; } ;
struct em28xx {int /*<<< orphan*/  volume; int /*<<< orphan*/  mute; } ;

/* Variables and functions */
#define  V4L2_CID_AUDIO_MUTE 129 
#define  V4L2_CID_AUDIO_VOLUME 128 

__attribute__((used)) static int ac97_get_ctrl(struct em28xx *dev, struct v4l2_control *ctrl)
{
	switch (ctrl->id) {
	case V4L2_CID_AUDIO_MUTE:
		ctrl->value = dev->mute;
		return 0;
	case V4L2_CID_AUDIO_VOLUME:
		ctrl->value = dev->volume;
		return 0;
	default:
		/* Control is not ac97 related */
		return 1;
	}
}