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
struct usb_device {scalar_t__ speed; } ;
struct urb {int interval; int /*<<< orphan*/  transfer_buffer; int /*<<< orphan*/  transfer_dma; int /*<<< orphan*/  transfer_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int INTERRUPT_RATE ; 
 int /*<<< orphan*/  URB_NO_TRANSFER_DMA_MAP ; 
 int /*<<< orphan*/  URB_SHORT_NOT_OK ; 
 scalar_t__ USB_SPEED_HIGH ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  simple_callback ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_buffer_alloc (struct usb_device*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,struct usb_device*,int,int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 scalar_t__ usb_pipein (int) ; 

__attribute__((used)) static struct urb *simple_alloc_urb (
	struct usb_device	*udev,
	int			pipe,
	unsigned long		bytes
)
{
	struct urb		*urb;

	urb = usb_alloc_urb (0, GFP_KERNEL);
	if (!urb)
		return urb;
	usb_fill_bulk_urb (urb, udev, pipe, NULL, bytes, simple_callback, NULL);
	urb->interval = (udev->speed == USB_SPEED_HIGH)
			? (INTERRUPT_RATE << 3)
			: INTERRUPT_RATE;
	urb->transfer_flags = URB_NO_TRANSFER_DMA_MAP;
	if (usb_pipein (pipe))
		urb->transfer_flags |= URB_SHORT_NOT_OK;
	urb->transfer_buffer = usb_buffer_alloc (udev, bytes, GFP_KERNEL,
			&urb->transfer_dma);
	if (!urb->transfer_buffer) {
		usb_free_urb (urb);
		urb = NULL;
	} else
		memset (urb->transfer_buffer, 0, bytes);
	return urb;
}