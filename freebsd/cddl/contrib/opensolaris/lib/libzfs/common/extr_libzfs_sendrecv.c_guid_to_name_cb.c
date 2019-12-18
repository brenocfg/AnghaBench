#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  zfs_name; } ;
typedef  TYPE_1__ zfs_handle_t ;
struct TYPE_13__ {scalar_t__ guid; scalar_t__ bookmark_ok; int /*<<< orphan*/  name; int /*<<< orphan*/ * skip; } ;
typedef  TYPE_2__ guid_to_name_data_t ;

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/  ZFS_PROP_GUID ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strrchr (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  zfs_close (TYPE_1__*) ; 
 int zfs_iter_bookmarks (TYPE_1__*,int (*) (TYPE_1__*,void*),TYPE_2__*) ; 
 int zfs_iter_children (TYPE_1__*,int (*) (TYPE_1__*,void*),TYPE_2__*) ; 
 scalar_t__ zfs_prop_get_int (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
guid_to_name_cb(zfs_handle_t *zhp, void *arg)
{
	guid_to_name_data_t *gtnd = arg;
	const char *slash;
	int err;

	if (gtnd->skip != NULL &&
	    (slash = strrchr(zhp->zfs_name, '/')) != NULL &&
	    strcmp(slash + 1, gtnd->skip) == 0) {
		zfs_close(zhp);
		return (0);
	}

	if (zfs_prop_get_int(zhp, ZFS_PROP_GUID) == gtnd->guid) {
		(void) strcpy(gtnd->name, zhp->zfs_name);
		zfs_close(zhp);
		return (EEXIST);
	}

	err = zfs_iter_children(zhp, guid_to_name_cb, gtnd);
	if (err != EEXIST && gtnd->bookmark_ok)
		err = zfs_iter_bookmarks(zhp, guid_to_name_cb, gtnd);
	zfs_close(zhp);
	return (err);
}