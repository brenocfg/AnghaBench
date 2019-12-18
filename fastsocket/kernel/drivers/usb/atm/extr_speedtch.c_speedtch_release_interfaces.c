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
struct usb_interface {int dummy; } ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  speedtch_usb_driver ; 
 int /*<<< orphan*/  usb_driver_release_interface (int /*<<< orphan*/ *,struct usb_interface*) ; 
 struct usb_interface* usb_ifnum_to_if (struct usb_device*,int) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void speedtch_release_interfaces(struct usb_device *usb_dev, int num_interfaces) {
	struct usb_interface *cur_intf;
	int i;

	for(i = 0; i < num_interfaces; i++)
		if ((cur_intf = usb_ifnum_to_if(usb_dev, i))) {
			usb_set_intfdata(cur_intf, NULL);
			usb_driver_release_interface(&speedtch_usb_driver, cur_intf);
		}
}