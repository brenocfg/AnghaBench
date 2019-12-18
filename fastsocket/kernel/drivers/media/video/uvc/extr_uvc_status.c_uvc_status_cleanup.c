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
struct uvc_device {int /*<<< orphan*/  status; int /*<<< orphan*/  int_urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uvc_input_cleanup (struct uvc_device*) ; 

void uvc_status_cleanup(struct uvc_device *dev)
{
	usb_kill_urb(dev->int_urb);
	usb_free_urb(dev->int_urb);
	kfree(dev->status);
	uvc_input_cleanup(dev);
}