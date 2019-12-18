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
struct dvb_usb_device {int dummy; } ;

/* Variables and functions */
 int anysee_ir_ctrl (struct dvb_usb_device*,int) ; 
 int anysee_led_ctrl (struct dvb_usb_device*,int,int) ; 

__attribute__((used)) static int anysee_init(struct dvb_usb_device *d)
{
	int ret;
	/* LED light */
	ret = anysee_led_ctrl(d, 0x01, 0x03);
	if (ret)
		return ret;

	/* enable IR */
	ret = anysee_ir_ctrl(d, 1);
	if (ret)
		return ret;

	return 0;
}