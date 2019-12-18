#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zfs_handle_t ;
struct TYPE_2__ {int /*<<< orphan*/  cb_defer_destroy; scalar_t__ cb_force; int /*<<< orphan*/  cb_batchedsnaps; scalar_t__ cb_dryrun; scalar_t__ cb_parsable; scalar_t__ cb_verbose; } ;
typedef  TYPE_1__ destroy_cbdata_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  MS_FORCE ; 
 scalar_t__ ZFS_TYPE_FILESYSTEM ; 
 scalar_t__ ZFS_TYPE_SNAPSHOT ; 
 int /*<<< orphan*/  fnvlist_add_boolean (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  fnvlist_alloc () ; 
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_zfs ; 
 char* gettext (char*) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int zfs_destroy_snaps_nvl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* zfs_get_name (int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_get_type (int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_unmount (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
destroy_callback(zfs_handle_t *zhp, void *data)
{
	destroy_cbdata_t *cb = data;
	const char *name = zfs_get_name(zhp);

	if (cb->cb_verbose) {
		if (cb->cb_parsable) {
			(void) printf("destroy\t%s\n", name);
		} else if (cb->cb_dryrun) {
			(void) printf(gettext("would destroy %s\n"),
			    name);
		} else {
			(void) printf(gettext("will destroy %s\n"),
			    name);
		}
	}

	/*
	 * Ignore pools (which we've already flagged as an error before getting
	 * here).
	 */
	if (strchr(zfs_get_name(zhp), '/') == NULL &&
	    zfs_get_type(zhp) == ZFS_TYPE_FILESYSTEM) {
		zfs_close(zhp);
		return (0);
	}
	if (cb->cb_dryrun) {
		zfs_close(zhp);
		return (0);
	}

	/*
	 * We batch up all contiguous snapshots (even of different
	 * filesystems) and destroy them with one ioctl.  We can't
	 * simply do all snap deletions and then all fs deletions,
	 * because we must delete a clone before its origin.
	 */
	if (zfs_get_type(zhp) == ZFS_TYPE_SNAPSHOT) {
		fnvlist_add_boolean(cb->cb_batchedsnaps, name);
	} else {
		int error = zfs_destroy_snaps_nvl(g_zfs,
		    cb->cb_batchedsnaps, B_FALSE);
		fnvlist_free(cb->cb_batchedsnaps);
		cb->cb_batchedsnaps = fnvlist_alloc();

		if (error != 0 ||
		    zfs_unmount(zhp, NULL, cb->cb_force ? MS_FORCE : 0) != 0 ||
		    zfs_destroy(zhp, cb->cb_defer_destroy) != 0) {
			zfs_close(zhp);
			return (-1);
		}
	}

	zfs_close(zhp);
	return (0);
}