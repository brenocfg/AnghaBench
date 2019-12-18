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
struct vstusb_device {int /*<<< orphan*/  lock; int /*<<< orphan*/  submitted; } ;
struct usb_interface {int dummy; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct vstusb_device* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_kill_anchored_urbs (int /*<<< orphan*/ *) ; 
 int usb_wait_anchor_empty_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int vstusb_suspend(struct usb_interface *intf, pm_message_t message)
{
	struct vstusb_device *vstdev = usb_get_intfdata(intf);
	int time;
	if (!vstdev)
		return 0;

	mutex_lock(&vstdev->lock);
	time = usb_wait_anchor_empty_timeout(&vstdev->submitted, 1000);
	if (!time)
		usb_kill_anchored_urbs(&vstdev->submitted);
	mutex_unlock(&vstdev->lock);

	return 0;
}