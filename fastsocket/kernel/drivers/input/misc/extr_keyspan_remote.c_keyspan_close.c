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
struct usb_keyspan {int /*<<< orphan*/  irq_urb; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 struct usb_keyspan* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void keyspan_close(struct input_dev *dev)
{
	struct usb_keyspan *remote = input_get_drvdata(dev);

	usb_kill_urb(remote->irq_urb);
}