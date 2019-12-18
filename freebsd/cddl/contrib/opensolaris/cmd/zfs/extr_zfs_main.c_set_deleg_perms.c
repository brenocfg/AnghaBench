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
typedef  scalar_t__ zfs_type_t ;
typedef  int /*<<< orphan*/  zfs_handle_t ;
struct deleg_perms {int /*<<< orphan*/  nvl; int /*<<< orphan*/  un; } ;

/* Variables and functions */
 scalar_t__ ZFS_TYPE_FILESYSTEM ; 
 scalar_t__ ZFS_TYPE_VOLUME ; 
 scalar_t__ zfs_get_type (int /*<<< orphan*/ *) ; 
 int zfs_set_fsacl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
set_deleg_perms(zfs_handle_t *zhp, void *data)
{
	struct deleg_perms *perms = (struct deleg_perms *)data;
	zfs_type_t zfs_type = zfs_get_type(zhp);

	if (zfs_type != ZFS_TYPE_FILESYSTEM && zfs_type != ZFS_TYPE_VOLUME)
		return (0);

	return (zfs_set_fsacl(zhp, perms->un, perms->nvl));
}