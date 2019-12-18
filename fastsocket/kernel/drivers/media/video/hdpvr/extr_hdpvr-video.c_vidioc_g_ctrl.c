#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct v4l2_control {int id; int /*<<< orphan*/  value; } ;
struct hdpvr_fh {struct hdpvr_device* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  sharpness; int /*<<< orphan*/  hue; int /*<<< orphan*/  saturation; int /*<<< orphan*/  contrast; int /*<<< orphan*/  brightness; } ;
struct hdpvr_device {TYPE_1__ options; } ;
struct file {struct hdpvr_fh* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_CID_BRIGHTNESS 132 
#define  V4L2_CID_CONTRAST 131 
#define  V4L2_CID_HUE 130 
#define  V4L2_CID_SATURATION 129 
#define  V4L2_CID_SHARPNESS 128 

__attribute__((used)) static int vidioc_g_ctrl(struct file *file, void *private_data,
			 struct v4l2_control *ctrl)
{
	struct hdpvr_fh *fh = file->private_data;
	struct hdpvr_device *dev = fh->dev;

	switch (ctrl->id) {
	case V4L2_CID_BRIGHTNESS:
		ctrl->value = dev->options.brightness;
		break;
	case V4L2_CID_CONTRAST:
		ctrl->value = dev->options.contrast;
		break;
	case V4L2_CID_SATURATION:
		ctrl->value = dev->options.saturation;
		break;
	case V4L2_CID_HUE:
		ctrl->value = dev->options.hue;
		break;
	case V4L2_CID_SHARPNESS:
		ctrl->value = dev->options.sharpness;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}