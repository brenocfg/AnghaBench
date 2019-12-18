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
struct usb_ov511 {int sensor; unsigned short contrast; scalar_t__ stop_during_set; } ;

/* Variables and functions */
 int EIO ; 
 int EPERM ; 
 int OV7610_REG_CNT ; 
 int /*<<< orphan*/  PDEBUG (int,char*,...) ; 
#define  SEN_OV6620 132 
#define  SEN_OV6630 131 
#define  SEN_OV7610 130 
#define  SEN_OV7620 129 
#define  SEN_SAA7111A 128 
 int i2c_w (struct usb_ov511*,int,unsigned short) ; 
 int i2c_w_mask (struct usb_ov511*,int,unsigned short,int) ; 
 scalar_t__ ov51x_restart (struct usb_ov511*) ; 
 scalar_t__ ov51x_stop (struct usb_ov511*) ; 

__attribute__((used)) static int
sensor_set_contrast(struct usb_ov511 *ov, unsigned short val)
{
	int rc;

	PDEBUG(3, "%d", val);

	if (ov->stop_during_set)
		if (ov51x_stop(ov) < 0)
			return -EIO;

	switch (ov->sensor) {
	case SEN_OV7610:
	case SEN_OV6620:
	{
		rc = i2c_w(ov, OV7610_REG_CNT, val >> 8);
		if (rc < 0)
			goto out;
		break;
	}
	case SEN_OV6630:
	{
		rc = i2c_w_mask(ov, OV7610_REG_CNT, val >> 12, 0x0f);
		if (rc < 0)
			goto out;
		break;
	}
	case SEN_OV7620:
	{
		unsigned char ctab[] = {
			0x01, 0x05, 0x09, 0x11, 0x15, 0x35, 0x37, 0x57,
			0x5b, 0xa5, 0xa7, 0xc7, 0xc9, 0xcf, 0xef, 0xff
		};

		/* Use Y gamma control instead. Bit 0 enables it. */
		rc = i2c_w(ov, 0x64, ctab[val>>12]);
		if (rc < 0)
			goto out;
		break;
	}
	case SEN_SAA7111A:
	{
		rc = i2c_w(ov, 0x0b, val >> 9);
		if (rc < 0)
			goto out;
		break;
	}
	default:
	{
		PDEBUG(3, "Unsupported with this sensor");
		rc = -EPERM;
		goto out;
	}
	}

	rc = 0;		/* Success */
	ov->contrast = val;
out:
	if (ov51x_restart(ov) < 0)
		return -EIO;

	return rc;
}