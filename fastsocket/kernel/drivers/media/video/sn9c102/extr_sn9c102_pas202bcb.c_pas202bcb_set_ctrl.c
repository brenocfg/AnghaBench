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
#define  SN9C102_V4L2_CID_DAC_MAGNITUDE 133 
#define  SN9C102_V4L2_CID_GREEN_BALANCE 132 
#define  V4L2_CID_BLUE_BALANCE 131 
#define  V4L2_CID_EXPOSURE 130 
#define  V4L2_CID_GAIN 129 
#define  V4L2_CID_RED_BALANCE 128 
 scalar_t__ sn9c102_i2c_write (struct sn9c102_device*,int,int) ; 

__attribute__((used)) static int pas202bcb_set_ctrl(struct sn9c102_device* cam,
			      const struct v4l2_control* ctrl)
{
	int err = 0;

	switch (ctrl->id) {
	case V4L2_CID_EXPOSURE:
		err += sn9c102_i2c_write(cam, 0x04, ctrl->value >> 6);
		err += sn9c102_i2c_write(cam, 0x05, ctrl->value & 0x3f);
		break;
	case V4L2_CID_RED_BALANCE:
		err += sn9c102_i2c_write(cam, 0x09, ctrl->value);
		break;
	case V4L2_CID_BLUE_BALANCE:
		err += sn9c102_i2c_write(cam, 0x07, ctrl->value);
		break;
	case V4L2_CID_GAIN:
		err += sn9c102_i2c_write(cam, 0x10, ctrl->value);
		break;
	case SN9C102_V4L2_CID_GREEN_BALANCE:
		err += sn9c102_i2c_write(cam, 0x08, ctrl->value);
		break;
	case SN9C102_V4L2_CID_DAC_MAGNITUDE:
		err += sn9c102_i2c_write(cam, 0x0c, ctrl->value);
		break;
	default:
		return -EINVAL;
	}
	err += sn9c102_i2c_write(cam, 0x11, 0x01);

	return err ? -EIO : 0;
}