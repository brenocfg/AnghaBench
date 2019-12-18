#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ zfs_type; int /*<<< orphan*/ * zfs_props; int /*<<< orphan*/  zfs_hdl; int /*<<< orphan*/  zfs_name; } ;
typedef  TYPE_1__ zfs_handle_t ;
struct get_clones_arg {scalar_t__ numclones; int /*<<< orphan*/  origin; int /*<<< orphan*/ * value; } ;
typedef  int /*<<< orphan*/  pool ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  NV_UNIQUE_NAME ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  ZFS_PROP_CLONES ; 
 int /*<<< orphan*/  ZFS_PROP_NUMCLONES ; 
 int /*<<< orphan*/  ZFS_TYPE_FILESYSTEM ; 
 scalar_t__ ZFS_TYPE_SNAPSHOT ; 
 int /*<<< orphan*/  ZPROP_VALUE ; 
 int /*<<< orphan*/  get_clones_cb (TYPE_1__*,struct get_clones_arg*) ; 
 scalar_t__ nvlist_add_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_alloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_lookup_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strsep (char**,char*) ; 
 int /*<<< orphan*/  verify (int) ; 
 TYPE_1__* zfs_open (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_prop_get_int (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_prop_to_name (int /*<<< orphan*/ ) ; 

nvlist_t *
zfs_get_clones_nvl(zfs_handle_t *zhp)
{
	nvlist_t *nv, *value;

	if (nvlist_lookup_nvlist(zhp->zfs_props,
	    zfs_prop_to_name(ZFS_PROP_CLONES), &nv) != 0) {
		struct get_clones_arg gca;

		/*
		 * if this is a snapshot, then the kernel wasn't able
		 * to get the clones.  Do it by slowly iterating.
		 */
		if (zhp->zfs_type != ZFS_TYPE_SNAPSHOT)
			return (NULL);
		if (nvlist_alloc(&nv, NV_UNIQUE_NAME, 0) != 0)
			return (NULL);
		if (nvlist_alloc(&value, NV_UNIQUE_NAME, 0) != 0) {
			nvlist_free(nv);
			return (NULL);
		}

		gca.numclones = zfs_prop_get_int(zhp, ZFS_PROP_NUMCLONES);
		gca.value = value;
		gca.origin = zhp->zfs_name;

		if (gca.numclones != 0) {
			zfs_handle_t *root;
			char pool[ZFS_MAX_DATASET_NAME_LEN];
			char *cp = pool;

			/* get the pool name */
			(void) strlcpy(pool, zhp->zfs_name, sizeof (pool));
			(void) strsep(&cp, "/@");
			root = zfs_open(zhp->zfs_hdl, pool,
			    ZFS_TYPE_FILESYSTEM);

			(void) get_clones_cb(root, &gca);
		}

		if (gca.numclones != 0 ||
		    nvlist_add_nvlist(nv, ZPROP_VALUE, value) != 0 ||
		    nvlist_add_nvlist(zhp->zfs_props,
		    zfs_prop_to_name(ZFS_PROP_CLONES), nv) != 0) {
			nvlist_free(nv);
			nvlist_free(value);
			return (NULL);
		}
		nvlist_free(nv);
		nvlist_free(value);
		verify(0 == nvlist_lookup_nvlist(zhp->zfs_props,
		    zfs_prop_to_name(ZFS_PROP_CLONES), &nv));
	}

	verify(nvlist_lookup_nvlist(nv, ZPROP_VALUE, &value) == 0);

	return (value);
}