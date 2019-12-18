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
 int /*<<< orphan*/  PDEBUG (int,char*,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  R511_I2C_CTL ; 
 int /*<<< orphan*/  R51x_I2C_DATA ; 
 int /*<<< orphan*/  R51x_I2C_SADDR_3 ; 
 int /*<<< orphan*/  err (char*) ; 
 int reg_r (struct usb_ov511*,int /*<<< orphan*/ ) ; 
 int reg_w (struct usb_ov511*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ov511_i2c_write_internal(struct usb_ov511 *ov,
			 unsigned char reg,
			 unsigned char value)
{
	int rc, retries;

	PDEBUG(5, "0x%02X:0x%02X", reg, value);

	/* Three byte write cycle */
	for (retries = OV511_I2C_RETRIES; ; ) {
		/* Select camera register */
		rc = reg_w(ov, R51x_I2C_SADDR_3, reg);
		if (rc < 0)
			break;

		/* Write "value" to I2C data port of OV511 */
		rc = reg_w(ov, R51x_I2C_DATA, value);
		if (rc < 0)
			break;

		/* Initiate 3-byte write cycle */
		rc = reg_w(ov, R511_I2C_CTL, 0x01);
		if (rc < 0)
			break;

		/* Retry until idle */
		do {
			rc = reg_r(ov, R511_I2C_CTL);
		} while (rc > 0 && ((rc&1) == 0));
		if (rc < 0)
			break;

		/* Ack? */
		if ((rc&2) == 0) {
			rc = 0;
			break;
		}
#if 0
		/* I2C abort */
		reg_w(ov, R511_I2C_CTL, 0x10);
#endif
		if (--retries < 0) {
			err("i2c write retries exhausted");
			rc = -1;
			break;
		}
	}

	return rc;
}