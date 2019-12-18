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
 void* zc0301_i2c_read (struct zc0301_device*,int,int) ; 

__attribute__((used)) static int pas202bcb_get_ctrl(struct zc0301_device* cam,
			      struct v4l2_control* ctrl)
{
	switch (ctrl->id) {
	case V4L2_CID_EXPOSURE:
		{
			int r1 = zc0301_i2c_read(cam, 0x04, 1),
			    r2 = zc0301_i2c_read(cam, 0x05, 1);
			if (r1 < 0 || r2 < 0)
				return -EIO;
			ctrl->value = (r1 << 6) | (r2 & 0x3f);
		}
		return 0;
	case V4L2_CID_RED_BALANCE:
		if ((ctrl->value = zc0301_i2c_read(cam, 0x09, 1)) < 0)
			return -EIO;
		ctrl->value &= 0x0f;
		return 0;
	case V4L2_CID_BLUE_BALANCE:
		if ((ctrl->value = zc0301_i2c_read(cam, 0x07, 1)) < 0)
			return -EIO;
		ctrl->value &= 0x0f;
		return 0;
	case V4L2_CID_GAIN:
		if ((ctrl->value = zc0301_i2c_read(cam, 0x10, 1)) < 0)
			return -EIO;
		ctrl->value &= 0x1f;
		return 0;
	case ZC0301_V4L2_CID_GREEN_BALANCE:
		if ((ctrl->value = zc0301_i2c_read(cam, 0x08, 1)) < 0)
			return -EIO;
		ctrl->value &= 0x0f;
		return 0;
	case ZC0301_V4L2_CID_DAC_MAGNITUDE:
		if ((ctrl->value = zc0301_i2c_read(cam, 0x0c, 1)) < 0)
			return -EIO;
		return 0;
	default:
		return -EINVAL;
	}
}