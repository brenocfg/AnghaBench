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
struct dvb_usb_device {int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_CTRL_GET_TIMEOUT ; 
 int USB_DIR_OUT ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  deb_data (char*,...) ; 
 int /*<<< orphan*/  debug_dump (int*,int,int /*<<< orphan*/  (*) (char*,int,int)) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dib0700_ctrl_wr(struct dvb_usb_device *d, u8 *tx, u8 txlen)
{
	int status;

	deb_data(">>> ");
	debug_dump(tx, txlen, deb_data);

	status = usb_control_msg(d->udev, usb_sndctrlpipe(d->udev,0),
		tx[0], USB_TYPE_VENDOR | USB_DIR_OUT, 0, 0, tx, txlen,
		USB_CTRL_GET_TIMEOUT);

	if (status != txlen)
		deb_data("ep 0 write error (status = %d, len: %d)\n",status,txlen);

	return status < 0 ? status : 0;
}