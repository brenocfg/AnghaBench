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
struct v4l2_control {scalar_t__ id; int value; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_CID_AUDIO_MUTE ; 
 scalar_t__ V4L2_CID_AUDIO_VOLUME ; 
 int cs5345_read (struct v4l2_subdev*,int) ; 

__attribute__((used)) static int cs5345_g_ctrl(struct v4l2_subdev *sd, struct v4l2_control *ctrl)
{
	if (ctrl->id == V4L2_CID_AUDIO_MUTE) {
		ctrl->value = (cs5345_read(sd, 0x04) & 0x08) != 0;
		return 0;
	}
	if (ctrl->id != V4L2_CID_AUDIO_VOLUME)
		return -EINVAL;
	ctrl->value = cs5345_read(sd, 0x07) & 0x3f;
	if (ctrl->value >= 32)
		ctrl->value = ctrl->value - 64;
	return 0;
}