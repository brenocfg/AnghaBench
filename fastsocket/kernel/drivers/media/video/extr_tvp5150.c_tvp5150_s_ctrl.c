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
typedef  size_t u8 ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_control {scalar_t__ id; scalar_t__ value; } ;
struct TYPE_3__ {scalar_t__ id; scalar_t__ minimum; scalar_t__ maximum; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 int ERANGE ; 
 int /*<<< orphan*/  TVP5150_BRIGHT_CTL ; 
 int /*<<< orphan*/  TVP5150_CONTRAST_CTL ; 
 int /*<<< orphan*/  TVP5150_HUE_CTL ; 
 int /*<<< orphan*/  TVP5150_SATURATION_CTL ; 
#define  V4L2_CID_BRIGHTNESS 131 
#define  V4L2_CID_CONTRAST 130 
#define  V4L2_CID_HUE 129 
#define  V4L2_CID_SATURATION 128 
 int /*<<< orphan*/  debug ; 
 TYPE_1__* tvp5150_qctrl ; 
 int /*<<< orphan*/  tvp5150_write (struct v4l2_subdev*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int tvp5150_s_ctrl(struct v4l2_subdev *sd, struct v4l2_control *ctrl)
{
	u8 i, n;
	n = ARRAY_SIZE(tvp5150_qctrl);

	for (i = 0; i < n; i++) {
		if (ctrl->id != tvp5150_qctrl[i].id)
			continue;
		if (ctrl->value < tvp5150_qctrl[i].minimum ||
		    ctrl->value > tvp5150_qctrl[i].maximum)
			return -ERANGE;
		v4l2_dbg(1, debug, sd, "s_ctrl: id=%d, value=%d\n",
					ctrl->id, ctrl->value);
		break;
	}

	switch (ctrl->id) {
	case V4L2_CID_BRIGHTNESS:
		tvp5150_write(sd, TVP5150_BRIGHT_CTL, ctrl->value);
		return 0;
	case V4L2_CID_CONTRAST:
		tvp5150_write(sd, TVP5150_CONTRAST_CTL, ctrl->value);
		return 0;
	case V4L2_CID_SATURATION:
		tvp5150_write(sd, TVP5150_SATURATION_CTL, ctrl->value);
		return 0;
	case V4L2_CID_HUE:
		tvp5150_write(sd, TVP5150_HUE_CTL, ctrl->value);
		return 0;
	}
	return -EINVAL;
}