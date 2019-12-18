#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int zc_nvlist_conf_size; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_15__ {int /*<<< orphan*/  libzfs_fd; } ;
typedef  TYPE_2__ libzfs_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_BUF_MINSIZE ; 
 scalar_t__ ENOMEM ; 
 int MAX (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ZFS_IOC_POOL_TRYIMPORT ; 
 scalar_t__ errno ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ zcmd_alloc_dst_nvlist (TYPE_2__*,TYPE_1__*,int) ; 
 scalar_t__ zcmd_expand_dst_nvlist (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  zcmd_free_nvlists (TYPE_1__*) ; 
 scalar_t__ zcmd_read_dst_nvlist (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ **) ; 
 scalar_t__ zcmd_write_conf_nvlist (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static nvlist_t *
refresh_config(libzfs_handle_t *hdl, nvlist_t *config)
{
	nvlist_t *nvl;
	zfs_cmd_t zc = { 0 };
	int err, dstbuf_size;

	if (zcmd_write_conf_nvlist(hdl, &zc, config) != 0)
		return (NULL);

	dstbuf_size = MAX(CONFIG_BUF_MINSIZE, zc.zc_nvlist_conf_size * 4);

	if (zcmd_alloc_dst_nvlist(hdl, &zc, dstbuf_size) != 0) {
		zcmd_free_nvlists(&zc);
		return (NULL);
	}

	while ((err = ioctl(hdl->libzfs_fd, ZFS_IOC_POOL_TRYIMPORT,
	    &zc)) != 0 && errno == ENOMEM) {
		if (zcmd_expand_dst_nvlist(hdl, &zc) != 0) {
			zcmd_free_nvlists(&zc);
			return (NULL);
		}
	}

	if (err) {
		zcmd_free_nvlists(&zc);
		return (NULL);
	}

	if (zcmd_read_dst_nvlist(hdl, &zc, &nvl) != 0) {
		zcmd_free_nvlists(&zc);
		return (NULL);
	}

	zcmd_free_nvlists(&zc);
	return (nvl);
}