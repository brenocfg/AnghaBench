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
struct usb_serial {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int USB_DIR_IN ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_VENDOR ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int keyspan_pda_get_modem_info(struct usb_serial *serial,
				      unsigned char *value)
{
	int rc;
	unsigned char data;
	rc = usb_control_msg(serial->dev, usb_rcvctrlpipe(serial->dev, 0),
			     3, /* get pins */
			     USB_TYPE_VENDOR|USB_RECIP_INTERFACE|USB_DIR_IN,
			     0, 0, &data, 1, 2000);
	if (rc >= 0)
		*value = data;
	return rc;
}