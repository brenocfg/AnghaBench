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
struct usb_kbd {int /*<<< orphan*/  leds_dma; int /*<<< orphan*/  leds; int /*<<< orphan*/  cr_dma; int /*<<< orphan*/  cr; int /*<<< orphan*/  new_dma; int /*<<< orphan*/  new; int /*<<< orphan*/  led; int /*<<< orphan*/  irq; } ;
struct usb_device {int dummy; } ;
struct usb_ctrlrequest {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_buffer_free (struct usb_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usb_kbd_free_mem(struct usb_device *dev, struct usb_kbd *kbd)
{
	usb_free_urb(kbd->irq);
	usb_free_urb(kbd->led);
	usb_buffer_free(dev, 8, kbd->new, kbd->new_dma);
	usb_buffer_free(dev, sizeof(struct usb_ctrlrequest), kbd->cr, kbd->cr_dma);
	usb_buffer_free(dev, 1, kbd->leds, kbd->leds_dma);
}