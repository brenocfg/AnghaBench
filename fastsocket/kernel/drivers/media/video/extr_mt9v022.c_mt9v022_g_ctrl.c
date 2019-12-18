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
struct v4l2_queryctrl {unsigned long maximum; unsigned long minimum; } ;
struct v4l2_control {int id; int value; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MT9V022_AEC_AGC_ENABLE ; 
 int /*<<< orphan*/  MT9V022_ANALOG_GAIN ; 
 int /*<<< orphan*/  MT9V022_READ_MODE ; 
 int /*<<< orphan*/  MT9V022_TOTAL_SHUTTER_WIDTH ; 
#define  V4L2_CID_AUTOGAIN 133 
#define  V4L2_CID_EXPOSURE 132 
#define  V4L2_CID_EXPOSURE_AUTO 131 
#define  V4L2_CID_GAIN 130 
#define  V4L2_CID_HFLIP 129 
#define  V4L2_CID_VFLIP 128 
 int /*<<< orphan*/  mt9v022_ops ; 
 int reg_read (struct i2c_client*,int /*<<< orphan*/ ) ; 
 struct v4l2_queryctrl* soc_camera_find_qctrl (int /*<<< orphan*/ *,int) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int mt9v022_g_ctrl(struct v4l2_subdev *sd, struct v4l2_control *ctrl)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	const struct v4l2_queryctrl *qctrl;
	unsigned long range;
	int data;

	qctrl = soc_camera_find_qctrl(&mt9v022_ops, ctrl->id);

	switch (ctrl->id) {
	case V4L2_CID_VFLIP:
		data = reg_read(client, MT9V022_READ_MODE);
		if (data < 0)
			return -EIO;
		ctrl->value = !!(data & 0x10);
		break;
	case V4L2_CID_HFLIP:
		data = reg_read(client, MT9V022_READ_MODE);
		if (data < 0)
			return -EIO;
		ctrl->value = !!(data & 0x20);
		break;
	case V4L2_CID_EXPOSURE_AUTO:
		data = reg_read(client, MT9V022_AEC_AGC_ENABLE);
		if (data < 0)
			return -EIO;
		ctrl->value = !!(data & 0x1);
		break;
	case V4L2_CID_AUTOGAIN:
		data = reg_read(client, MT9V022_AEC_AGC_ENABLE);
		if (data < 0)
			return -EIO;
		ctrl->value = !!(data & 0x2);
		break;
	case V4L2_CID_GAIN:
		data = reg_read(client, MT9V022_ANALOG_GAIN);
		if (data < 0)
			return -EIO;

		range = qctrl->maximum - qctrl->minimum;
		ctrl->value = ((data - 16) * range + 24) / 48 + qctrl->minimum;

		break;
	case V4L2_CID_EXPOSURE:
		data = reg_read(client, MT9V022_TOTAL_SHUTTER_WIDTH);
		if (data < 0)
			return -EIO;

		range = qctrl->maximum - qctrl->minimum;
		ctrl->value = ((data - 1) * range + 239) / 479 + qctrl->minimum;

		break;
	}
	return 0;
}