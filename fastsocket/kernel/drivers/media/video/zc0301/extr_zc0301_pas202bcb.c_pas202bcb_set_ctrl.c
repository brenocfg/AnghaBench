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
struct zc0301_device {int dummy; } ;
struct v4l2_control {int id; int value; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
#define  V4L2_CID_BLUE_BALANCE 133 
#define  V4L2_CID_EXPOSURE 132 
#define  V4L2_CID_GAIN 131 
#define  V4L2_CID_RED_BALANCE 130 
#define  ZC0301_V4L2_CID_DAC_MAGNITUDE 129 
#define  ZC0301_V4L2_CID_GREEN_BALANCE 128 
 scalar_t__ zc0301_i2c_write (struct zc0301_device*,int,int) ; 

__attribute__((used)) static int pas202bcb_set_ctrl(struct zc0301_device* cam,
			      const struct v4l2_control* ctrl)
{
	int err = 0;

	switch (ctrl->id) {
	case V4L2_CID_EXPOSURE:
		err += zc0301_i2c_write(cam, 0x04, ctrl->value >> 6);
		err += zc0301_i2c_write(cam, 0x05, ctrl->value & 0x3f);
		break;
	case V4L2_CID_RED_BALANCE:
		err += zc0301_i2c_write(cam, 0x09, ctrl->value);
		break;
	case V4L2_CID_BLUE_BALANCE:
		err += zc0301_i2c_write(cam, 0x07, ctrl->value);
		break;
	case V4L2_CID_GAIN:
		err += zc0301_i2c_write(cam, 0x10, ctrl->value);
		break;
	case ZC0301_V4L2_CID_GREEN_BALANCE:
		err += zc0301_i2c_write(cam, 0x08, ctrl->value);
		break;
	case ZC0301_V4L2_CID_DAC_MAGNITUDE:
		err += zc0301_i2c_write(cam, 0x0c, ctrl->value);
		break;
	default:
		return -EINVAL;
	}
	err += zc0301_i2c_write(cam, 0x11, 0x01);

	return err ? -EIO : 0;
}