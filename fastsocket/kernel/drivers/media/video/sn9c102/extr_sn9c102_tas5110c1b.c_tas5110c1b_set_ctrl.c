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
struct v4l2_control {int id; int /*<<< orphan*/  value; } ;
struct sn9c102_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
#define  V4L2_CID_GAIN 128 
 int sn9c102_i2c_write (struct sn9c102_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tas5110c1b_set_ctrl(struct sn9c102_device* cam,
			       const struct v4l2_control* ctrl)
{
	int err = 0;

	switch (ctrl->id) {
	case V4L2_CID_GAIN:
		err += sn9c102_i2c_write(cam, 0x20, 0xf6 - ctrl->value);
		break;
	default:
		return -EINVAL;
	}

	return err ? -EIO : 0;
}