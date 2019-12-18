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
struct v4l2_control {int id; unsigned long value; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
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
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  mt9v022_ops ; 
 int reg_clear (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reg_read (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int reg_set (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reg_write (struct i2c_client*,int /*<<< orphan*/ ,unsigned long) ; 
 struct v4l2_queryctrl* soc_camera_find_qctrl (int /*<<< orphan*/ *,int) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int mt9v022_s_ctrl(struct v4l2_subdev *sd, struct v4l2_control *ctrl)
{
	int data;
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	const struct v4l2_queryctrl *qctrl;

	qctrl = soc_camera_find_qctrl(&mt9v022_ops, ctrl->id);
	if (!qctrl)
		return -EINVAL;

	switch (ctrl->id) {
	case V4L2_CID_VFLIP:
		if (ctrl->value)
			data = reg_set(client, MT9V022_READ_MODE, 0x10);
		else
			data = reg_clear(client, MT9V022_READ_MODE, 0x10);
		if (data < 0)
			return -EIO;
		break;
	case V4L2_CID_HFLIP:
		if (ctrl->value)
			data = reg_set(client, MT9V022_READ_MODE, 0x20);
		else
			data = reg_clear(client, MT9V022_READ_MODE, 0x20);
		if (data < 0)
			return -EIO;
		break;
	case V4L2_CID_GAIN:
		/* mt9v022 has minimum == default */
		if (ctrl->value > qctrl->maximum || ctrl->value < qctrl->minimum)
			return -EINVAL;
		else {
			unsigned long range = qctrl->maximum - qctrl->minimum;
			/* Valid values 16 to 64, 32 to 64 must be even. */
			unsigned long gain = ((ctrl->value - qctrl->minimum) *
					      48 + range / 2) / range + 16;
			if (gain >= 32)
				gain &= ~1;
			/*
			 * The user wants to set gain manually, hope, she
			 * knows, what she's doing... Switch AGC off.
			 */

			if (reg_clear(client, MT9V022_AEC_AGC_ENABLE, 0x2) < 0)
				return -EIO;

			dev_dbg(&client->dev, "Setting gain from %d to %lu\n",
				reg_read(client, MT9V022_ANALOG_GAIN), gain);
			if (reg_write(client, MT9V022_ANALOG_GAIN, gain) < 0)
				return -EIO;
		}
		break;
	case V4L2_CID_EXPOSURE:
		/* mt9v022 has maximum == default */
		if (ctrl->value > qctrl->maximum || ctrl->value < qctrl->minimum)
			return -EINVAL;
		else {
			unsigned long range = qctrl->maximum - qctrl->minimum;
			unsigned long shutter = ((ctrl->value - qctrl->minimum) *
						 479 + range / 2) / range + 1;
			/*
			 * The user wants to set shutter width manually, hope,
			 * she knows, what she's doing... Switch AEC off.
			 */

			if (reg_clear(client, MT9V022_AEC_AGC_ENABLE, 0x1) < 0)
				return -EIO;

			dev_dbg(&client->dev, "Shutter width from %d to %lu\n",
				reg_read(client, MT9V022_TOTAL_SHUTTER_WIDTH),
				shutter);
			if (reg_write(client, MT9V022_TOTAL_SHUTTER_WIDTH,
				      shutter) < 0)
				return -EIO;
		}
		break;
	case V4L2_CID_AUTOGAIN:
		if (ctrl->value)
			data = reg_set(client, MT9V022_AEC_AGC_ENABLE, 0x2);
		else
			data = reg_clear(client, MT9V022_AEC_AGC_ENABLE, 0x2);
		if (data < 0)
			return -EIO;
		break;
	case V4L2_CID_EXPOSURE_AUTO:
		if (ctrl->value)
			data = reg_set(client, MT9V022_AEC_AGC_ENABLE, 0x1);
		else
			data = reg_clear(client, MT9V022_AEC_AGC_ENABLE, 0x1);
		if (data < 0)
			return -EIO;
		break;
	}
	return 0;
}