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
typedef  int speed_t ;

/* Variables and functions */
 int USB_DIR_OUT ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_VENDOR ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static speed_t keyspan_pda_setbaud(struct usb_serial *serial, speed_t baud)
{
	int rc;
	int bindex;

	switch (baud) {
	case 110:
		bindex = 0;
		break;
	case 300:
		bindex = 1;
		break;
	case 1200:
		bindex = 2;
		break;
	case 2400:
		bindex = 3;
		break;
	case 4800:
		bindex = 4;
		break;
	case 9600:
		bindex = 5;
		break;
	case 19200:
		bindex = 6;
		break;
	case 38400:
		bindex = 7;
		break;
	case 57600:
		bindex = 8;
		break;
	case 115200:
		bindex = 9;
		break;
	default:
		bindex = 5;	/* Default to 9600 */
		baud = 9600;
	}

	/* rather than figure out how to sleep while waiting for this
	   to complete, I just use the "legacy" API. */
	rc = usb_control_msg(serial->dev, usb_sndctrlpipe(serial->dev, 0),
			     0, /* set baud */
			     USB_TYPE_VENDOR
			     | USB_RECIP_INTERFACE
			     | USB_DIR_OUT, /* type */
			     bindex, /* value */
			     0, /* index */
			     NULL, /* &data */
			     0, /* size */
			     2000); /* timeout */
	if (rc < 0)
		return 0;
	return baud;
}