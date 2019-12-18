#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zfs_handle_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
struct TYPE_4__ {int /*<<< orphan*/  cb_defer_destroy; int /*<<< orphan*/  cb_nvl; } ;
typedef  TYPE_1__ destroy_cbdata_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  ZFS_TYPE_SNAPSHOT ; 
 int /*<<< orphan*/  destroy_callback ; 
 int /*<<< orphan*/  g_zfs ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ *) ; 
 int zfs_iter_dependents (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * zfs_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
destroy_clones(destroy_cbdata_t *cb)
{
	nvpair_t *pair;
	for (pair = nvlist_next_nvpair(cb->cb_nvl, NULL);
	    pair != NULL;
	    pair = nvlist_next_nvpair(cb->cb_nvl, pair)) {
		zfs_handle_t *zhp = zfs_open(g_zfs, nvpair_name(pair),
		    ZFS_TYPE_SNAPSHOT);
		if (zhp != NULL) {
			boolean_t defer = cb->cb_defer_destroy;
			int err = 0;

			/*
			 * We can't defer destroy non-snapshots, so set it to
			 * false while destroying the clones.
			 */
			cb->cb_defer_destroy = B_FALSE;
			err = zfs_iter_dependents(zhp, B_FALSE,
			    destroy_callback, cb);
			cb->cb_defer_destroy = defer;
			zfs_close(zhp);
			if (err != 0)
				return (err);
		}
	}
	return (0);
}