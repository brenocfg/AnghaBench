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
struct usb_keyspan {TYPE_1__* irq_urb; int /*<<< orphan*/  udev; } ;
struct input_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct usb_keyspan* input_get_drvdata (struct input_dev*) ; 
 scalar_t__ usb_submit_urb (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int keyspan_open(struct input_dev *dev)
{
	struct usb_keyspan *remote = input_get_drvdata(dev);

	remote->irq_urb->dev = remote->udev;
	if (usb_submit_urb(remote->irq_urb, GFP_KERNEL))
		return -EIO;

	return 0;
}