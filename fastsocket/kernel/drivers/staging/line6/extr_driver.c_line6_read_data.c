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
struct usb_line6 {int /*<<< orphan*/  ifcdev; struct usb_device* usbdev; } ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int HZ ; 
 int LINE6_TIMEOUT ; 
 int USB_DIR_IN ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int,int,int,int,void*,size_t,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

int line6_read_data(struct usb_line6 *line6, int address, void *data, size_t datalen)
{
	struct usb_device *usbdev = line6->usbdev;
	int ret;
	unsigned char len;

	/* query the serial number: */
	ret = usb_control_msg(usbdev, usb_sndctrlpipe(usbdev, 0), 0x67,
												USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_DIR_OUT,
												(datalen << 8) | 0x21, address, NULL, 0, LINE6_TIMEOUT * HZ);

	if (ret < 0) {
		dev_err(line6->ifcdev, "read request failed (error %d)\n", ret);
		return ret;
	}

	/* Wait for data length. We'll get a couple of 0xff until length arrives. */
	do {
		ret = usb_control_msg(usbdev, usb_rcvctrlpipe(usbdev, 0), 0x67,
				      USB_TYPE_VENDOR | USB_RECIP_DEVICE |
				      USB_DIR_IN,
				      0x0012, 0x0000, &len, 1,
				      LINE6_TIMEOUT * HZ);
		if (ret < 0) {
			dev_err(line6->ifcdev,
				"receive length failed (error %d)\n", ret);
			return ret;
		}
	}
	while (len == 0xff)
		;

	if (len != datalen) {
		/* should be equal or something went wrong */
		dev_err(line6->ifcdev,
			"length mismatch (expected %d, got %d)\n",
			(int)datalen, (int)len);
		return -EINVAL;
	}

	/* receive the result: */
	ret = usb_control_msg(usbdev, usb_rcvctrlpipe(usbdev, 0), 0x67,
			      USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_DIR_IN,
			      0x0013, 0x0000, data, datalen,
			      LINE6_TIMEOUT * HZ);

	if (ret < 0) {
		dev_err(line6->ifcdev, "read failed (error %d)\n", ret);
		return ret;
	}

	return 0;
}