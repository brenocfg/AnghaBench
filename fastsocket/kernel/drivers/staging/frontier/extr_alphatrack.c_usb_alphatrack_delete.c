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
struct usb_alphatrack {struct usb_alphatrack* interrupt_out_buffer; struct usb_alphatrack* interrupt_in_buffer; struct usb_alphatrack* ring_buffer; int /*<<< orphan*/  interrupt_out_urb; int /*<<< orphan*/  interrupt_in_urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct usb_alphatrack*) ; 
 int /*<<< orphan*/  usb_alphatrack_abort_transfers (struct usb_alphatrack*) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usb_alphatrack_delete(struct usb_alphatrack *dev)
{
	usb_alphatrack_abort_transfers(dev);
	usb_free_urb(dev->interrupt_in_urb);
	usb_free_urb(dev->interrupt_out_urb);
	kfree(dev->ring_buffer);
	kfree(dev->interrupt_in_buffer);
	kfree(dev->interrupt_out_buffer);
	kfree(dev);		/* fixme oldi_buffer */
}