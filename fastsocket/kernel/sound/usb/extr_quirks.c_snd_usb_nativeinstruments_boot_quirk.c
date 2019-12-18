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
struct usb_device {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_reset_device (struct usb_device*) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_usb_nativeinstruments_boot_quirk(struct usb_device *dev)
{
	int ret = usb_control_msg(dev, usb_sndctrlpipe(dev, 0),
				  0xaf, USB_TYPE_VENDOR | USB_RECIP_DEVICE,
				  cpu_to_le16(1), 0, NULL, 0, 1000);

	if (ret < 0)
		return ret;

	usb_reset_device(dev);

	/* return -EAGAIN, so the creation of an audio interface for this
	 * temporary device is aborted. The device will reconnect with a
	 * new product ID */
	return -EAGAIN;
}