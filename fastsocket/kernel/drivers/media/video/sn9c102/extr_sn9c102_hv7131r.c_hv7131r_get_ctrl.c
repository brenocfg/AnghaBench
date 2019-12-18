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
 void* sn9c102_i2c_read (struct sn9c102_device*,int) ; 

__attribute__((used)) static int hv7131r_get_ctrl(struct sn9c102_device* cam,
			    struct v4l2_control* ctrl)
{
	switch (ctrl->id) {
	case V4L2_CID_GAIN:
		if ((ctrl->value = sn9c102_i2c_read(cam, 0x30)) < 0)
			return -EIO;
		return 0;
	case V4L2_CID_RED_BALANCE:
		if ((ctrl->value = sn9c102_i2c_read(cam, 0x31)) < 0)
			return -EIO;
		ctrl->value = ctrl->value & 0x3f;
		return 0;
	case V4L2_CID_BLUE_BALANCE:
		if ((ctrl->value = sn9c102_i2c_read(cam, 0x33)) < 0)
			return -EIO;
		ctrl->value = ctrl->value & 0x3f;
		return 0;
	case SN9C102_V4L2_CID_GREEN_BALANCE:
		if ((ctrl->value = sn9c102_i2c_read(cam, 0x32)) < 0)
			return -EIO;
		ctrl->value = ctrl->value & 0x3f;
		return 0;
	case V4L2_CID_BLACK_LEVEL:
		if ((ctrl->value = sn9c102_i2c_read(cam, 0x01)) < 0)
			return -EIO;
		ctrl->value = (ctrl->value & 0x08) ? 1 : 0;
		return 0;
	default:
		return -EINVAL;
	}
}