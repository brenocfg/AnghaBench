#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* zpool_name; TYPE_4__* zpool_hdl; } ;
typedef  TYPE_1__ zpool_handle_t ;
struct TYPE_7__ {char* zc_name; char* zc_value; scalar_t__ zc_obj; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ zfs_cmd_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  dsname ;
typedef  scalar_t__ boolean_t ;
struct TYPE_8__ {int /*<<< orphan*/  libzfs_fd; } ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 int /*<<< orphan*/  ZFS_IOC_DSOBJ_TO_DSNAME ; 
 int /*<<< orphan*/  ZFS_IOC_OBJ_TO_PATH ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ is_mounted (TYPE_4__*,char*,char**) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*,...) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 

void
zpool_obj_to_path(zpool_handle_t *zhp, uint64_t dsobj, uint64_t obj,
    char *pathname, size_t len)
{
	zfs_cmd_t zc = { 0 };
	boolean_t mounted = B_FALSE;
	char *mntpnt = NULL;
	char dsname[ZFS_MAX_DATASET_NAME_LEN];

	if (dsobj == 0) {
		/* special case for the MOS */
		(void) snprintf(pathname, len, "<metadata>:<0x%llx>", obj);
		return;
	}

	/* get the dataset's name */
	(void) strlcpy(zc.zc_name, zhp->zpool_name, sizeof (zc.zc_name));
	zc.zc_obj = dsobj;
	if (ioctl(zhp->zpool_hdl->libzfs_fd,
	    ZFS_IOC_DSOBJ_TO_DSNAME, &zc) != 0) {
		/* just write out a path of two object numbers */
		(void) snprintf(pathname, len, "<0x%llx>:<0x%llx>",
		    dsobj, obj);
		return;
	}
	(void) strlcpy(dsname, zc.zc_value, sizeof (dsname));

	/* find out if the dataset is mounted */
	mounted = is_mounted(zhp->zpool_hdl, dsname, &mntpnt);

	/* get the corrupted object's path */
	(void) strlcpy(zc.zc_name, dsname, sizeof (zc.zc_name));
	zc.zc_obj = obj;
	if (ioctl(zhp->zpool_hdl->libzfs_fd, ZFS_IOC_OBJ_TO_PATH,
	    &zc) == 0) {
		if (mounted) {
			(void) snprintf(pathname, len, "%s%s", mntpnt,
			    zc.zc_value);
		} else {
			(void) snprintf(pathname, len, "%s:%s",
			    dsname, zc.zc_value);
		}
	} else {
		(void) snprintf(pathname, len, "%s:<0x%llx>", dsname, obj);
	}
	free(mntpnt);
}