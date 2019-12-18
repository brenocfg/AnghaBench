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
struct usb_ov511 {int sensor; unsigned short contrast; } ;

/* Variables and functions */
 int EPERM ; 
 int OV7610_REG_CNT ; 
 int /*<<< orphan*/  PDEBUG (int,char*,...) ; 
#define  SEN_OV6620 132 
#define  SEN_OV6630 131 
#define  SEN_OV7610 130 
#define  SEN_OV7620 129 
#define  SEN_SAA7111A 128 
 int i2c_r (struct usb_ov511*,int) ; 

__attribute__((used)) static int
sensor_get_contrast(struct usb_ov511 *ov, unsigned short *val)
{
	int rc;

	switch (ov->sensor) {
	case SEN_OV7610:
	case SEN_OV6620:
		rc = i2c_r(ov, OV7610_REG_CNT);
		if (rc < 0)
			return rc;
		else
			*val = rc << 8;
		break;
	case SEN_OV6630:
		rc = i2c_r(ov, OV7610_REG_CNT);
		if (rc < 0)
			return rc;
		else
			*val = rc << 12;
		break;
	case SEN_OV7620:
		/* Use Y gamma reg instead. Bit 0 is the enable bit. */
		rc = i2c_r(ov, 0x64);
		if (rc < 0)
			return rc;
		else
			*val = (rc & 0xfe) << 8;
		break;
	case SEN_SAA7111A:
		*val = ov->contrast;
		break;
	default:
		PDEBUG(3, "Unsupported with this sensor");
		return -EPERM;
	}

	PDEBUG(3, "%d", *val);
	ov->contrast = *val;

	return 0;
}