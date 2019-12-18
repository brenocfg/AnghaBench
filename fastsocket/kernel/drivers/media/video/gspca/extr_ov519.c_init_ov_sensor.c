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
typedef  int /*<<< orphan*/  u8 ;
struct sd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_PROBE ; 
 int OV7610_REG_ID_HIGH ; 
 int OV7610_REG_ID_LOW ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int) ; 
 int i2c_detect_tries ; 
 scalar_t__ i2c_r (struct sd*,int) ; 
 int /*<<< orphan*/  i2c_w (struct sd*,int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  ov51x_set_slave_ids (struct sd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_ov_sensor(struct sd *sd, u8 slave)
{
	int i;

	ov51x_set_slave_ids(sd, slave);

	/* Reset the sensor */
	i2c_w(sd, 0x12, 0x80);

	/* Wait for it to initialize */
	msleep(150);

	for (i = 0; i < i2c_detect_tries; i++) {
		if (i2c_r(sd, OV7610_REG_ID_HIGH) == 0x7f &&
		    i2c_r(sd, OV7610_REG_ID_LOW) == 0xa2) {
			PDEBUG(D_PROBE, "I2C synced in %d attempt(s)", i);
			return 0;
		}

		/* Reset the sensor */
		i2c_w(sd, 0x12, 0x80);

		/* Wait for it to initialize */
		msleep(150);

		/* Dummy read to sync I2C */
		if (i2c_r(sd, 0x00) < 0)
			return -1;
	}
	return -1;
}