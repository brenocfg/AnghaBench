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
typedef  int /*<<< orphan*/  u8 ;
struct dvb_usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SET_INIT ; 
 int /*<<< orphan*/  dvb_usb_generic_write (struct dvb_usb_device*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int dtt200u_power_ctrl(struct dvb_usb_device *d, int onoff)
{
	u8 b = SET_INIT;

	if (onoff)
		dvb_usb_generic_write(d,&b,2);

	return 0;
}