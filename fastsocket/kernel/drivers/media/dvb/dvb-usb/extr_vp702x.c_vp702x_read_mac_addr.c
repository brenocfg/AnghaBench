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
typedef  int u8 ;
struct dvb_usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_EEPROM_REQ ; 
 int /*<<< orphan*/  vp702x_usb_in_op (struct dvb_usb_device*,int /*<<< orphan*/ ,int,int,int*,int) ; 

__attribute__((used)) static int vp702x_read_mac_addr(struct dvb_usb_device *d,u8 mac[6])
{
	u8 i;
	for (i = 6; i < 12; i++)
		vp702x_usb_in_op(d, READ_EEPROM_REQ, i, 1, &mac[i - 6], 1);
	return 0;
}