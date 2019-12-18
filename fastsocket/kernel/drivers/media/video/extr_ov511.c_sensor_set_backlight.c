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
struct usb_ov511 {int sensor; int backlight; } ;

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
 int /*<<< orphan*/  i2c_w_mask (struct usb_ov511*,int,int,int) ; 

__attribute__((used)) static int
sensor_set_backlight(struct usb_ov511 *ov, int enable)
{
	PDEBUG(4, " (%s)", enable ? "turn on" : "turn off");

	switch (ov->sensor) {
	case SEN_OV7620:
	case SEN_OV8600:
		i2c_w_mask(ov, 0x68, enable?0xe0:0xc0, 0xe0);
		i2c_w_mask(ov, 0x29, enable?0x08:0x00, 0x08);
		i2c_w_mask(ov, 0x28, enable?0x02:0x00, 0x02);
		break;
	case SEN_OV6620:
		i2c_w_mask(ov, 0x4e, enable?0xe0:0xc0, 0xe0);
		i2c_w_mask(ov, 0x29, enable?0x08:0x00, 0x08);
		i2c_w_mask(ov, 0x0e, enable?0x80:0x00, 0x80);
		break;
	case SEN_OV6630:
		i2c_w_mask(ov, 0x4e, enable?0x80:0x60, 0xe0);
		i2c_w_mask(ov, 0x29, enable?0x08:0x00, 0x08);
		i2c_w_mask(ov, 0x28, enable?0x02:0x00, 0x02);
		break;
	case SEN_OV7610:
	case SEN_OV76BE:
	case SEN_KS0127:
	case SEN_KS0127B:
	case SEN_SAA7111A:
		PDEBUG(5, "Unsupported with this sensor");
		return -EPERM;
	default:
		err("Sensor not supported for set_backlight");
		return -EINVAL;
	}

	ov->backlight = enable;

	return 0;
}