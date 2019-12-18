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
typedef  int u32 ;
typedef  int u16 ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_queryctrl {unsigned long maximum; unsigned long minimum; unsigned long default_value; } ;
struct v4l2_control {int id; unsigned long value; } ;
struct TYPE_2__ {int const height; } ;
struct mt9t031 {unsigned long gain; int exposure; int autoexposure; int const y_skip_top; TYPE_1__ rect; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 size_t MT9T031_CTRL_EXPOSURE ; 
 size_t MT9T031_CTRL_GAIN ; 
 int /*<<< orphan*/  MT9T031_GLOBAL_GAIN ; 
 int const MT9T031_MAX_HEIGHT ; 
 int /*<<< orphan*/  MT9T031_READ_MODE_2 ; 
 int MT9T031_VERTICAL_BLANK ; 
#define  V4L2_CID_EXPOSURE 132 
#define  V4L2_CID_EXPOSURE_AUTO 131 
#define  V4L2_CID_GAIN 130 
#define  V4L2_CID_HFLIP 129 
#define  V4L2_CID_VFLIP 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  get_shutter (struct i2c_client*,int*) ; 
 struct v4l2_queryctrl* mt9t031_controls ; 
 int reg_clear (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int reg_read (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int reg_set (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int reg_write (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_shutter (struct i2c_client*,int const) ; 
 struct mt9t031* to_mt9t031 (struct i2c_client*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int mt9t031_s_ctrl(struct v4l2_subdev *sd, struct v4l2_control *ctrl)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct mt9t031 *mt9t031 = to_mt9t031(client);
	const struct v4l2_queryctrl *qctrl;
	int data;

	switch (ctrl->id) {
	case V4L2_CID_VFLIP:
		if (ctrl->value)
			data = reg_set(client, MT9T031_READ_MODE_2, 0x8000);
		else
			data = reg_clear(client, MT9T031_READ_MODE_2, 0x8000);
		if (data < 0)
			return -EIO;
		break;
	case V4L2_CID_HFLIP:
		if (ctrl->value)
			data = reg_set(client, MT9T031_READ_MODE_2, 0x4000);
		else
			data = reg_clear(client, MT9T031_READ_MODE_2, 0x4000);
		if (data < 0)
			return -EIO;
		break;
	case V4L2_CID_GAIN:
		qctrl = &mt9t031_controls[MT9T031_CTRL_GAIN];
		if (ctrl->value > qctrl->maximum || ctrl->value < qctrl->minimum)
			return -EINVAL;
		/* See Datasheet Table 7, Gain settings. */
		if (ctrl->value <= qctrl->default_value) {
			/* Pack it into 0..1 step 0.125, register values 0..8 */
			unsigned long range = qctrl->default_value - qctrl->minimum;
			data = ((ctrl->value - qctrl->minimum) * 8 + range / 2) / range;

			dev_dbg(&client->dev, "Setting gain %d\n", data);
			data = reg_write(client, MT9T031_GLOBAL_GAIN, data);
			if (data < 0)
				return -EIO;
		} else {
			/* Pack it into 1.125..128 variable step, register values 9..0x7860 */
			/* We assume qctrl->maximum - qctrl->default_value - 1 > 0 */
			unsigned long range = qctrl->maximum - qctrl->default_value - 1;
			/* calculated gain: map 65..127 to 9..1024 step 0.125 */
			unsigned long gain = ((ctrl->value - qctrl->default_value - 1) *
					       1015 + range / 2) / range + 9;

			if (gain <= 32)		/* calculated gain 9..32 -> 9..32 */
				data = gain;
			else if (gain <= 64)	/* calculated gain 33..64 -> 0x51..0x60 */
				data = ((gain - 32) * 16 + 16) / 32 + 80;
			else
				/* calculated gain 65..1024 -> (1..120) << 8 + 0x60 */
				data = (((gain - 64 + 7) * 32) & 0xff00) | 0x60;

			dev_dbg(&client->dev, "Set gain from 0x%x to 0x%x\n",
				reg_read(client, MT9T031_GLOBAL_GAIN), data);
			data = reg_write(client, MT9T031_GLOBAL_GAIN, data);
			if (data < 0)
				return -EIO;
		}

		/* Success */
		mt9t031->gain = ctrl->value;
		break;
	case V4L2_CID_EXPOSURE:
		qctrl = &mt9t031_controls[MT9T031_CTRL_EXPOSURE];
		/* mt9t031 has maximum == default */
		if (ctrl->value > qctrl->maximum || ctrl->value < qctrl->minimum)
			return -EINVAL;
		else {
			const unsigned long range = qctrl->maximum - qctrl->minimum;
			const u32 shutter = ((ctrl->value - qctrl->minimum) * 1048 +
					     range / 2) / range + 1;
			u32 old;

			get_shutter(client, &old);
			dev_dbg(&client->dev, "Set shutter from %u to %u\n",
				old, shutter);
			if (set_shutter(client, shutter) < 0)
				return -EIO;
			mt9t031->exposure = ctrl->value;
			mt9t031->autoexposure = 0;
		}
		break;
	case V4L2_CID_EXPOSURE_AUTO:
		if (ctrl->value) {
			const u16 vblank = MT9T031_VERTICAL_BLANK;
			const u32 shutter_max = MT9T031_MAX_HEIGHT + vblank;
			unsigned int total_h = mt9t031->rect.height +
				mt9t031->y_skip_top + vblank;

			if (set_shutter(client, total_h) < 0)
				return -EIO;
			qctrl = &mt9t031_controls[MT9T031_CTRL_EXPOSURE];
			mt9t031->exposure = (shutter_max / 2 + (total_h - 1) *
				 (qctrl->maximum - qctrl->minimum)) /
				shutter_max + qctrl->minimum;
			mt9t031->autoexposure = 1;
		} else
			mt9t031->autoexposure = 0;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}