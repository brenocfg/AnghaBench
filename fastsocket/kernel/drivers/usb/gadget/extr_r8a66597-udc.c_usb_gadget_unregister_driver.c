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
struct usb_gadget_driver {int /*<<< orphan*/  (* unbind ) (TYPE_1__*) ;} ;
struct TYPE_2__ {scalar_t__ speed; int /*<<< orphan*/  dev; } ;
struct r8a66597 {struct usb_gadget_driver* driver; TYPE_1__ gadget; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INTENB0 ; 
 scalar_t__ USB_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  VBSE ; 
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_controller (struct r8a66597*) ; 
 int /*<<< orphan*/  init_controller (struct r8a66597*) ; 
 int /*<<< orphan*/  r8a66597_bclr (struct r8a66597*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8a66597_usb_disconnect (struct r8a66597*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 struct r8a66597* the_controller ; 

int usb_gadget_unregister_driver(struct usb_gadget_driver *driver)
{
	struct r8a66597 *r8a66597 = the_controller;
	unsigned long flags;

	if (driver != r8a66597->driver || !driver->unbind)
		return -EINVAL;

	spin_lock_irqsave(&r8a66597->lock, flags);
	if (r8a66597->gadget.speed != USB_SPEED_UNKNOWN)
		r8a66597_usb_disconnect(r8a66597);
	spin_unlock_irqrestore(&r8a66597->lock, flags);

	r8a66597_bclr(r8a66597, VBSE, INTENB0);

	driver->unbind(&r8a66597->gadget);

	init_controller(r8a66597);
	disable_controller(r8a66597);

	device_del(&r8a66597->gadget.dev);
	r8a66597->driver = NULL;
	return 0;
}