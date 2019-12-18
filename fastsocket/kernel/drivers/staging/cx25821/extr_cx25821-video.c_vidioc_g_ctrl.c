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
struct v4l2_queryctrl {int dummy; } ;
struct v4l2_control {int id; int /*<<< orphan*/  value; } ;
struct file {int dummy; } ;
struct cx25821_fh {struct cx25821_dev* dev; } ;
struct cx25821_dev {int /*<<< orphan*/  ctl_saturation; int /*<<< orphan*/  ctl_contrast; int /*<<< orphan*/  ctl_hue; int /*<<< orphan*/  ctl_bright; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_CID_BRIGHTNESS 131 
#define  V4L2_CID_CONTRAST 130 
#define  V4L2_CID_HUE 129 
#define  V4L2_CID_SATURATION 128 
 struct v4l2_queryctrl* ctrl_by_id (int) ; 

int vidioc_g_ctrl(struct file *file, void *priv, struct v4l2_control *ctl)
{
	struct cx25821_dev *dev = ((struct cx25821_fh *)priv)->dev;

	const struct v4l2_queryctrl *ctrl;

	ctrl = ctrl_by_id(ctl->id);

	if (NULL == ctrl)
		return -EINVAL;
	switch (ctl->id) {
	case V4L2_CID_BRIGHTNESS:
		ctl->value = dev->ctl_bright;
		break;
	case V4L2_CID_HUE:
		ctl->value = dev->ctl_hue;
		break;
	case V4L2_CID_CONTRAST:
		ctl->value = dev->ctl_contrast;
		break;
	case V4L2_CID_SATURATION:
		ctl->value = dev->ctl_saturation;
		break;
	}
	return 0;
}