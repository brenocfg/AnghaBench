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
struct usb_ov511 {int sensor; unsigned char exposure; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  PDEBUG (int,char*,...) ; 
#define  SEN_KS0127 136 
#define  SEN_KS0127B 135 
#define  SEN_OV6620 134 
#define  SEN_OV6630 133 
#define  SEN_OV7610 132 
#define  SEN_OV7620 131 
#define  SEN_OV76BE 130 
#define  SEN_OV8600 129 
#define  SEN_SAA7111A 128 
 int /*<<< orphan*/  err (char*) ; 
 int i2c_r (struct usb_ov511*,int) ; 

__attribute__((used)) static int
sensor_get_exposure(struct usb_ov511 *ov, unsigned char *val)
{
	int rc;

	switch (ov->sensor) {
	case SEN_OV7610:
	case SEN_OV6620:
	case SEN_OV6630:
	case SEN_OV7620:
	case SEN_OV76BE:
	case SEN_OV8600:
		rc = i2c_r(ov, 0x10);
		if (rc < 0)
			return rc;
		else
			*val = rc;
		break;
	case SEN_KS0127:
	case SEN_KS0127B:
	case SEN_SAA7111A:
		val = NULL;
		PDEBUG(3, "Unsupported with this sensor");
		return -EPERM;
	default:
		err("Sensor not supported for get_exposure");
		return -EINVAL;
	}

	PDEBUG(3, "%d", *val);
	ov->exposure = *val;

	return 0;
}