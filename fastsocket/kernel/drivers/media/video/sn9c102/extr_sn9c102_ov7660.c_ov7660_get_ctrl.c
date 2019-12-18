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
 void* sn9c102_i2c_read (struct sn9c102_device*,int) ; 
 void* sn9c102_read_reg (struct sn9c102_device*,int) ; 

__attribute__((used)) static int ov7660_get_ctrl(struct sn9c102_device* cam,
			   struct v4l2_control* ctrl)
{
	int err = 0;

	switch (ctrl->id) {
	case V4L2_CID_EXPOSURE:
		if ((ctrl->value = sn9c102_i2c_read(cam, 0x10)) < 0)
			return -EIO;
		break;
	case V4L2_CID_DO_WHITE_BALANCE:
		if ((ctrl->value = sn9c102_read_reg(cam, 0x02)) < 0)
			return -EIO;
		ctrl->value = (ctrl->value & 0x04) ? 1 : 0;
		break;
	case V4L2_CID_RED_BALANCE:
		if ((ctrl->value = sn9c102_read_reg(cam, 0x05)) < 0)
			return -EIO;
		ctrl->value &= 0x7f;
		break;
	case V4L2_CID_BLUE_BALANCE:
		if ((ctrl->value = sn9c102_read_reg(cam, 0x06)) < 0)
			return -EIO;
		ctrl->value &= 0x7f;
		break;
	case SN9C102_V4L2_CID_GREEN_BALANCE:
		if ((ctrl->value = sn9c102_read_reg(cam, 0x07)) < 0)
			return -EIO;
		ctrl->value &= 0x7f;
		break;
	case SN9C102_V4L2_CID_BAND_FILTER:
		if ((ctrl->value = sn9c102_i2c_read(cam, 0x3b)) < 0)
			return -EIO;
		ctrl->value &= 0x08;
		break;
	case V4L2_CID_GAIN:
		if ((ctrl->value = sn9c102_i2c_read(cam, 0x00)) < 0)
			return -EIO;
		ctrl->value &= 0x1f;
		break;
	case V4L2_CID_AUTOGAIN:
		if ((ctrl->value = sn9c102_i2c_read(cam, 0x13)) < 0)
			return -EIO;
		ctrl->value &= 0x01;
		break;
	default:
		return -EINVAL;
	}

	return err ? -EIO : 0;
}