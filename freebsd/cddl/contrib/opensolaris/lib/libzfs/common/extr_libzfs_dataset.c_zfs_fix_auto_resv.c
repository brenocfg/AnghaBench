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
typedef  scalar_t__ zfs_prop_t ;
struct TYPE_6__ {int /*<<< orphan*/  zfs_hdl; } ;
typedef  TYPE_1__ zfs_handle_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 scalar_t__ UINT64_MAX ; 
 int /*<<< orphan*/  ZFS_IS_VOLUME (TYPE_1__*) ; 
 scalar_t__ ZFS_PROP_REFRESERVATION ; 
 scalar_t__ ZFS_PROP_VOLBLOCKSIZE ; 
 scalar_t__ ZFS_PROP_VOLSIZE ; 
 int /*<<< orphan*/  fnvlist_add_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  no_memory (int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_add_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  nvlist_remove_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_prop_get_int (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  zfs_prop_to_name (scalar_t__) ; 
 scalar_t__ zfs_which_resv_prop (TYPE_1__*,scalar_t__*) ; 
 scalar_t__ zvol_volsize_to_reservation (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zfs_fix_auto_resv(zfs_handle_t *zhp, nvlist_t *nvl)
{
	uint64_t volsize;
	uint64_t resvsize;
	zfs_prop_t prop;
	nvlist_t *props;

	if (!ZFS_IS_VOLUME(zhp)) {
		return (0);
	}

	if (zfs_which_resv_prop(zhp, &prop) != 0) {
		return (-1);
	}

	if (prop != ZFS_PROP_REFRESERVATION) {
		return (0);
	}

	if (nvlist_lookup_uint64(nvl, zfs_prop_to_name(prop), &resvsize) != 0) {
		/* No value being set, so it can't be "auto" */
		return (0);
	}
	if (resvsize != UINT64_MAX) {
		/* Being set to a value other than "auto" */
		return (0);
	}

	props = fnvlist_alloc();

	fnvlist_add_uint64(props, zfs_prop_to_name(ZFS_PROP_VOLBLOCKSIZE),
	    zfs_prop_get_int(zhp, ZFS_PROP_VOLBLOCKSIZE));

	if (nvlist_lookup_uint64(nvl, zfs_prop_to_name(ZFS_PROP_VOLSIZE),
	    &volsize) != 0) {
		volsize = zfs_prop_get_int(zhp, ZFS_PROP_VOLSIZE);
	}

	resvsize = zvol_volsize_to_reservation(volsize, props);
	fnvlist_free(props);

	(void) nvlist_remove_all(nvl, zfs_prop_to_name(prop));
	if (nvlist_add_uint64(nvl, zfs_prop_to_name(prop), resvsize) != 0) {
		(void) no_memory(zhp->zfs_hdl);
		return (-1);
	}
	return (1);
}