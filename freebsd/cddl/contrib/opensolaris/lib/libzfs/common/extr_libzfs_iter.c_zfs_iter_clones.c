#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int (* zfs_iter_f ) (TYPE_1__*,void*) ;
struct TYPE_7__ {int /*<<< orphan*/  zfs_hdl; } ;
typedef  TYPE_1__ zfs_handle_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int ZFS_TYPE_FILESYSTEM ; 
 int ZFS_TYPE_VOLUME ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zfs_get_clones_nvl (TYPE_1__*) ; 
 TYPE_1__* zfs_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
zfs_iter_clones(zfs_handle_t *zhp, zfs_iter_f func, void *data)
{
	nvlist_t *nvl = zfs_get_clones_nvl(zhp);
	nvpair_t *pair;

	if (nvl == NULL)
		return (0);

	for (pair = nvlist_next_nvpair(nvl, NULL); pair != NULL;
	    pair = nvlist_next_nvpair(nvl, pair)) {
		zfs_handle_t *clone = zfs_open(zhp->zfs_hdl, nvpair_name(pair),
		    ZFS_TYPE_FILESYSTEM | ZFS_TYPE_VOLUME);
		if (clone != NULL) {
			int err = func(clone, data);
			if (err != 0)
				return (err);
		}
	}
	return (0);
}