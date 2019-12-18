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
struct usbnet {int dummy; } ;
struct usb_context {struct usbnet* dev; } ;
struct urb {int status; struct usb_context* context; } ;

/* Variables and functions */
 int /*<<< orphan*/  devwarn (struct usbnet*,char*,int) ; 
 int /*<<< orphan*/  kfree (struct usb_context*) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 

__attribute__((used)) static void smsc95xx_async_cmd_callback(struct urb *urb)
{
	struct usb_context *usb_context = urb->context;
	struct usbnet *dev = usb_context->dev;
	int status = urb->status;

	if (status < 0)
		devwarn(dev, "async callback failed with %d", status);

	kfree(usb_context);
	usb_free_urb(urb);
}