#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * zpool_hdl; } ;
typedef  TYPE_1__ zpool_handle_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EZFS_NODEVICE ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_INDIRECT_SIZE ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int zfs_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * zpool_find_vdev (TYPE_1__*,char const*,scalar_t__*,scalar_t__*,scalar_t__*) ; 

int
zpool_vdev_indirect_size(zpool_handle_t *zhp, const char *path,
    uint64_t *sizep)
{
	char msg[1024];
	nvlist_t *tgt;
	boolean_t avail_spare, l2cache, islog;
	libzfs_handle_t *hdl = zhp->zpool_hdl;

	(void) snprintf(msg, sizeof (msg),
	    dgettext(TEXT_DOMAIN, "cannot determine indirect size of %s"),
	    path);

	if ((tgt = zpool_find_vdev(zhp, path, &avail_spare, &l2cache,
	    &islog)) == NULL)
		return (zfs_error(hdl, EZFS_NODEVICE, msg));

	if (avail_spare || l2cache || islog) {
		*sizep = 0;
		return (0);
	}

	if (nvlist_lookup_uint64(tgt, ZPOOL_CONFIG_INDIRECT_SIZE, sizep) != 0) {
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
		    "indirect size not available"));
		return (zfs_error(hdl, EINVAL, msg));
	}
	return (0);
}