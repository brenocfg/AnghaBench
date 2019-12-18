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
struct v4l2_control {int id; void* value; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TVP5150_BRIGHT_CTL ; 
 int /*<<< orphan*/  TVP5150_CONTRAST_CTL ; 
 int /*<<< orphan*/  TVP5150_HUE_CTL ; 
 int /*<<< orphan*/  TVP5150_SATURATION_CTL ; 
#define  V4L2_CID_BRIGHTNESS 131 
#define  V4L2_CID_CONTRAST 130 
#define  V4L2_CID_HUE 129 
#define  V4L2_CID_SATURATION 128 
 int /*<<< orphan*/  debug ; 
 void* tvp5150_read (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*) ; 

__attribute__((used)) static int tvp5150_g_ctrl(struct v4l2_subdev *sd, struct v4l2_control *ctrl)
{
	v4l2_dbg(1, debug, sd, "g_ctrl called\n");

	switch (ctrl->id) {
	case V4L2_CID_BRIGHTNESS:
		ctrl->value = tvp5150_read(sd, TVP5150_BRIGHT_CTL);
		return 0;
	case V4L2_CID_CONTRAST:
		ctrl->value = tvp5150_read(sd, TVP5150_CONTRAST_CTL);
		return 0;
	case V4L2_CID_SATURATION:
		ctrl->value = tvp5150_read(sd, TVP5150_SATURATION_CTL);
		return 0;
	case V4L2_CID_HUE:
		ctrl->value = tvp5150_read(sd, TVP5150_HUE_CTL);
		return 0;
	}
	return -EINVAL;
}