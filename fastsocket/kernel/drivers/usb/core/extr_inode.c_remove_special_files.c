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
 int /*<<< orphan*/ * devices_usbfs_dentry ; 
 int /*<<< orphan*/  fs_remove_file (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_release_fs (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbfs_mount ; 
 int /*<<< orphan*/  usbfs_mount_count ; 

__attribute__((used)) static void remove_special_files (void)
{
	if (devices_usbfs_dentry)
		fs_remove_file (devices_usbfs_dentry);
	devices_usbfs_dentry = NULL;
	simple_release_fs(&usbfs_mount, &usbfs_mount_count);
}