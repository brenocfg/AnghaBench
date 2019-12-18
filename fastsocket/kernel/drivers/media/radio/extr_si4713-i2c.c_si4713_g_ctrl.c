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
struct si4713_device {int /*<<< orphan*/  mutex; int /*<<< orphan*/  mute; scalar_t__ power_state; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  SI4713_TX_LINE_INPUT_MUTE ; 
#define  V4L2_CID_AUDIO_MUTE 128 
 int /*<<< orphan*/  get_mute (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int si4713_read_property (struct si4713_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct si4713_device* to_si4713_device (struct v4l2_subdev*) ; 

__attribute__((used)) static int si4713_g_ctrl(struct v4l2_subdev *sd, struct v4l2_control *ctrl)
{
	struct si4713_device *sdev = to_si4713_device(sd);
	int rval = 0;

	if (!sdev)
		return -ENODEV;

	mutex_lock(&sdev->mutex);

	if (sdev->power_state) {
		rval = si4713_read_property(sdev, SI4713_TX_LINE_INPUT_MUTE,
						&sdev->mute);

		if (rval < 0)
			goto unlock;
	}

	switch (ctrl->id) {
	case V4L2_CID_AUDIO_MUTE:
		ctrl->value = get_mute(sdev->mute);
		break;
	}

unlock:
	mutex_unlock(&sdev->mutex);
	return rval;
}