#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  zfs_props; int /*<<< orphan*/ * zpool_hdl; int /*<<< orphan*/  zfs_type; int /*<<< orphan*/  zfs_head_type; int /*<<< orphan*/  zfs_name; int /*<<< orphan*/  zfs_hdl; } ;
typedef  TYPE_1__ zfs_handle_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZFS_TYPE_BOOKMARK ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ nvlist_dup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/ * zpool_handle (TYPE_1__*) ; 

zfs_handle_t *
make_bookmark_handle(zfs_handle_t *parent, const char *path,
    nvlist_t *bmark_props)
{
	zfs_handle_t *zhp = calloc(sizeof (zfs_handle_t), 1);

	if (zhp == NULL)
		return (NULL);

	/* Fill in the name. */
	zhp->zfs_hdl = parent->zfs_hdl;
	(void) strlcpy(zhp->zfs_name, path, sizeof (zhp->zfs_name));

	/* Set the property lists. */
	if (nvlist_dup(bmark_props, &zhp->zfs_props, 0) != 0) {
		free(zhp);
		return (NULL);
	}

	/* Set the types. */
	zhp->zfs_head_type = parent->zfs_head_type;
	zhp->zfs_type = ZFS_TYPE_BOOKMARK;

	if ((zhp->zpool_hdl = zpool_handle(zhp)) == NULL) {
		nvlist_free(zhp->zfs_props);
		free(zhp);
		return (NULL);
	}

	return (zhp);
}