#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* dds_origin; } ;
struct TYPE_5__ {TYPE_1__ zfs_dmustats; int /*<<< orphan*/  zfs_name; int /*<<< orphan*/  zfs_type; int /*<<< orphan*/ * zfs_hdl; } ;
typedef  TYPE_2__ zfs_handle_t ;
typedef  int /*<<< orphan*/  snapname ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int /*<<< orphan*/  errbuf ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
#define  EEXIST 128 
 int /*<<< orphan*/  EZFS_BADTYPE ; 
 int /*<<< orphan*/  EZFS_EXISTS ; 
 int /*<<< orphan*/  EZFS_INVALIDNAME ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  ZFS_TYPE_SNAPSHOT ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 int lzc_promote (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int zfs_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ *,char*,...) ; 
 int zfs_standard_error (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  zfs_validate_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
zfs_promote(zfs_handle_t *zhp)
{
	libzfs_handle_t *hdl = zhp->zfs_hdl;
	char snapname[ZFS_MAX_DATASET_NAME_LEN];
	int ret;
	char errbuf[1024];

	(void) snprintf(errbuf, sizeof (errbuf), dgettext(TEXT_DOMAIN,
	    "cannot promote '%s'"), zhp->zfs_name);

	if (zhp->zfs_type == ZFS_TYPE_SNAPSHOT) {
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
		    "snapshots can not be promoted"));
		return (zfs_error(hdl, EZFS_BADTYPE, errbuf));
	}

	if (zhp->zfs_dmustats.dds_origin[0] == '\0') {
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
		    "not a cloned filesystem"));
		return (zfs_error(hdl, EZFS_BADTYPE, errbuf));
	}

	if (!zfs_validate_name(hdl, zhp->zfs_name, zhp->zfs_type, B_TRUE))
		return (zfs_error(hdl, EZFS_INVALIDNAME, errbuf));

	ret = lzc_promote(zhp->zfs_name, snapname, sizeof (snapname));

	if (ret != 0) {
		switch (ret) {
		case EEXIST:
			/* There is a conflicting snapshot name. */
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "conflicting snapshot '%s' from parent '%s'"),
			    snapname, zhp->zfs_dmustats.dds_origin);
			return (zfs_error(hdl, EZFS_EXISTS, errbuf));

		default:
			return (zfs_standard_error(hdl, ret, errbuf));
		}
	}
	return (ret);
}