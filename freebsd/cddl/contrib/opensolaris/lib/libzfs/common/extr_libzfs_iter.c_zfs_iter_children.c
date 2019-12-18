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
typedef  int /*<<< orphan*/  zfs_iter_f ;
typedef  int /*<<< orphan*/  zfs_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int zfs_iter_filesystems (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int zfs_iter_snapshots (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
zfs_iter_children(zfs_handle_t *zhp, zfs_iter_f func, void *data)
{
	int ret;

	if ((ret = zfs_iter_snapshots(zhp, B_FALSE, func, data, 0, 0)) != 0)
		return (ret);

	return (zfs_iter_filesystems(zhp, func, data));
}