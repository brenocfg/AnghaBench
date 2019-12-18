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
struct v4l2_control {int id; int value; } ;
struct mt9t031 {int autoexposure; int gain; int exposure; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MT9T031_READ_MODE_2 ; 
#define  V4L2_CID_EXPOSURE 132 
#define  V4L2_CID_EXPOSURE_AUTO 131 
#define  V4L2_CID_GAIN 130 
#define  V4L2_CID_HFLIP 129 
#define  V4L2_CID_VFLIP 128 
 int reg_read (struct i2c_client*,int /*<<< orphan*/ ) ; 
 struct mt9t031* to_mt9t031 (struct i2c_client*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int mt9t031_g_ctrl(struct v4l2_subdev *sd, struct v4l2_control *ctrl)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct mt9t031 *mt9t031 = to_mt9t031(client);
	int data;

	switch (ctrl->id) {
	case V4L2_CID_VFLIP:
		data = reg_read(client, MT9T031_READ_MODE_2);
		if (data < 0)
			return -EIO;
		ctrl->value = !!(data & 0x8000);
		break;
	case V4L2_CID_HFLIP:
		data = reg_read(client, MT9T031_READ_MODE_2);
		if (data < 0)
			return -EIO;
		ctrl->value = !!(data & 0x4000);
		break;
	case V4L2_CID_EXPOSURE_AUTO:
		ctrl->value = mt9t031->autoexposure;
		break;
	case V4L2_CID_GAIN:
		ctrl->value = mt9t031->gain;
		break;
	case V4L2_CID_EXPOSURE:
		ctrl->value = mt9t031->exposure;
		break;
	}
	return 0;
}