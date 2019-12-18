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
struct wacom {TYPE_1__* intf; int /*<<< orphan*/  lock; scalar_t__ open; int /*<<< orphan*/  irq; } ;
struct input_dev {int dummy; } ;
struct TYPE_2__ {scalar_t__ needs_remote_wakeup; } ;

/* Variables and functions */
 struct wacom* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wacom_close(struct input_dev *dev)
{
	struct wacom *wacom = input_get_drvdata(dev);

	mutex_lock(&wacom->lock);
	usb_kill_urb(wacom->irq);
	wacom->open = 0;
	wacom->intf->needs_remote_wakeup = 0;
	mutex_unlock(&wacom->lock);

	usb_autopm_put_interface(wacom->intf);
}