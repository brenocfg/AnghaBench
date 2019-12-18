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
struct TYPE_9__ {void* mnt_mntopts; void* mnt_fstype; void* mnt_mountp; void* mnt_special; } ;
struct TYPE_10__ {TYPE_1__ mtn_mt; } ;
typedef  TYPE_2__ mnttab_node_t ;
struct TYPE_11__ {int /*<<< orphan*/  libzfs_mnttab_cache_lock; int /*<<< orphan*/  libzfs_mnttab_cache; } ;
typedef  TYPE_3__ libzfs_handle_t ;

/* Variables and functions */
 char const* MNTTYPE_ZFS ; 
 int /*<<< orphan*/  avl_add (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ avl_numnodes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__* zfs_alloc (TYPE_3__*,int) ; 
 void* zfs_strdup (TYPE_3__*,char const*) ; 

void
libzfs_mnttab_add(libzfs_handle_t *hdl, const char *special,
    const char *mountp, const char *mntopts)
{
	mnttab_node_t *mtn;

	pthread_mutex_lock(&hdl->libzfs_mnttab_cache_lock);
	if (avl_numnodes(&hdl->libzfs_mnttab_cache) == 0) {
		mtn = zfs_alloc(hdl, sizeof (mnttab_node_t));
		mtn->mtn_mt.mnt_special = zfs_strdup(hdl, special);
		mtn->mtn_mt.mnt_mountp = zfs_strdup(hdl, mountp);
		mtn->mtn_mt.mnt_fstype = zfs_strdup(hdl, MNTTYPE_ZFS);
		mtn->mtn_mt.mnt_mntopts = zfs_strdup(hdl, mntopts);
		avl_add(&hdl->libzfs_mnttab_cache, mtn);
	}
	pthread_mutex_unlock(&hdl->libzfs_mnttab_cache_lock);
}