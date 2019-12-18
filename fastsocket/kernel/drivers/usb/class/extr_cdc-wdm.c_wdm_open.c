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
struct wdm_device {TYPE_1__* intf; int /*<<< orphan*/  plock; int /*<<< orphan*/  count; int /*<<< orphan*/  validity; int /*<<< orphan*/  flags; } ;
struct usb_interface {int needs_remote_wakeup; } ;
struct inode {int dummy; } ;
struct file {struct wdm_device* private_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WDM_DISCONNECTING ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int iminor (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int usb_autopm_get_interface (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (TYPE_1__*) ; 
 struct usb_interface* usb_find_interface (int /*<<< orphan*/ *,int) ; 
 struct wdm_device* usb_get_intfdata (struct usb_interface*) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wdm_driver ; 
 int /*<<< orphan*/  wdm_mutex ; 

__attribute__((used)) static int wdm_open(struct inode *inode, struct file *file)
{
	int minor = iminor(inode);
	int rv = -ENODEV;
	struct usb_interface *intf;
	struct wdm_device *desc;

	mutex_lock(&wdm_mutex);
	intf = usb_find_interface(&wdm_driver, minor);
	if (!intf)
		goto out;

	desc = usb_get_intfdata(intf);
	if (test_bit(WDM_DISCONNECTING, &desc->flags))
		goto out;
	file->private_data = desc;

	rv = usb_autopm_get_interface(desc->intf);
	if (rv < 0) {
		dev_err(&desc->intf->dev, "Error autopm - %d\n", rv);
		goto out;
	}
	intf->needs_remote_wakeup = 1;

	mutex_lock(&desc->plock);
	if (!desc->count++) {
		rv = usb_submit_urb(desc->validity, GFP_KERNEL);
		if (rv < 0) {
			desc->count--;
			dev_err(&desc->intf->dev,
				"Error submitting int urb - %d\n", rv);
		}
	} else {
		rv = 0;
	}
	mutex_unlock(&desc->plock);
	usb_autopm_put_interface(desc->intf);
out:
	mutex_unlock(&wdm_mutex);
	return rv;
}