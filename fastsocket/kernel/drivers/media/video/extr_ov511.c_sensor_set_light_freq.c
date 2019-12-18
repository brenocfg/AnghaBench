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
struct usb_ov511 {int sensor; int lightfreq; } ;

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
 int /*<<< orphan*/  err (char*,...) ; 
 int /*<<< orphan*/  i2c_w (struct usb_ov511*,int,int) ; 
 int /*<<< orphan*/  i2c_w_mask (struct usb_ov511*,int,int,int) ; 

__attribute__((used)) static int
sensor_set_light_freq(struct usb_ov511 *ov, int freq)
{
	int sixty;

	PDEBUG(4, "%d Hz", freq);

	if (freq == 60)
		sixty = 1;
	else if (freq == 50)
		sixty = 0;
	else {
		err("Invalid light freq (%d Hz)", freq);
		return -EINVAL;
	}

	switch (ov->sensor) {
	case SEN_OV7610:
		i2c_w_mask(ov, 0x2a, sixty?0x00:0x80, 0x80);
		i2c_w(ov, 0x2b, sixty?0x00:0xac);
		i2c_w_mask(ov, 0x13, 0x10, 0x10);
		i2c_w_mask(ov, 0x13, 0x00, 0x10);
		break;
	case SEN_OV7620:
	case SEN_OV76BE:
	case SEN_OV8600:
		i2c_w_mask(ov, 0x2a, sixty?0x00:0x80, 0x80);
		i2c_w(ov, 0x2b, sixty?0x00:0xac);
		i2c_w_mask(ov, 0x76, 0x01, 0x01);
		break;
	case SEN_OV6620:
	case SEN_OV6630:
		i2c_w(ov, 0x2b, sixty?0xa8:0x28);
		i2c_w(ov, 0x2a, sixty?0x84:0xa4);
		break;
	case SEN_KS0127:
	case SEN_KS0127B:
	case SEN_SAA7111A:
		PDEBUG(5, "Unsupported with this sensor");
		return -EPERM;
	default:
		err("Sensor not supported for set_light_freq");
		return -EINVAL;
	}

	ov->lightfreq = freq;

	return 0;
}