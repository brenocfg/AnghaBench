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
struct TYPE_6__ {int /*<<< orphan*/  zfs_props_table; int /*<<< orphan*/ * zfs_mntopts; int /*<<< orphan*/  zfs_hdl; int /*<<< orphan*/  zfs_mntcheck; int /*<<< orphan*/ * zfs_recvd_props; int /*<<< orphan*/ * zfs_user_props; int /*<<< orphan*/ * zfs_props; int /*<<< orphan*/  zfs_dmustats; int /*<<< orphan*/  zfs_head_type; int /*<<< orphan*/  zfs_type; int /*<<< orphan*/  zfs_name; int /*<<< orphan*/  zpool_hdl; } ;
typedef  TYPE_1__ zfs_handle_t ;

/* Variables and functions */
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  no_memory (int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_dup (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zfs_close (TYPE_1__*) ; 
 int /*<<< orphan*/ * zfs_strdup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

zfs_handle_t *
zfs_handle_dup(zfs_handle_t *zhp_orig)
{
	zfs_handle_t *zhp = calloc(sizeof (zfs_handle_t), 1);

	if (zhp == NULL)
		return (NULL);

	zhp->zfs_hdl = zhp_orig->zfs_hdl;
	zhp->zpool_hdl = zhp_orig->zpool_hdl;
	(void) strlcpy(zhp->zfs_name, zhp_orig->zfs_name,
	    sizeof (zhp->zfs_name));
	zhp->zfs_type = zhp_orig->zfs_type;
	zhp->zfs_head_type = zhp_orig->zfs_head_type;
	zhp->zfs_dmustats = zhp_orig->zfs_dmustats;
	if (zhp_orig->zfs_props != NULL) {
		if (nvlist_dup(zhp_orig->zfs_props, &zhp->zfs_props, 0) != 0) {
			(void) no_memory(zhp->zfs_hdl);
			zfs_close(zhp);
			return (NULL);
		}
	}
	if (zhp_orig->zfs_user_props != NULL) {
		if (nvlist_dup(zhp_orig->zfs_user_props,
		    &zhp->zfs_user_props, 0) != 0) {
			(void) no_memory(zhp->zfs_hdl);
			zfs_close(zhp);
			return (NULL);
		}
	}
	if (zhp_orig->zfs_recvd_props != NULL) {
		if (nvlist_dup(zhp_orig->zfs_recvd_props,
		    &zhp->zfs_recvd_props, 0)) {
			(void) no_memory(zhp->zfs_hdl);
			zfs_close(zhp);
			return (NULL);
		}
	}
	zhp->zfs_mntcheck = zhp_orig->zfs_mntcheck;
	if (zhp_orig->zfs_mntopts != NULL) {
		zhp->zfs_mntopts = zfs_strdup(zhp_orig->zfs_hdl,
		    zhp_orig->zfs_mntopts);
	}
	zhp->zfs_props_table = zhp_orig->zfs_props_table;
	return (zhp);
}