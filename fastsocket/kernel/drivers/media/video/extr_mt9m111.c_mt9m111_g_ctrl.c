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
struct mt9m111 {int autoexposure; int autowhitebalance; int /*<<< orphan*/  context; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  HIGHPOWER ; 
 int MT9M111_RMB_MIRROR_COLS ; 
 int MT9M111_RMB_MIRROR_ROWS ; 
 int /*<<< orphan*/  READ_MODE_A ; 
 int /*<<< orphan*/  READ_MODE_B ; 
#define  V4L2_CID_AUTO_WHITE_BALANCE 132 
#define  V4L2_CID_EXPOSURE_AUTO 131 
#define  V4L2_CID_GAIN 130 
#define  V4L2_CID_HFLIP 129 
#define  V4L2_CID_VFLIP 128 
 int mt9m111_get_global_gain (struct i2c_client*) ; 
 int reg_read (int /*<<< orphan*/ ) ; 
 struct mt9m111* to_mt9m111 (struct i2c_client*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int mt9m111_g_ctrl(struct v4l2_subdev *sd, struct v4l2_control *ctrl)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct mt9m111 *mt9m111 = to_mt9m111(client);
	int data;

	switch (ctrl->id) {
	case V4L2_CID_VFLIP:
		if (mt9m111->context == HIGHPOWER)
			data = reg_read(READ_MODE_B);
		else
			data = reg_read(READ_MODE_A);

		if (data < 0)
			return -EIO;
		ctrl->value = !!(data & MT9M111_RMB_MIRROR_ROWS);
		break;
	case V4L2_CID_HFLIP:
		if (mt9m111->context == HIGHPOWER)
			data = reg_read(READ_MODE_B);
		else
			data = reg_read(READ_MODE_A);

		if (data < 0)
			return -EIO;
		ctrl->value = !!(data & MT9M111_RMB_MIRROR_COLS);
		break;
	case V4L2_CID_GAIN:
		data = mt9m111_get_global_gain(client);
		if (data < 0)
			return data;
		ctrl->value = data;
		break;
	case V4L2_CID_EXPOSURE_AUTO:
		ctrl->value = mt9m111->autoexposure;
		break;
	case V4L2_CID_AUTO_WHITE_BALANCE:
		ctrl->value = mt9m111->autowhitebalance;
		break;
	}
	return 0;
}