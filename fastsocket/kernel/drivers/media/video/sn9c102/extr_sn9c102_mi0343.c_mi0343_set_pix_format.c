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
struct v4l2_pix_format {scalar_t__ pixelformat; } ;
struct sn9c102_sensor {int /*<<< orphan*/  i2c_slave_id; } ;
struct sn9c102_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ V4L2_PIX_FMT_SN9C10X ; 
 struct sn9c102_sensor* sn9c102_get_sensor (struct sn9c102_device*) ; 
 scalar_t__ sn9c102_i2c_try_raw_write (struct sn9c102_device*,struct sn9c102_sensor*,int,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sn9c102_write_reg (struct sn9c102_device*,int,int) ; 

__attribute__((used)) static int mi0343_set_pix_format(struct sn9c102_device* cam,
				 const struct v4l2_pix_format* pix)
{
	struct sn9c102_sensor* s = sn9c102_get_sensor(cam);
	int err = 0;

	if (pix->pixelformat == V4L2_PIX_FMT_SN9C10X) {
		err += sn9c102_i2c_try_raw_write(cam, s, 4, s->i2c_slave_id,
						 0x0a, 0x00, 0x03, 0, 0);
		err += sn9c102_write_reg(cam, 0x20, 0x19);
	} else {
		err += sn9c102_i2c_try_raw_write(cam, s, 4, s->i2c_slave_id,
						 0x0a, 0x00, 0x05, 0, 0);
		err += sn9c102_write_reg(cam, 0xa0, 0x19);
	}

	return err;
}