#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int zpool_config_size; void* zpool_state; int /*<<< orphan*/ * zpool_config; int /*<<< orphan*/ * zpool_old_config; TYPE_3__* zpool_hdl; int /*<<< orphan*/  zpool_name; } ;
typedef  TYPE_1__ zpool_handle_t ;
struct TYPE_14__ {int zc_cookie; int zc_nvlist_dst_size; int /*<<< orphan*/  zc_name; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ zfs_cmd_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_15__ {int /*<<< orphan*/  libzfs_fd; } ;
typedef  TYPE_3__ libzfs_handle_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 scalar_t__ EINVAL ; 
 scalar_t__ ENOENT ; 
 scalar_t__ ENOMEM ; 
 void* POOL_STATE_ACTIVE ; 
 void* POOL_STATE_UNAVAIL ; 
 int /*<<< orphan*/  ZFS_IOC_POOL_STATS ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_POOL_TXG ; 
 scalar_t__ errno ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verify (int) ; 
 scalar_t__ zcmd_alloc_dst_nvlist (TYPE_3__*,TYPE_2__*,int) ; 
 scalar_t__ zcmd_expand_dst_nvlist (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  zcmd_free_nvlists (TYPE_2__*) ; 
 scalar_t__ zcmd_read_dst_nvlist (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ **) ; 

int
zpool_refresh_stats(zpool_handle_t *zhp, boolean_t *missing)
{
	zfs_cmd_t zc = { 0 };
	int error;
	nvlist_t *config;
	libzfs_handle_t *hdl = zhp->zpool_hdl;

	*missing = B_FALSE;
	(void) strcpy(zc.zc_name, zhp->zpool_name);

	if (zhp->zpool_config_size == 0)
		zhp->zpool_config_size = 1 << 16;

	if (zcmd_alloc_dst_nvlist(hdl, &zc, zhp->zpool_config_size) != 0)
		return (-1);

	for (;;) {
		if (ioctl(zhp->zpool_hdl->libzfs_fd, ZFS_IOC_POOL_STATS,
		    &zc) == 0) {
			/*
			 * The real error is returned in the zc_cookie field.
			 */
			error = zc.zc_cookie;
			break;
		}

		if (errno == ENOMEM) {
			if (zcmd_expand_dst_nvlist(hdl, &zc) != 0) {
				zcmd_free_nvlists(&zc);
				return (-1);
			}
		} else {
			zcmd_free_nvlists(&zc);
			if (errno == ENOENT || errno == EINVAL)
				*missing = B_TRUE;
			zhp->zpool_state = POOL_STATE_UNAVAIL;
			return (0);
		}
	}

	if (zcmd_read_dst_nvlist(hdl, &zc, &config) != 0) {
		zcmd_free_nvlists(&zc);
		return (-1);
	}

	zcmd_free_nvlists(&zc);

	zhp->zpool_config_size = zc.zc_nvlist_dst_size;

	if (zhp->zpool_config != NULL) {
		uint64_t oldtxg, newtxg;

		verify(nvlist_lookup_uint64(zhp->zpool_config,
		    ZPOOL_CONFIG_POOL_TXG, &oldtxg) == 0);
		verify(nvlist_lookup_uint64(config,
		    ZPOOL_CONFIG_POOL_TXG, &newtxg) == 0);

		nvlist_free(zhp->zpool_old_config);

		if (oldtxg != newtxg) {
			nvlist_free(zhp->zpool_config);
			zhp->zpool_old_config = NULL;
		} else {
			zhp->zpool_old_config = zhp->zpool_config;
		}
	}

	zhp->zpool_config = config;
	if (error)
		zhp->zpool_state = POOL_STATE_UNAVAIL;
	else
		zhp->zpool_state = POOL_STATE_ACTIVE;

	return (0);
}