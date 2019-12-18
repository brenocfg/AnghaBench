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
typedef  scalar_t__ zprop_source_t ;
typedef  int /*<<< orphan*/  zfs_handle_t ;
typedef  int /*<<< orphan*/  mountpoint ;

/* Variables and functions */
 int ZFS_MAXPROPLEN ; 
 scalar_t__ ZPROP_SRC_DEFAULT ; 
 scalar_t__ ZPROP_SRC_INHERITED ; 
 int /*<<< orphan*/  rmdir (char*) ; 
 int /*<<< orphan*/  zfs_is_mountable (int /*<<< orphan*/ *,char*,int,scalar_t__*) ; 

void
remove_mountpoint(zfs_handle_t *zhp)
{
	char mountpoint[ZFS_MAXPROPLEN];
	zprop_source_t source;

	if (!zfs_is_mountable(zhp, mountpoint, sizeof (mountpoint),
	    &source))
		return;

	if (source == ZPROP_SRC_DEFAULT ||
	    source == ZPROP_SRC_INHERITED) {
		/*
		 * Try to remove the directory, silently ignoring any errors.
		 * The filesystem may have since been removed or moved around,
		 * and this error isn't really useful to the administrator in
		 * any way.
		 */
		(void) rmdir(mountpoint);
	}
}