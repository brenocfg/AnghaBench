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
struct v4l2_control {int id; int value; } ;
struct sn9c102_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
#define  SN9C102_V4L2_CID_GREEN_BALANCE 132 
#define  V4L2_CID_BLACK_LEVEL 131 
#define  V4L2_CID_BLUE_BALANCE 130 
#define  V4L2_CID_GAIN 129 
#define  V4L2_CID_RED_BALANCE 128 
 int sn9c102_i2c_read (struct sn9c102_device*,int) ; 
 int sn9c102_i2c_write (struct sn9c102_device*,int,int) ; 

__attribute__((used)) static int hv7131r_set_ctrl(struct sn9c102_device* cam,
			    const struct v4l2_control* ctrl)
{
	int err = 0;

	switch (ctrl->id) {
	case V4L2_CID_GAIN:
		err += sn9c102_i2c_write(cam, 0x30, ctrl->value);
		break;
	case V4L2_CID_RED_BALANCE:
		err += sn9c102_i2c_write(cam, 0x31, ctrl->value);
		break;
	case V4L2_CID_BLUE_BALANCE:
		err += sn9c102_i2c_write(cam, 0x33, ctrl->value);
		break;
	case SN9C102_V4L2_CID_GREEN_BALANCE:
		err += sn9c102_i2c_write(cam, 0x32, ctrl->value);
		break;
	case V4L2_CID_BLACK_LEVEL:
		{
			int r = sn9c102_i2c_read(cam, 0x01);
			if (r < 0)
				return -EIO;
			err += sn9c102_i2c_write(cam, 0x01,
						 (ctrl->value<<3) | (r&0xf7));
		}
		break;
	default:
		return -EINVAL;
	}

	return err ? -EIO : 0;
}