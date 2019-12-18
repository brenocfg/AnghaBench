#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_device_id {int match_flags; scalar_t__ idVendor; scalar_t__ idProduct; scalar_t__ bcdDevice_lo; scalar_t__ bcdDevice_hi; scalar_t__ bDeviceClass; scalar_t__ bDeviceSubClass; scalar_t__ bDeviceProtocol; } ;
struct TYPE_2__ {scalar_t__ bDeviceClass; scalar_t__ bDeviceSubClass; scalar_t__ bDeviceProtocol; int /*<<< orphan*/  bcdDevice; int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; } ;
struct usb_device {TYPE_1__ descriptor; } ;

/* Variables and functions */
 int USB_DEVICE_ID_MATCH_DEV_CLASS ; 
 int USB_DEVICE_ID_MATCH_DEV_HI ; 
 int USB_DEVICE_ID_MATCH_DEV_LO ; 
 int USB_DEVICE_ID_MATCH_DEV_PROTOCOL ; 
 int USB_DEVICE_ID_MATCH_DEV_SUBCLASS ; 
 int USB_DEVICE_ID_MATCH_PRODUCT ; 
 int USB_DEVICE_ID_MATCH_VENDOR ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 

int usb_match_device(struct usb_device *dev, const struct usb_device_id *id)
{
	if ((id->match_flags & USB_DEVICE_ID_MATCH_VENDOR) &&
	    id->idVendor != le16_to_cpu(dev->descriptor.idVendor))
		return 0;

	if ((id->match_flags & USB_DEVICE_ID_MATCH_PRODUCT) &&
	    id->idProduct != le16_to_cpu(dev->descriptor.idProduct))
		return 0;

	/* No need to test id->bcdDevice_lo != 0, since 0 is never
	   greater than any unsigned number. */
	if ((id->match_flags & USB_DEVICE_ID_MATCH_DEV_LO) &&
	    (id->bcdDevice_lo > le16_to_cpu(dev->descriptor.bcdDevice)))
		return 0;

	if ((id->match_flags & USB_DEVICE_ID_MATCH_DEV_HI) &&
	    (id->bcdDevice_hi < le16_to_cpu(dev->descriptor.bcdDevice)))
		return 0;

	if ((id->match_flags & USB_DEVICE_ID_MATCH_DEV_CLASS) &&
	    (id->bDeviceClass != dev->descriptor.bDeviceClass))
		return 0;

	if ((id->match_flags & USB_DEVICE_ID_MATCH_DEV_SUBCLASS) &&
	    (id->bDeviceSubClass != dev->descriptor.bDeviceSubClass))
		return 0;

	if ((id->match_flags & USB_DEVICE_ID_MATCH_DEV_PROTOCOL) &&
	    (id->bDeviceProtocol != dev->descriptor.bDeviceProtocol))
		return 0;

	return 1;
}