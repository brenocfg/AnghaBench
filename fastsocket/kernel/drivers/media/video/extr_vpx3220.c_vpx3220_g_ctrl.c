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
struct vpx3220 {int /*<<< orphan*/  hue; int /*<<< orphan*/  sat; int /*<<< orphan*/  contrast; int /*<<< orphan*/  bright; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_control {int id; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_CID_BRIGHTNESS 131 
#define  V4L2_CID_CONTRAST 130 
#define  V4L2_CID_HUE 129 
#define  V4L2_CID_SATURATION 128 
 struct vpx3220* to_vpx3220 (struct v4l2_subdev*) ; 

__attribute__((used)) static int vpx3220_g_ctrl(struct v4l2_subdev *sd, struct v4l2_control *ctrl)
{
	struct vpx3220 *decoder = to_vpx3220(sd);

	switch (ctrl->id) {
	case V4L2_CID_BRIGHTNESS:
		ctrl->value = decoder->bright;
		break;
	case V4L2_CID_CONTRAST:
		ctrl->value = decoder->contrast;
		break;
	case V4L2_CID_SATURATION:
		ctrl->value = decoder->sat;
		break;
	case V4L2_CID_HUE:
		ctrl->value = decoder->hue;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}