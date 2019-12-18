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
 int OV511_I2C_RETRIES ; 
 int /*<<< orphan*/  PDEBUG (int,char*,unsigned char,int) ; 
 int /*<<< orphan*/  R511_I2C_CTL ; 
 int /*<<< orphan*/  R51x_I2C_DATA ; 
 int /*<<< orphan*/  R51x_I2C_SADDR_2 ; 
 int /*<<< orphan*/  err (char*) ; 
 int reg_r (struct usb_ov511*,int /*<<< orphan*/ ) ; 
 int reg_w (struct usb_ov511*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ov511_i2c_read_internal(struct usb_ov511 *ov, unsigned char reg)
{
	int rc, value, retries;

	/* Two byte write cycle */
	for (retries = OV511_I2C_RETRIES; ; ) {
		/* Select camera register */
		rc = reg_w(ov, R51x_I2C_SADDR_2, reg);
		if (rc < 0)
			return rc;

		/* Initiate 2-byte write cycle */
		rc = reg_w(ov, R511_I2C_CTL, 0x03);
		if (rc < 0)
			return rc;

		/* Retry until idle */
		do {
			rc = reg_r(ov, R511_I2C_CTL);
		} while (rc > 0 && ((rc & 1) == 0));
		if (rc < 0)
			return rc;

		if ((rc&2) == 0) /* Ack? */
			break;

		/* I2C abort */
		reg_w(ov, R511_I2C_CTL, 0x10);

		if (--retries < 0) {
			err("i2c write retries exhausted");
			return -1;
		}
	}

	/* Two byte read cycle */
	for (retries = OV511_I2C_RETRIES; ; ) {
		/* Initiate 2-byte read cycle */
		rc = reg_w(ov, R511_I2C_CTL, 0x05);
		if (rc < 0)
			return rc;

		/* Retry until idle */
		do {
			rc = reg_r(ov, R511_I2C_CTL);
		} while (rc > 0 && ((rc&1) == 0));
		if (rc < 0)
			return rc;

		if ((rc&2) == 0) /* Ack? */
			break;

		/* I2C abort */
		rc = reg_w(ov, R511_I2C_CTL, 0x10);
		if (rc < 0)
			return rc;

		if (--retries < 0) {
			err("i2c read retries exhausted");
			return -1;
		}
	}

	value = reg_r(ov, R51x_I2C_DATA);

	PDEBUG(5, "0x%02X:0x%02X", reg, value);

	/* This is needed to make i2c_w() work */
	rc = reg_w(ov, R511_I2C_CTL, 0x05);
	if (rc < 0)
		return rc;

	return value;
}