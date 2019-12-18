#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zfs_handle_t ;
struct TYPE_3__ {char* sd_snapname; int /*<<< orphan*/  sd_nvl; } ;
typedef  TYPE_1__ snapdata_t ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  ZFS_PROP_INCONSISTENT ; 
 int /*<<< orphan*/  fnvlist_add_boolean (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ *) ; 
 char* zfs_get_name (int /*<<< orphan*/ *) ; 
 int zfs_iter_filesystems (int /*<<< orphan*/ *,int (*) (int /*<<< orphan*/ *,void*),TYPE_1__*) ; 
 scalar_t__ zfs_prop_get_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zfs_snapshot_cb(zfs_handle_t *zhp, void *arg)
{
	snapdata_t *sd = arg;
	char name[ZFS_MAX_DATASET_NAME_LEN];
	int rv = 0;

	if (zfs_prop_get_int(zhp, ZFS_PROP_INCONSISTENT) == 0) {
		(void) snprintf(name, sizeof (name),
		    "%s@%s", zfs_get_name(zhp), sd->sd_snapname);

		fnvlist_add_boolean(sd->sd_nvl, name);

		rv = zfs_iter_filesystems(zhp, zfs_snapshot_cb, sd);
	}
	zfs_close(zhp);

	return (rv);
}