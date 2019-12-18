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
typedef  int /*<<< orphan*/  zfs_type_t ;
struct TYPE_6__ {scalar_t__ zfs_type; int /*<<< orphan*/ * zfs_hdl; int /*<<< orphan*/  zfs_name; int /*<<< orphan*/  zpool_hdl; } ;
typedef  TYPE_1__ zfs_handle_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  parent ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int /*<<< orphan*/  errbuf ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
#define  ENOENT 129 
#define  EXDEV 128 
 int /*<<< orphan*/  EZFS_CROSSTARGET ; 
 int /*<<< orphan*/  EZFS_INVALIDNAME ; 
 int /*<<< orphan*/  EZFS_NOENT ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 scalar_t__ ZFS_IS_VOLUME (TYPE_1__*) ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  ZFS_TYPE_FILESYSTEM ; 
 scalar_t__ ZFS_TYPE_SNAPSHOT ; 
 int /*<<< orphan*/  ZFS_TYPE_VOLUME ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ check_parents (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 int errno ; 
 int lzc_clone (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parent_name (char const*,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int zfs_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ *,char*,...) ; 
 int zfs_fix_auto_resv (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int zfs_standard_error (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/ * zfs_valid_proplist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_validate_name (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
zfs_clone(zfs_handle_t *zhp, const char *target, nvlist_t *props)
{
	char parent[ZFS_MAX_DATASET_NAME_LEN];
	int ret;
	char errbuf[1024];
	libzfs_handle_t *hdl = zhp->zfs_hdl;
	uint64_t zoned;

	assert(zhp->zfs_type == ZFS_TYPE_SNAPSHOT);

	(void) snprintf(errbuf, sizeof (errbuf), dgettext(TEXT_DOMAIN,
	    "cannot create '%s'"), target);

	/* validate the target/clone name */
	if (!zfs_validate_name(hdl, target, ZFS_TYPE_FILESYSTEM, B_TRUE))
		return (zfs_error(hdl, EZFS_INVALIDNAME, errbuf));

	/* validate parents exist */
	if (check_parents(hdl, target, &zoned, B_FALSE, NULL) != 0)
		return (-1);

	(void) parent_name(target, parent, sizeof (parent));

	/* do the clone */

	if (props) {
		zfs_type_t type;

		if (ZFS_IS_VOLUME(zhp)) {
			type = ZFS_TYPE_VOLUME;
		} else {
			type = ZFS_TYPE_FILESYSTEM;
		}
		if ((props = zfs_valid_proplist(hdl, type, props, zoned,
		    zhp, zhp->zpool_hdl, errbuf)) == NULL)
			return (-1);
		if (zfs_fix_auto_resv(zhp, props) == -1) {
			nvlist_free(props);
			return (-1);
		}
	}

	ret = lzc_clone(target, zhp->zfs_name, props);
	nvlist_free(props);

	if (ret != 0) {
		switch (errno) {

		case ENOENT:
			/*
			 * The parent doesn't exist.  We should have caught this
			 * above, but there may a race condition that has since
			 * destroyed the parent.
			 *
			 * At this point, we don't know whether it's the source
			 * that doesn't exist anymore, or whether the target
			 * dataset doesn't exist.
			 */
			zfs_error_aux(zhp->zfs_hdl, dgettext(TEXT_DOMAIN,
			    "no such parent '%s'"), parent);
			return (zfs_error(zhp->zfs_hdl, EZFS_NOENT, errbuf));

		case EXDEV:
			zfs_error_aux(zhp->zfs_hdl, dgettext(TEXT_DOMAIN,
			    "source and target pools differ"));
			return (zfs_error(zhp->zfs_hdl, EZFS_CROSSTARGET,
			    errbuf));

		default:
			return (zfs_standard_error(zhp->zfs_hdl, errno,
			    errbuf));
		}
	}

	return (ret);
}