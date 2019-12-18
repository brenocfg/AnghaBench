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

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_CID_AUTOGAIN 137 
#define  V4L2_CID_BRIGHTNESS 136 
#define  V4L2_CID_CONTRAST 135 
#define  V4L2_CID_EXPOSURE 134 
#define  V4L2_CID_EXPOSURE_AUTO 133 
#define  V4L2_CID_GAIN 132 
#define  V4L2_CID_HFLIP 131 
#define  V4L2_CID_HUE 130 
#define  V4L2_CID_SATURATION 129 
#define  V4L2_CID_VFLIP 128 
 int ov7670_g_autoexp (struct v4l2_subdev*,int /*<<< orphan*/ *) ; 
 int ov7670_g_autogain (struct v4l2_subdev*,int /*<<< orphan*/ *) ; 
 int ov7670_g_brightness (struct v4l2_subdev*,int /*<<< orphan*/ *) ; 
 int ov7670_g_contrast (struct v4l2_subdev*,int /*<<< orphan*/ *) ; 
 int ov7670_g_exp (struct v4l2_subdev*,int /*<<< orphan*/ *) ; 
 int ov7670_g_gain (struct v4l2_subdev*,int /*<<< orphan*/ *) ; 
 int ov7670_g_hflip (struct v4l2_subdev*,int /*<<< orphan*/ *) ; 
 int ov7670_g_hue (struct v4l2_subdev*,int /*<<< orphan*/ *) ; 
 int ov7670_g_sat (struct v4l2_subdev*,int /*<<< orphan*/ *) ; 
 int ov7670_g_vflip (struct v4l2_subdev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ov7670_g_ctrl(struct v4l2_subdev *sd, struct v4l2_control *ctrl)
{
	switch (ctrl->id) {
	case V4L2_CID_BRIGHTNESS:
		return ov7670_g_brightness(sd, &ctrl->value);
	case V4L2_CID_CONTRAST:
		return ov7670_g_contrast(sd, &ctrl->value);
	case V4L2_CID_SATURATION:
		return ov7670_g_sat(sd, &ctrl->value);
	case V4L2_CID_HUE:
		return ov7670_g_hue(sd, &ctrl->value);
	case V4L2_CID_VFLIP:
		return ov7670_g_vflip(sd, &ctrl->value);
	case V4L2_CID_HFLIP:
		return ov7670_g_hflip(sd, &ctrl->value);
	case V4L2_CID_GAIN:
		return ov7670_g_gain(sd, &ctrl->value);
	case V4L2_CID_AUTOGAIN:
		return ov7670_g_autogain(sd, &ctrl->value);
	case V4L2_CID_EXPOSURE:
		return ov7670_g_exp(sd, &ctrl->value);
	case V4L2_CID_EXPOSURE_AUTO:
		return ov7670_g_autoexp(sd, &ctrl->value);
	}
	return -EINVAL;
}