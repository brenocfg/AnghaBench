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
typedef  enum sn9c102_bridge { ____Placeholder_sn9c102_bridge } sn9c102_bridge ;

/* Variables and functions */
 int BRIDGE_SN9C105 ; 
 int BRIDGE_SN9C120 ; 
 int EINVAL ; 
 int EIO ; 
#define  SN9C102_V4L2_CID_BAND_FILTER 138 
#define  SN9C102_V4L2_CID_GAMMA 137 
#define  SN9C102_V4L2_CID_GREEN_BALANCE 136 
#define  V4L2_CID_AUTOGAIN 135 
#define  V4L2_CID_BLUE_BALANCE 134 
#define  V4L2_CID_DO_WHITE_BALANCE 133 
#define  V4L2_CID_EXPOSURE 132 
#define  V4L2_CID_GAIN 131 
#define  V4L2_CID_RED_BALANCE 130 
#define  V4L2_CID_VFLIP 129 
#define  V4L2_CID_WHITENESS 128 
 int sn9c102_get_bridge (struct sn9c102_device*) ; 
 int sn9c102_i2c_write (struct sn9c102_device*,int,int) ; 
 int sn9c102_write_reg (struct sn9c102_device*,int,int) ; 

__attribute__((used)) static int ov7630_set_ctrl(struct sn9c102_device* cam,
			   const struct v4l2_control* ctrl)
{
	enum sn9c102_bridge bridge = sn9c102_get_bridge(cam);
	int err = 0;

	switch (ctrl->id) {
	case V4L2_CID_EXPOSURE:
		err += sn9c102_i2c_write(cam, 0x10, ctrl->value);
		break;
	case V4L2_CID_RED_BALANCE:
		if (bridge == BRIDGE_SN9C105 || bridge == BRIDGE_SN9C120)
			err += sn9c102_write_reg(cam, ctrl->value, 0x05);
		else
			err += sn9c102_write_reg(cam, ctrl->value, 0x07);
		break;
	case V4L2_CID_BLUE_BALANCE:
		err += sn9c102_write_reg(cam, ctrl->value, 0x06);
		break;
	case SN9C102_V4L2_CID_GREEN_BALANCE:
		if (bridge == BRIDGE_SN9C105 || bridge == BRIDGE_SN9C120)
			err += sn9c102_write_reg(cam, ctrl->value, 0x07);
		else
			err += sn9c102_write_reg(cam, ctrl->value, 0x05);
		break;
	case V4L2_CID_GAIN:
		err += sn9c102_i2c_write(cam, 0x00, ctrl->value);
		break;
	case V4L2_CID_DO_WHITE_BALANCE:
		err += sn9c102_i2c_write(cam, 0x0c, ctrl->value);
		break;
	case V4L2_CID_WHITENESS:
		err += sn9c102_i2c_write(cam, 0x0d, ctrl->value);
		break;
	case V4L2_CID_AUTOGAIN:
		err += sn9c102_i2c_write(cam, 0x13, ctrl->value |
						    (ctrl->value << 1));
		break;
	case V4L2_CID_VFLIP:
		err += sn9c102_i2c_write(cam, 0x75, 0x0e | (ctrl->value << 7));
		break;
	case SN9C102_V4L2_CID_GAMMA:
		err += sn9c102_i2c_write(cam, 0x14, ctrl->value << 2);
		break;
	case SN9C102_V4L2_CID_BAND_FILTER:
		err += sn9c102_i2c_write(cam, 0x2d, ctrl->value << 2);
		break;
	default:
		return -EINVAL;
	}

	return err ? -EIO : 0;
}