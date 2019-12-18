#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zfs_handle_t ;
struct get_clones_arg {scalar_t__ numclones; int /*<<< orphan*/  value; int /*<<< orphan*/  origin; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  ZFS_PROP_ORIGIN ; 
 int /*<<< orphan*/  fnvlist_add_boolean (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_get_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_iter_children (int /*<<< orphan*/ *,int (*) (int /*<<< orphan*/ *,void*),struct get_clones_arg*) ; 
 scalar_t__ zfs_prop_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
get_clones_cb(zfs_handle_t *zhp, void *arg)
{
	struct get_clones_arg *gca = arg;

	if (gca->numclones == 0) {
		zfs_close(zhp);
		return (0);
	}

	if (zfs_prop_get(zhp, ZFS_PROP_ORIGIN, gca->buf, sizeof (gca->buf),
	    NULL, NULL, 0, B_TRUE) != 0)
		goto out;
	if (strcmp(gca->buf, gca->origin) == 0) {
		fnvlist_add_boolean(gca->value, zfs_get_name(zhp));
		gca->numclones--;
	}

out:
	(void) zfs_iter_children(zhp, get_clones_cb, gca);
	zfs_close(zhp);
	return (0);
}