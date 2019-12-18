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
struct urb {int /*<<< orphan*/  transfer_flags; } ;
struct ar9170 {int /*<<< orphan*/  rx_anch; int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR9170_USB_EP_CTRL_MAX ; 
 int /*<<< orphan*/  AR9170_USB_EP_IRQ ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  URB_FREE_BUFFER ; 
 int /*<<< orphan*/  carl9170_usb_rx_irq_complete ; 
 void* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_anchor_urb (struct urb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fill_int_urb (struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ar9170*,int) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_rcvintpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_unanchor_urb (struct urb*) ; 

__attribute__((used)) static int carl9170_usb_send_rx_irq_urb(struct ar9170 *ar)
{
	struct urb *urb = NULL;
	void *ibuf;
	int err = -ENOMEM;

	urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!urb)
		goto out;

	ibuf = kmalloc(AR9170_USB_EP_CTRL_MAX, GFP_KERNEL);
	if (!ibuf)
		goto out;

	usb_fill_int_urb(urb, ar->udev, usb_rcvintpipe(ar->udev,
			 AR9170_USB_EP_IRQ), ibuf, AR9170_USB_EP_CTRL_MAX,
			 carl9170_usb_rx_irq_complete, ar, 1);

	urb->transfer_flags |= URB_FREE_BUFFER;

	usb_anchor_urb(urb, &ar->rx_anch);
	err = usb_submit_urb(urb, GFP_KERNEL);
	if (err)
		usb_unanchor_urb(urb);

out:
	usb_free_urb(urb);
	return err;
}