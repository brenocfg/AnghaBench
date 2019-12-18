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
struct v4l2_subdev {int dummy; } ;
struct v4l2_control {int id; int /*<<< orphan*/  value; } ;
struct si4713_device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  POWER_DOWN ; 
 int /*<<< orphan*/  POWER_UP ; 
#define  V4L2_CID_AUDIO_MUTE 128 
 int si4713_set_mute (struct si4713_device*,int /*<<< orphan*/ ) ; 
 int si4713_set_power_state (struct si4713_device*,int /*<<< orphan*/ ) ; 
 int si4713_setup (struct si4713_device*) ; 
 struct si4713_device* to_si4713_device (struct v4l2_subdev*) ; 

__attribute__((used)) static int si4713_s_ctrl(struct v4l2_subdev *sd, struct v4l2_control *ctrl)
{
	struct si4713_device *sdev = to_si4713_device(sd);
	int rval = 0;

	if (!sdev)
		return -ENODEV;

	switch (ctrl->id) {
	case V4L2_CID_AUDIO_MUTE:
		if (ctrl->value) {
			rval = si4713_set_mute(sdev, ctrl->value);
			if (rval < 0)
				goto exit;

			rval = si4713_set_power_state(sdev, POWER_DOWN);
		} else {
			rval = si4713_set_power_state(sdev, POWER_UP);
			if (rval < 0)
				goto exit;

			rval = si4713_setup(sdev);
			if (rval < 0)
				goto exit;

			rval = si4713_set_mute(sdev, ctrl->value);
		}
		break;
	}

exit:
	return rval;
}