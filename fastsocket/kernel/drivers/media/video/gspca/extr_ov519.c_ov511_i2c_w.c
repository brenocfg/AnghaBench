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
typedef  int u8 ;
struct sd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_USBO ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  R511_I2C_CTL ; 
 int /*<<< orphan*/  R51x_I2C_DATA ; 
 int /*<<< orphan*/  R51x_I2C_SADDR_3 ; 
 int reg_r (struct sd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_w (struct sd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ov511_i2c_w(struct sd *sd, u8 reg, u8 value)
{
	int rc, retries;

	PDEBUG(D_USBO, "ov511_i2c_w %02x %02x", reg, value);

	/* Three byte write cycle */
	for (retries = 6; ; ) {
		/* Select camera register */
		reg_w(sd, R51x_I2C_SADDR_3, reg);

		/* Write "value" to I2C data port of OV511 */
		reg_w(sd, R51x_I2C_DATA, value);

		/* Initiate 3-byte write cycle */
		reg_w(sd, R511_I2C_CTL, 0x01);

		do {
			rc = reg_r(sd, R511_I2C_CTL);
		} while (rc > 0 && ((rc & 1) == 0)); /* Retry until idle */

		if (rc < 0)
			return;

		if ((rc & 2) == 0) /* Ack? */
			break;
		if (--retries < 0) {
			PDEBUG(D_USBO, "i2c write retries exhausted");
			return;
		}
	}
}