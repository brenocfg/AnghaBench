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
struct usb_bus {int /*<<< orphan*/ * usbfs_dentry; } ;

/* Variables and functions */
 int /*<<< orphan*/  fs_remove_file (int /*<<< orphan*/ *) ; 
 scalar_t__ num_buses ; 
 int /*<<< orphan*/  remove_special_files () ; 

__attribute__((used)) static void usbfs_remove_bus(struct usb_bus *bus)
{
	if (bus->usbfs_dentry) {
		fs_remove_file (bus->usbfs_dentry);
		bus->usbfs_dentry = NULL;
	}

	--num_buses;
	if (num_buses <= 0) {
		remove_special_files();
		num_buses = 0;
	}
}