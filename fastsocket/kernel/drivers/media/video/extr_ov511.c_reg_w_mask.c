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
 int reg_r (struct usb_ov511*,unsigned char) ; 
 int reg_w (struct usb_ov511*,unsigned char,unsigned char) ; 

__attribute__((used)) static int
reg_w_mask(struct usb_ov511 *ov,
	   unsigned char reg,
	   unsigned char value,
	   unsigned char mask)
{
	int ret;
	unsigned char oldval, newval;

	ret = reg_r(ov, reg);
	if (ret < 0)
		return ret;

	oldval = (unsigned char) ret;
	oldval &= (~mask);		/* Clear the masked bits */
	value &= mask;			/* Enforce mask on value */
	newval = oldval | value;	/* Set the desired bits */

	return (reg_w(ov, reg, newval));
}