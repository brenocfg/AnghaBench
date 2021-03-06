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
typedef  int u16 ;
struct usbnet {int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_WRITE_REGS ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  USB_CTRL_SET_TIMEOUT ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  devdbg (struct usbnet*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dm_write(struct usbnet *dev, u8 reg, u16 length, void *data)
{
	void *buf = NULL;
	int err = -ENOMEM;

	devdbg(dev, "dm_write() reg=0x%02x, length=%d", reg, length);

	if (data) {
		buf = kmalloc(length, GFP_KERNEL);
		if (!buf)
			goto out;
		memcpy(buf, data, length);
	}

	err = usb_control_msg(dev->udev,
			      usb_sndctrlpipe(dev->udev, 0),
			      DM_WRITE_REGS,
			      USB_DIR_OUT | USB_TYPE_VENDOR |USB_RECIP_DEVICE,
			      0, reg, buf, length, USB_CTRL_SET_TIMEOUT);
	kfree(buf);
	if (err >= 0 && err < length)
		err = -EINVAL;
 out:
	return err;
}