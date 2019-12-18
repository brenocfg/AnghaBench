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
struct wusb_dev {void* wusb_cap_descr; } ;
struct device {int dummy; } ;
struct usb_device {struct device dev; } ;
struct usb_dev_cap_header {size_t bLength; int bDevCapabilityType; } ;
struct usb_bos_descriptor {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EBADF ; 
 int ENOSPC ; 
#define  USB_CAP_TYPE_WIRELESS_USB 128 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,size_t,...) ; 

__attribute__((used)) static int wusb_dev_bos_grok(struct usb_device *usb_dev,
			     struct wusb_dev *wusb_dev,
			     struct usb_bos_descriptor *bos, size_t desc_size)
{
	ssize_t result;
	struct device *dev = &usb_dev->dev;
	void *itr, *top;

	/* Walk over BOS capabilities, verify them */
	itr = (void *)bos + sizeof(*bos);
	top = itr + desc_size - sizeof(*bos);
	while (itr < top) {
		struct usb_dev_cap_header *cap_hdr = itr;
		size_t cap_size;
		u8 cap_type;
		if (top - itr < sizeof(*cap_hdr)) {
			dev_err(dev, "Device BUG? premature end of BOS header "
				"data [offset 0x%02x]: only %zu bytes left\n",
				(int)(itr - (void *)bos), top - itr);
			result = -ENOSPC;
			goto error_bad_cap;
		}
		cap_size = cap_hdr->bLength;
		cap_type = cap_hdr->bDevCapabilityType;
		if (cap_size == 0)
			break;
		if (cap_size > top - itr) {
			dev_err(dev, "Device BUG? premature end of BOS data "
				"[offset 0x%02x cap %02x %zu bytes]: "
				"only %zu bytes left\n",
				(int)(itr - (void *)bos),
				cap_type, cap_size, top - itr);
			result = -EBADF;
			goto error_bad_cap;
		}
		switch (cap_type) {
		case USB_CAP_TYPE_WIRELESS_USB:
			if (cap_size != sizeof(*wusb_dev->wusb_cap_descr))
				dev_err(dev, "Device BUG? WUSB Capability "
					"descriptor is %zu bytes vs %zu "
					"needed\n", cap_size,
					sizeof(*wusb_dev->wusb_cap_descr));
			else
				wusb_dev->wusb_cap_descr = itr;
			break;
		default:
			dev_err(dev, "BUG? Unknown BOS capability 0x%02x "
				"(%zu bytes) at offset 0x%02x\n", cap_type,
				cap_size, (int)(itr - (void *)bos));
		}
		itr += cap_size;
	}
	result = 0;
error_bad_cap:
	return result;
}