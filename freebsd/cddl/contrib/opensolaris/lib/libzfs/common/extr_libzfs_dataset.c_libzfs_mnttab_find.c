#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct mnttab {char* mnt_special; int /*<<< orphan*/  mnt_fstype; int /*<<< orphan*/  member_0; } ;
struct TYPE_8__ {struct mnttab mtn_mt; } ;
typedef  TYPE_1__ mnttab_node_t ;
struct TYPE_9__ {int /*<<< orphan*/  libzfs_mnttab_cache_lock; int /*<<< orphan*/  libzfs_mnttab_cache; int /*<<< orphan*/  libzfs_mnttab; int /*<<< orphan*/  libzfs_mnttab_enable; } ;
typedef  TYPE_2__ libzfs_handle_t ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  MNTTYPE_ZFS ; 
 TYPE_1__* avl_find (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ avl_numnodes (int /*<<< orphan*/ *) ; 
 scalar_t__ getmntany (int /*<<< orphan*/ ,struct mnttab*,struct mnttab*) ; 
 int /*<<< orphan*/  libzfs_mnttab_fini (TYPE_2__*) ; 
 int /*<<< orphan*/  libzfs_mnttab_update (TYPE_2__*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ ) ; 

int
libzfs_mnttab_find(libzfs_handle_t *hdl, const char *fsname,
    struct mnttab *entry)
{
	mnttab_node_t find;
	mnttab_node_t *mtn;
	int ret = ENOENT;

	if (!hdl->libzfs_mnttab_enable) {
		struct mnttab srch = { 0 };

		if (avl_numnodes(&hdl->libzfs_mnttab_cache))
			libzfs_mnttab_fini(hdl);
		rewind(hdl->libzfs_mnttab);
		srch.mnt_special = (char *)fsname;
		srch.mnt_fstype = MNTTYPE_ZFS;
		if (getmntany(hdl->libzfs_mnttab, entry, &srch) == 0)
			return (0);
		else
			return (ENOENT);
	}

	pthread_mutex_lock(&hdl->libzfs_mnttab_cache_lock);
	if (avl_numnodes(&hdl->libzfs_mnttab_cache) == 0)
		libzfs_mnttab_update(hdl);

	find.mtn_mt.mnt_special = (char *)fsname;
	mtn = avl_find(&hdl->libzfs_mnttab_cache, &find, NULL);
	if (mtn) {
		*entry = mtn->mtn_mt;
		ret = 0;
	}
	pthread_mutex_unlock(&hdl->libzfs_mnttab_cache_lock);
	return (ret);
}