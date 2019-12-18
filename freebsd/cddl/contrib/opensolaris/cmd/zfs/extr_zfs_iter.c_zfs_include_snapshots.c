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
typedef  int /*<<< orphan*/  zpool_handle_t ;
typedef  int /*<<< orphan*/  zfs_handle_t ;
struct TYPE_3__ {int cb_flags; int cb_types; } ;
typedef  TYPE_1__ callback_data_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int ZFS_ITER_PROP_LISTSNAPS ; 
 int ZFS_TYPE_SNAPSHOT ; 
 int /*<<< orphan*/  ZPOOL_PROP_LISTSNAPS ; 
 int /*<<< orphan*/ * zfs_get_pool_handle (int /*<<< orphan*/ *) ; 
 int zpool_get_prop_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static boolean_t
zfs_include_snapshots(zfs_handle_t *zhp, callback_data_t *cb)
{
	zpool_handle_t *zph;

	if ((cb->cb_flags & ZFS_ITER_PROP_LISTSNAPS) == 0)
		return (cb->cb_types & ZFS_TYPE_SNAPSHOT);

	zph = zfs_get_pool_handle(zhp);
	return (zpool_get_prop_int(zph, ZPOOL_PROP_LISTSNAPS, NULL));
}