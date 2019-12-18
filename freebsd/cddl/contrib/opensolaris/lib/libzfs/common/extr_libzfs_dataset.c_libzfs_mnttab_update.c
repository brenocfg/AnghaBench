#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct mnttab {int /*<<< orphan*/  mnt_mntopts; int /*<<< orphan*/  mnt_fstype; int /*<<< orphan*/  mnt_mountp; int /*<<< orphan*/  mnt_special; } ;
struct TYPE_9__ {void* mnt_mntopts; void* mnt_fstype; void* mnt_mountp; void* mnt_special; } ;
struct TYPE_10__ {TYPE_1__ mtn_mt; } ;
typedef  TYPE_2__ mnttab_node_t ;
struct TYPE_11__ {int /*<<< orphan*/  libzfs_mnttab_cache; int /*<<< orphan*/  libzfs_mnttab; } ;
typedef  TYPE_3__ libzfs_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  MNTTYPE_ZFS ; 
 int /*<<< orphan*/  avl_add (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ getmntent (int /*<<< orphan*/ ,struct mnttab*) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* zfs_alloc (TYPE_3__*,int) ; 
 void* zfs_strdup (TYPE_3__*,int /*<<< orphan*/ ) ; 

void
libzfs_mnttab_update(libzfs_handle_t *hdl)
{
	struct mnttab entry;

	rewind(hdl->libzfs_mnttab);
	while (getmntent(hdl->libzfs_mnttab, &entry) == 0) {
		mnttab_node_t *mtn;

		if (strcmp(entry.mnt_fstype, MNTTYPE_ZFS) != 0)
			continue;
		mtn = zfs_alloc(hdl, sizeof (mnttab_node_t));
		mtn->mtn_mt.mnt_special = zfs_strdup(hdl, entry.mnt_special);
		mtn->mtn_mt.mnt_mountp = zfs_strdup(hdl, entry.mnt_mountp);
		mtn->mtn_mt.mnt_fstype = zfs_strdup(hdl, entry.mnt_fstype);
		mtn->mtn_mt.mnt_mntopts = zfs_strdup(hdl, entry.mnt_mntopts);
		avl_add(&hdl->libzfs_mnttab_cache, mtn);
	}
}