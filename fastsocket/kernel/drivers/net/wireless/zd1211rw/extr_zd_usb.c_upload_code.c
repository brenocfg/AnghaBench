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
typedef  size_t u16 ;
struct usb_device {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  ret ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t MAX_TRANSFER_SIZE ; 
 int REBOOT ; 
 int USB_DIR_IN ; 
 int USB_DIR_OUT ; 
 int /*<<< orphan*/  USB_REQ_FIRMWARE_CONFIRM ; 
 int /*<<< orphan*/  USB_REQ_FIRMWARE_DOWNLOAD ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  dev_dbg_f (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,size_t) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,size_t,int /*<<< orphan*/ ,int*,int,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int upload_code(struct usb_device *udev,
	const u8 *data, size_t size, u16 code_offset, int flags)
{
	u8 *p;
	int r;

	/* USB request blocks need "kmalloced" buffers.
	 */
	p = kmalloc(MAX_TRANSFER_SIZE, GFP_KERNEL);
	if (!p) {
		dev_err(&udev->dev, "out of memory\n");
		r = -ENOMEM;
		goto error;
	}

	size &= ~1;
	while (size > 0) {
		size_t transfer_size = size <= MAX_TRANSFER_SIZE ?
			size : MAX_TRANSFER_SIZE;

		dev_dbg_f(&udev->dev, "transfer size %zu\n", transfer_size);

		memcpy(p, data, transfer_size);
		r = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
			USB_REQ_FIRMWARE_DOWNLOAD,
			USB_DIR_OUT | USB_TYPE_VENDOR,
			code_offset, 0, p, transfer_size, 1000 /* ms */);
		if (r < 0) {
			dev_err(&udev->dev,
			       "USB control request for firmware upload"
			       " failed. Error number %d\n", r);
			goto error;
		}
		transfer_size = r & ~1;

		size -= transfer_size;
		data += transfer_size;
		code_offset += transfer_size/sizeof(u16);
	}

	if (flags & REBOOT) {
		u8 ret;

		/* Use "DMA-aware" buffer. */
		r = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
			USB_REQ_FIRMWARE_CONFIRM,
			USB_DIR_IN | USB_TYPE_VENDOR,
			0, 0, p, sizeof(ret), 5000 /* ms */);
		if (r != sizeof(ret)) {
			dev_err(&udev->dev,
				"control request firmeware confirmation failed."
				" Return value %d\n", r);
			if (r >= 0)
				r = -ENODEV;
			goto error;
		}
		ret = p[0];
		if (ret & 0x80) {
			dev_err(&udev->dev,
				"Internal error while downloading."
				" Firmware confirm return value %#04x\n",
				(unsigned int)ret);
			r = -ENODEV;
			goto error;
		}
		dev_dbg_f(&udev->dev, "firmware confirm return value %#04x\n",
			(unsigned int)ret);
	}

	r = 0;
error:
	kfree(p);
	return r;
}