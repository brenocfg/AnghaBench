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
struct zd_usb_interrupt {int /*<<< orphan*/  lock; int /*<<< orphan*/ * buffer; int /*<<< orphan*/  buffer_dma; struct urb* urb; } ;
struct zd_usb {struct zd_usb_interrupt intr; } ;
struct usb_device {int dummy; } ;
struct urb {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  USB_MAX_EP_INT_BUFFER ; 
 int /*<<< orphan*/  dev_dbg_f (int /*<<< orphan*/ ,char*,struct urb*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usb_buffer_free (struct usb_device*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_kill_urb (struct urb*) ; 
 int /*<<< orphan*/  zd_usb_dev (struct zd_usb*) ; 
 struct usb_device* zd_usb_to_usbdev (struct zd_usb*) ; 

void zd_usb_disable_int(struct zd_usb *usb)
{
	unsigned long flags;
	struct usb_device *udev = zd_usb_to_usbdev(usb);
	struct zd_usb_interrupt *intr = &usb->intr;
	struct urb *urb;
	void *buffer;
	dma_addr_t buffer_dma;

	spin_lock_irqsave(&intr->lock, flags);
	urb = intr->urb;
	if (!urb) {
		spin_unlock_irqrestore(&intr->lock, flags);
		return;
	}
	intr->urb = NULL;
	buffer = intr->buffer;
	buffer_dma = intr->buffer_dma;
	intr->buffer = NULL;
	spin_unlock_irqrestore(&intr->lock, flags);

	usb_kill_urb(urb);
	dev_dbg_f(zd_usb_dev(usb), "urb %p killed\n", urb);
	usb_free_urb(urb);

	if (buffer)
		usb_buffer_free(udev, USB_MAX_EP_INT_BUFFER,
				  buffer, buffer_dma);
}