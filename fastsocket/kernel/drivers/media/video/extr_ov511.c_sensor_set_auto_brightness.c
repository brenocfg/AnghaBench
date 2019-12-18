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
struct usb_ov511 {scalar_t__ sensor; int auto_brt; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  PDEBUG (int,char*,...) ; 
 scalar_t__ SEN_KS0127 ; 
 scalar_t__ SEN_KS0127B ; 
 scalar_t__ SEN_SAA7111A ; 
 int i2c_w_mask (struct usb_ov511*,int,int,int) ; 

__attribute__((used)) static int
sensor_set_auto_brightness(struct usb_ov511 *ov, int enable)
{
	int rc;

	PDEBUG(4, " (%s)", enable ? "turn on" : "turn off");

	if (ov->sensor == SEN_KS0127 || ov->sensor == SEN_KS0127B
		|| ov->sensor == SEN_SAA7111A) {
		PDEBUG(5, "Unsupported with this sensor");
		return -EPERM;
	}

	rc = i2c_w_mask(ov, 0x2d, enable?0x10:0x00, 0x10);
	if (rc < 0)
		return rc;

	ov->auto_brt = enable;

	return 0;
}