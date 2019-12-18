#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wacom {int open; int /*<<< orphan*/  lock; TYPE_1__* intf; int /*<<< orphan*/  irq; } ;
struct input_dev {int dummy; } ;
struct TYPE_3__ {int needs_remote_wakeup; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct wacom* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ usb_autopm_get_interface (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (TYPE_1__*) ; 
 scalar_t__ usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wacom_open(struct input_dev *dev)
{
	struct wacom *wacom = input_get_drvdata(dev);
	int retval = 0;

	if (usb_autopm_get_interface(wacom->intf) < 0)
		return -EIO;

	mutex_lock(&wacom->lock);

	if (usb_submit_urb(wacom->irq, GFP_KERNEL)) {
		retval = -EIO;
		goto out;
	}

	wacom->open = 1;
	wacom->intf->needs_remote_wakeup = 1;

out:
	if (retval)
		usb_autopm_put_interface(wacom->intf);
	mutex_unlock(&wacom->lock);
	return retval;
}