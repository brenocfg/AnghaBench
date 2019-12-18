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
typedef  int u8 ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_control {scalar_t__ id; int value; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_CID_AUDIO_MUTE ; 
 scalar_t__ V4L2_CID_AUDIO_VOLUME ; 
 int /*<<< orphan*/  cs5345_write (struct v4l2_subdev*,int,int) ; 

__attribute__((used)) static int cs5345_s_ctrl(struct v4l2_subdev *sd, struct v4l2_control *ctrl)
{
	if (ctrl->id == V4L2_CID_AUDIO_MUTE) {
		cs5345_write(sd, 0x04, ctrl->value ? 0x80 : 0);
		return 0;
	}
	if (ctrl->id != V4L2_CID_AUDIO_VOLUME)
		return -EINVAL;
	if (ctrl->value > 24 || ctrl->value < -24)
		return -EINVAL;
	cs5345_write(sd, 0x07, ((u8)ctrl->value) & 0x3f);
	cs5345_write(sd, 0x08, ((u8)ctrl->value) & 0x3f);
	return 0;
}