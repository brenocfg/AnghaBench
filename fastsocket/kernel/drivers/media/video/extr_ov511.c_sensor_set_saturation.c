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
struct usb_ov511 {int sensor; unsigned short colour; scalar_t__ stop_during_set; } ;

/* Variables and functions */
 int EIO ; 
 int EPERM ; 
 int OV7610_REG_SAT ; 
 int /*<<< orphan*/  PDEBUG (int,char*,...) ; 
#define  SEN_OV6620 133 
#define  SEN_OV6630 132 
#define  SEN_OV7610 131 
#define  SEN_OV7620 130 
#define  SEN_OV76BE 129 
#define  SEN_SAA7111A 128 
 int i2c_w (struct usb_ov511*,int,unsigned short) ; 
 scalar_t__ ov51x_restart (struct usb_ov511*) ; 
 scalar_t__ ov51x_stop (struct usb_ov511*) ; 

__attribute__((used)) static int
sensor_set_saturation(struct usb_ov511 *ov, unsigned short val)
{
	int rc;

	PDEBUG(3, "%d", val);

	if (ov->stop_during_set)
		if (ov51x_stop(ov) < 0)
			return -EIO;

	switch (ov->sensor) {
	case SEN_OV7610:
	case SEN_OV76BE:
	case SEN_OV6620:
	case SEN_OV6630:
		rc = i2c_w(ov, OV7610_REG_SAT, val >> 8);
		if (rc < 0)
			goto out;
		break;
	case SEN_OV7620:
//		/* Use UV gamma control instead. Bits 0 & 7 are reserved. */
//		rc = ov_i2c_write(ov->dev, 0x62, (val >> 9) & 0x7e);
//		if (rc < 0)
//			goto out;
		rc = i2c_w(ov, OV7610_REG_SAT, val >> 8);
		if (rc < 0)
			goto out;
		break;
	case SEN_SAA7111A:
		rc = i2c_w(ov, 0x0c, val >> 9);
		if (rc < 0)
			goto out;
		break;
	default:
		PDEBUG(3, "Unsupported with this sensor");
		rc = -EPERM;
		goto out;
	}

	rc = 0;		/* Success */
	ov->colour = val;
out:
	if (ov51x_restart(ov) < 0)
		return -EIO;

	return rc;
}