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
struct usb_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int USB_DIR_IN ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int,int,int,int,int*,size_t,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ReadPacket(struct usb_device *udev, u8 *packet, u8 *buf, size_t size)
{
	if (!packet || size <= 0)
		return -EINVAL;

	return usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
			 packet[1] + (packet[0] << 8),
			 USB_DIR_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			 packet[2] + (packet[3] << 8),
			 packet[4] + (packet[5] << 8), buf, size, 1000);
}