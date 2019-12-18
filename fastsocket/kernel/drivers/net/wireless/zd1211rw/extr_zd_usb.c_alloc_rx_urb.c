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
struct zd_usb {int dummy; } ;
struct usb_device {int dummy; } ;
struct urb {int /*<<< orphan*/  transfer_flags; int /*<<< orphan*/  transfer_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  EP_DATA_IN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  URB_NO_TRANSFER_DMA_MAP ; 
 int /*<<< orphan*/  USB_MAX_RX_SIZE ; 
 int /*<<< orphan*/  rx_urb_complete ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* usb_buffer_alloc (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,struct usb_device*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct zd_usb*) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 struct usb_device* zd_usb_to_usbdev (struct zd_usb*) ; 

__attribute__((used)) static struct urb *alloc_rx_urb(struct zd_usb *usb)
{
	struct usb_device *udev = zd_usb_to_usbdev(usb);
	struct urb *urb;
	void *buffer;

	urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!urb)
		return NULL;
	buffer = usb_buffer_alloc(udev, USB_MAX_RX_SIZE, GFP_KERNEL,
				    &urb->transfer_dma);
	if (!buffer) {
		usb_free_urb(urb);
		return NULL;
	}

	usb_fill_bulk_urb(urb, udev, usb_rcvbulkpipe(udev, EP_DATA_IN),
			  buffer, USB_MAX_RX_SIZE,
			  rx_urb_complete, usb);
	urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	return urb;
}