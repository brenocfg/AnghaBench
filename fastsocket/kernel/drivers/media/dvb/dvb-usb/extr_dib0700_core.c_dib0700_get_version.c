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
typedef  int u32 ;
struct dvb_usb_device {int /*<<< orphan*/  udev; } ;
typedef  int /*<<< orphan*/  b ;

/* Variables and functions */
 int /*<<< orphan*/  REQUEST_GET_VERSION ; 
 int /*<<< orphan*/  USB_CTRL_GET_TIMEOUT ; 
 int USB_DIR_IN ; 
 int USB_TYPE_VENDOR ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int dib0700_get_version(struct dvb_usb_device *d, u32 *hwversion,
			u32 *romversion, u32 *ramversion, u32 *fwtype)
{
	u8 b[16];
	int ret = usb_control_msg(d->udev, usb_rcvctrlpipe(d->udev, 0),
				  REQUEST_GET_VERSION,
				  USB_TYPE_VENDOR | USB_DIR_IN, 0, 0,
				  b, sizeof(b), USB_CTRL_GET_TIMEOUT);
	if (hwversion != NULL)
		*hwversion  = (b[0] << 24)  | (b[1] << 16)  | (b[2] << 8)  | b[3];
	if (romversion != NULL)
		*romversion = (b[4] << 24)  | (b[5] << 16)  | (b[6] << 8)  | b[7];
	if (ramversion != NULL)
		*ramversion = (b[8] << 24)  | (b[9] << 16)  | (b[10] << 8) | b[11];
	if (fwtype != NULL)
		*fwtype     = (b[12] << 24) | (b[13] << 16) | (b[14] << 8) | b[15];
	return ret;
}