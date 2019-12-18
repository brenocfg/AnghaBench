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
struct et61x251_sensor {scalar_t__ interface; } ;
struct et61x251_device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 scalar_t__ ET61X251_I2C_3WIRES ; 
 int et61x251_read_reg (struct et61x251_device*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
et61x251_i2c_wait(struct et61x251_device* cam,
		  const struct et61x251_sensor* sensor)
{
	int i, r;

	for (i = 1; i <= 8; i++) {
		if (sensor->interface == ET61X251_I2C_3WIRES) {
			r = et61x251_read_reg(cam, 0x8e);
			if (!(r & 0x02) && (r >= 0))
				return 0;
		} else {
			r = et61x251_read_reg(cam, 0x8b);
			if (!(r & 0x01) && (r >= 0))
				return 0;
		}
		if (r < 0)
			return -EIO;
		udelay(8*8); /* minimum for sensors at 400kHz */
	}

	return -EBUSY;
}