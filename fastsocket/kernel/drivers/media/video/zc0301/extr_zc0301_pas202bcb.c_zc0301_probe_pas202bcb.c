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

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pas202bcb ; 
 int /*<<< orphan*/  zc0301_attach_sensor (struct zc0301_device*,int /*<<< orphan*/ *) ; 
 int zc0301_i2c_read (struct zc0301_device*,int,int) ; 
 scalar_t__ zc0301_write_reg (struct zc0301_device*,int,int) ; 

int zc0301_probe_pas202bcb(struct zc0301_device* cam)
{
	int r0 = 0, r1 = 0, err = 0;
	unsigned int pid = 0;

	err += zc0301_write_reg(cam, 0x0000, 0x01);
	err += zc0301_write_reg(cam, 0x0010, 0x0e);
	err += zc0301_write_reg(cam, 0x0001, 0x01);
	err += zc0301_write_reg(cam, 0x0012, 0x03);
	err += zc0301_write_reg(cam, 0x0012, 0x01);
	err += zc0301_write_reg(cam, 0x008d, 0x08);

	msleep(10);

	r0 = zc0301_i2c_read(cam, 0x00, 1);
	r1 = zc0301_i2c_read(cam, 0x01, 1);

	if (r0 < 0 || r1 < 0 || err)
		return -EIO;

	pid = (r0 << 4) | ((r1 & 0xf0) >> 4);
	if (pid != 0x017)
		return -ENODEV;

	zc0301_attach_sensor(cam, &pas202bcb);

	return 0;
}