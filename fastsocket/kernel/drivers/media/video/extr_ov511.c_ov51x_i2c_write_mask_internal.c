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
struct usb_ov511 {scalar_t__ bclass; } ;

/* Variables and functions */
 scalar_t__ BCL_OV518 ; 
 int ov511_i2c_read_internal (struct usb_ov511*,unsigned char) ; 
 int ov511_i2c_write_internal (struct usb_ov511*,unsigned char,unsigned char) ; 
 int ov518_i2c_read_internal (struct usb_ov511*,unsigned char) ; 
 int ov518_i2c_write_internal (struct usb_ov511*,unsigned char,unsigned char) ; 

__attribute__((used)) static int
ov51x_i2c_write_mask_internal(struct usb_ov511 *ov,
			      unsigned char reg,
			      unsigned char value,
			      unsigned char mask)
{
	int rc;
	unsigned char oldval, newval;

	if (mask == 0xff) {
		newval = value;
	} else {
		if (ov->bclass == BCL_OV518)
			rc = ov518_i2c_read_internal(ov, reg);
		else
			rc = ov511_i2c_read_internal(ov, reg);
		if (rc < 0)
			return rc;

		oldval = (unsigned char) rc;
		oldval &= (~mask);		/* Clear the masked bits */
		value &= mask;			/* Enforce mask on value */
		newval = oldval | value;	/* Set the desired bits */
	}

	if (ov->bclass == BCL_OV518)
		return (ov518_i2c_write_internal(ov, reg, newval));
	else
		return (ov511_i2c_write_internal(ov, reg, newval));
}