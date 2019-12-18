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
struct usb_xpad {scalar_t__ xtype; int /*<<< orphan*/  idata_dma; int /*<<< orphan*/  idata; int /*<<< orphan*/  udev; int /*<<< orphan*/  irq_in; int /*<<< orphan*/  bulk_out; int /*<<< orphan*/  dev; } ;
struct usb_interface {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XPAD_PKT_LEN ; 
 scalar_t__ XTYPE_XBOX360W ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct usb_xpad*) ; 
 int /*<<< orphan*/  usb_buffer_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 struct usb_xpad* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpad_deinit_output (struct usb_xpad*) ; 
 int /*<<< orphan*/  xpad_led_disconnect (struct usb_xpad*) ; 

__attribute__((used)) static void xpad_disconnect(struct usb_interface *intf)
{
	struct usb_xpad *xpad = usb_get_intfdata (intf);

	usb_set_intfdata(intf, NULL);
	if (xpad) {
		xpad_led_disconnect(xpad);
		input_unregister_device(xpad->dev);
		xpad_deinit_output(xpad);
		if (xpad->xtype == XTYPE_XBOX360W) {
			usb_kill_urb(xpad->bulk_out);
			usb_free_urb(xpad->bulk_out);
			usb_kill_urb(xpad->irq_in);
		}
		usb_free_urb(xpad->irq_in);
		usb_buffer_free(xpad->udev, XPAD_PKT_LEN,
				xpad->idata, xpad->idata_dma);
		kfree(xpad);
	}
}