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
struct usb_xpad {scalar_t__ xtype; int /*<<< orphan*/  irq_in; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ XTYPE_XBOX360W ; 
 struct usb_xpad* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpad_stop_output (struct usb_xpad*) ; 

__attribute__((used)) static void xpad_close(struct input_dev *dev)
{
	struct usb_xpad *xpad = input_get_drvdata(dev);

	if(xpad->xtype != XTYPE_XBOX360W)
		usb_kill_urb(xpad->irq_in);
	xpad_stop_output(xpad);
}