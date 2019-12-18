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
 int /*<<< orphan*/  CTRL_BRIGHTNESS ; 
 int /*<<< orphan*/  CTRL_CONTRAST ; 
 int /*<<< orphan*/  CTRL_HUE ; 
 int /*<<< orphan*/  CTRL_SATURATION ; 
 int /*<<< orphan*/  CTRL_SHARPNESS ; 
 int EINVAL ; 
#define  V4L2_CID_BRIGHTNESS 132 
#define  V4L2_CID_CONTRAST 131 
#define  V4L2_CID_HUE 130 
#define  V4L2_CID_SATURATION 129 
#define  V4L2_CID_SHARPNESS 128 
 int hdpvr_config_call (struct hdpvr_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vidioc_s_ctrl(struct file *file, void *private_data,
			 struct v4l2_control *ctrl)
{
	struct hdpvr_fh *fh = file->private_data;
	struct hdpvr_device *dev = fh->dev;
	int retval;

	switch (ctrl->id) {
	case V4L2_CID_BRIGHTNESS:
		retval = hdpvr_config_call(dev, CTRL_BRIGHTNESS, ctrl->value);
		if (!retval)
			dev->options.brightness = ctrl->value;
		break;
	case V4L2_CID_CONTRAST:
		retval = hdpvr_config_call(dev, CTRL_CONTRAST, ctrl->value);
		if (!retval)
			dev->options.contrast = ctrl->value;
		break;
	case V4L2_CID_SATURATION:
		retval = hdpvr_config_call(dev, CTRL_SATURATION, ctrl->value);
		if (!retval)
			dev->options.saturation = ctrl->value;
		break;
	case V4L2_CID_HUE:
		retval = hdpvr_config_call(dev, CTRL_HUE, ctrl->value);
		if (!retval)
			dev->options.hue = ctrl->value;
		break;
	case V4L2_CID_SHARPNESS:
		retval = hdpvr_config_call(dev, CTRL_SHARPNESS, ctrl->value);
		if (!retval)
			dev->options.sharpness = ctrl->value;
		break;
	default:
		return -EINVAL;
	}

	return retval;
}