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
typedef  int /*<<< orphan*/  u16 ;
struct usbnet {struct usb_device* udev; } ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  MCS7830_CTRL_TIMEOUT ; 
 int /*<<< orphan*/  MCS7830_WR_BMREQ ; 
 int /*<<< orphan*/  MCS7830_WR_BREQ ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int /*<<< orphan*/ ) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mcs7830_set_reg(struct usbnet *dev, u16 index, u16 size, void *data)
{
	struct usb_device *xdev = dev->udev;
	int ret;
	void *buffer;

	buffer = kmalloc(size, GFP_NOIO);
	if (buffer == NULL)
		return -ENOMEM;

	memcpy(buffer, data, size);

	ret = usb_control_msg(xdev, usb_sndctrlpipe(xdev, 0), MCS7830_WR_BREQ,
			      MCS7830_WR_BMREQ, 0x0000, index, buffer,
			      size, MCS7830_CTRL_TIMEOUT);
	kfree(buffer);
	return ret;
}