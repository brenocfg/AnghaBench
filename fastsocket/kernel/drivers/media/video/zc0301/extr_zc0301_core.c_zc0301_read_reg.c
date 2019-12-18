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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct zc0301_device {scalar_t__* control_buffer; struct usb_device* usbdev; } ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PDBGG (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ZC0301_CTRL_TIMEOUT ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,scalar_t__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

int zc0301_read_reg(struct zc0301_device* cam, u16 index)
{
	struct usb_device* udev = cam->usbdev;
	u8* buff = cam->control_buffer;
	int res;

	res = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0), 0xa1, 0xc0,
			      0x0001, index, buff, 1, ZC0301_CTRL_TIMEOUT);
	if (res < 0)
		DBG(3, "Failed to read a register (index 0x%04X, error %d)",
		    index, res);

	PDBGG("Read: index 0x%04X, value: 0x%04X", index, (int)(*buff));

	return (res >= 0) ? (int)(*buff) : -1;
}