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
#define  SN9C102_V4L2_CID_BAND_FILTER 135 
#define  SN9C102_V4L2_CID_GREEN_BALANCE 134 
#define  V4L2_CID_AUTOGAIN 133 
#define  V4L2_CID_BLUE_BALANCE 132 
#define  V4L2_CID_DO_WHITE_BALANCE 131 
#define  V4L2_CID_EXPOSURE 130 
#define  V4L2_CID_GAIN 129 
#define  V4L2_CID_RED_BALANCE 128 
 int sn9c102_i2c_write (struct sn9c102_device*,int,int) ; 
 int sn9c102_write_reg (struct sn9c102_device*,int,int) ; 

__attribute__((used)) static int ov7660_set_ctrl(struct sn9c102_device* cam,
			   const struct v4l2_control* ctrl)
{
	int err = 0;

	switch (ctrl->id) {
	case V4L2_CID_EXPOSURE:
		err += sn9c102_i2c_write(cam, 0x10, ctrl->value);
		break;
	case V4L2_CID_DO_WHITE_BALANCE:
		err += sn9c102_write_reg(cam, 0x43 | (ctrl->value << 2), 0x02);
		break;
	case V4L2_CID_RED_BALANCE:
		err += sn9c102_write_reg(cam, ctrl->value, 0x05);
		break;
	case V4L2_CID_BLUE_BALANCE:
		err += sn9c102_write_reg(cam, ctrl->value, 0x06);
		break;
	case SN9C102_V4L2_CID_GREEN_BALANCE:
		err += sn9c102_write_reg(cam, ctrl->value, 0x07);
		break;
	case SN9C102_V4L2_CID_BAND_FILTER:
		err += sn9c102_i2c_write(cam, ctrl->value << 3, 0x3b);
		break;
	case V4L2_CID_GAIN:
		err += sn9c102_i2c_write(cam, 0x00, 0x60 + ctrl->value);
		break;
	case V4L2_CID_AUTOGAIN:
		err += sn9c102_i2c_write(cam, 0x13, 0xc0 |
						    (ctrl->value * 0x07));
		break;
	default:
		return -EINVAL;
	}

	return err ? -EIO : 0;
}