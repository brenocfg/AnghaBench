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
struct usb_ov511 {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int OV7610_REG_ID_HIGH ; 
 int OV7610_REG_ID_LOW ; 
 int /*<<< orphan*/  PDEBUG (int,char*,int) ; 
 int i2c_detect_tries ; 
 scalar_t__ i2c_r (struct usb_ov511*,int) ; 
 scalar_t__ i2c_w (struct usb_ov511*,int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int
init_ov_sensor(struct usb_ov511 *ov)
{
	int i, success;

	/* Reset the sensor */
	if (i2c_w(ov, 0x12, 0x80) < 0)
		return -EIO;

	/* Wait for it to initialize */
	msleep(150);

	for (i = 0, success = 0; i < i2c_detect_tries && !success; i++) {
		if ((i2c_r(ov, OV7610_REG_ID_HIGH) == 0x7F) &&
		    (i2c_r(ov, OV7610_REG_ID_LOW) == 0xA2)) {
			success = 1;
			continue;
		}

		/* Reset the sensor */
		if (i2c_w(ov, 0x12, 0x80) < 0)
			return -EIO;
		/* Wait for it to initialize */
		msleep(150);
		/* Dummy read to sync I2C */
		if (i2c_r(ov, 0x00) < 0)
			return -EIO;
	}

	if (!success)
		return -EIO;

	PDEBUG(1, "I2C synced in %d attempt(s)", i);

	return 0;
}