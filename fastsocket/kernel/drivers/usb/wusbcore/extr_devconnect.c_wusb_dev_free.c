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
struct wusb_dev {int /*<<< orphan*/  set_gtk_urb; struct wusb_dev* set_gtk_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct wusb_dev*) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wusb_dev_free(struct wusb_dev *wusb_dev)
{
	if (wusb_dev) {
		kfree(wusb_dev->set_gtk_req);
		usb_free_urb(wusb_dev->set_gtk_urb);
		kfree(wusb_dev);
	}
}