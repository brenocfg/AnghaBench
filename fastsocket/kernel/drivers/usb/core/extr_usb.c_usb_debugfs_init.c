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

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/ * debugfs_create_dir (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_debug_devices ; 
 int /*<<< orphan*/ * usb_debug_root ; 
 int /*<<< orphan*/  usbfs_devices_fops ; 

__attribute__((used)) static int usb_debugfs_init(void)
{
	usb_debug_root = debugfs_create_dir("usb", NULL);
	if (!usb_debug_root)
		return -ENOENT;

	usb_debug_devices = debugfs_create_file("devices", 0444,
						usb_debug_root, NULL,
						&usbfs_devices_fops);
	if (!usb_debug_devices) {
		debugfs_remove(usb_debug_root);
		usb_debug_root = NULL;
		return -ENOENT;
	}

	return 0;
}