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
typedef  scalar_t__ zoneid_t ;
typedef  int /*<<< orphan*/  (* zfs_iter_f ) (int /*<<< orphan*/ *,void*) ;
typedef  int /*<<< orphan*/  zfs_handle_t ;
typedef  int /*<<< orphan*/  tpool_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int boolean_t ;

/* Variables and functions */
 scalar_t__ GLOBAL_ZONEID ; 
 int /*<<< orphan*/  ZFS_PROP_ZONED ; 
 int /*<<< orphan*/ * getenv (char*) ; 
 scalar_t__ getzoneid () ; 
 int /*<<< orphan*/  mount_tp_nthr ; 
 int /*<<< orphan*/  mountpoint_cmp ; 
 int non_descendant_idx (int /*<<< orphan*/ **,size_t,int) ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ **,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tpool_create (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tpool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tpool_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_dispatch_mount (int /*<<< orphan*/ *,int /*<<< orphan*/ **,size_t,int,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *,void*),void*,int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_prop_get_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
zfs_foreach_mountpoint(libzfs_handle_t *hdl, zfs_handle_t **handles,
    size_t num_handles, zfs_iter_f func, void *data, boolean_t parallel)
{
	zoneid_t zoneid = getzoneid();

	/*
	 * The ZFS_SERIAL_MOUNT environment variable is an undocumented
	 * variable that can be used as a convenience to do a/b comparison
	 * of serial vs. parallel mounting.
	 */
	boolean_t serial_mount = !parallel ||
	    (getenv("ZFS_SERIAL_MOUNT") != NULL);

	/*
	 * Sort the datasets by mountpoint. See mountpoint_cmp for details
	 * of how these are sorted.
	 */
	qsort(handles, num_handles, sizeof (zfs_handle_t *), mountpoint_cmp);

	if (serial_mount) {
		for (int i = 0; i < num_handles; i++) {
			func(handles[i], data);
		}
		return;
	}

	/*
	 * Issue the callback function for each dataset using a parallel
	 * algorithm that uses a thread pool to manage threads.
	 */
	tpool_t *tp = tpool_create(1, mount_tp_nthr, 0, NULL);

	/*
	 * There may be multiple "top level" mountpoints outside of the pool's
	 * root mountpoint, e.g.: /foo /bar. Dispatch a mount task for each of
	 * these.
	 */
	for (int i = 0; i < num_handles;
	    i = non_descendant_idx(handles, num_handles, i)) {
		/*
		 * Since the mountpoints have been sorted so that the zoned
		 * filesystems are at the end, a zoned filesystem seen from
		 * the global zone means that we're done.
		 */
		if (zoneid == GLOBAL_ZONEID &&
		    zfs_prop_get_int(handles[i], ZFS_PROP_ZONED))
			break;
		zfs_dispatch_mount(hdl, handles, num_handles, i, func, data,
		    tp);
	}

	tpool_wait(tp);	/* wait for all scheduled mounts to complete */
	tpool_destroy(tp);
}