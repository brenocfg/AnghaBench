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
struct et61x251_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
#define  V4L2_CID_EXPOSURE 129 
#define  V4L2_CID_GAIN 128 
 int et61x251_i2c_raw_write (struct et61x251_device*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tas5130d1b_set_ctrl(struct et61x251_device* cam,
			       const struct v4l2_control* ctrl)
{
	int err = 0;

	switch (ctrl->id) {
	case V4L2_CID_GAIN:
		err += et61x251_i2c_raw_write(cam, 2, 0x20,
					      0xf6-ctrl->value, 0, 0, 0,
					      0, 0, 0, 0);
		break;
	case V4L2_CID_EXPOSURE:
		err += et61x251_i2c_raw_write(cam, 2, 0x40,
					      0x47-ctrl->value, 0, 0, 0,
					      0, 0, 0, 0);
		break;
	default:
		return -EINVAL;
	}

	return err ? -EIO : 0;
}