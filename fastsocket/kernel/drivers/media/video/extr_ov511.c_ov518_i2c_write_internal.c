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
 int /*<<< orphan*/  PDEBUG (int,char*,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  R518_I2C_CTL ; 
 int /*<<< orphan*/  R51x_I2C_DATA ; 
 int /*<<< orphan*/  R51x_I2C_SADDR_3 ; 
 int reg_w (struct usb_ov511*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ov518_i2c_write_internal(struct usb_ov511 *ov,
			 unsigned char reg,
			 unsigned char value)
{
	int rc;

	PDEBUG(5, "0x%02X:0x%02X", reg, value);

	/* Select camera register */
	rc = reg_w(ov, R51x_I2C_SADDR_3, reg);
	if (rc < 0)
		return rc;

	/* Write "value" to I2C data port of OV511 */
	rc = reg_w(ov, R51x_I2C_DATA, value);
	if (rc < 0)
		return rc;

	/* Initiate 3-byte write cycle */
	rc = reg_w(ov, R518_I2C_CTL, 0x01);
	if (rc < 0)
		return rc;

	return 0;
}