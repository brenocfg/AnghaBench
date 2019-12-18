#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_kbd {scalar_t__* leds; scalar_t__ newleds; TYPE_2__* led; int /*<<< orphan*/  usbdev; } ;
struct urb {scalar_t__ status; TYPE_1__* dev; struct usb_kbd* context; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  err_hid (char*) ; 
 scalar_t__ usb_submit_urb (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usb_kbd_led(struct urb *urb)
{
	struct usb_kbd *kbd = urb->context;

	if (urb->status)
		dev_warn(&urb->dev->dev, "led urb status %d received\n",
			 urb->status);

	if (*(kbd->leds) == kbd->newleds)
		return;

	*(kbd->leds) = kbd->newleds;
	kbd->led->dev = kbd->usbdev;
	if (usb_submit_urb(kbd->led, GFP_ATOMIC))
		err_hid("usb_submit_urb(leds) failed");
}