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
struct sn9c102_sensor {int /*<<< orphan*/  i2c_slave_id; } ;
struct sn9c102_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
#define  V4L2_CID_VFLIP 128 
 struct sn9c102_sensor* sn9c102_get_sensor (struct sn9c102_device*) ; 
 int sn9c102_i2c_try_raw_write (struct sn9c102_device*,struct sn9c102_sensor*,int,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt9v111_set_ctrl(struct sn9c102_device *cam,
			    const struct v4l2_control *ctrl)
{
	struct sn9c102_sensor *s = sn9c102_get_sensor(cam);
	int err = 0;

	switch (ctrl->id) {
	case V4L2_CID_VFLIP:
		err += sn9c102_i2c_try_raw_write(cam, s, 4, s->i2c_slave_id,
						 0x20,
						 ctrl->value ? 0x80 : 0x00,
						 ctrl->value ? 0x80 : 0x00, 0,
						 0);
		break;
	default:
		return -EINVAL;
	}

	return err ? -EIO : 0;
}