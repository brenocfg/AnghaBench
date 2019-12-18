#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  cn_handle; } ;
typedef  TYPE_1__ prop_changenode_t ;
typedef  int /*<<< orphan*/  mountb ;
typedef  int /*<<< orphan*/  mounta ;
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  ZFS_PROP_MOUNTPOINT ; 
 int strcmp (char*,char*) ; 
 scalar_t__ zfs_prop_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
compare_mountpoints(const void *a, const void *b, void *unused)
{
	const prop_changenode_t *ca = a;
	const prop_changenode_t *cb = b;

	char mounta[MAXPATHLEN];
	char mountb[MAXPATHLEN];

	boolean_t hasmounta, hasmountb;

	/*
	 * When unsharing or unmounting filesystems, we need to do it in
	 * mountpoint order.  This allows the user to have a mountpoint
	 * hierarchy that is different from the dataset hierarchy, and still
	 * allow it to be changed.  However, if either dataset doesn't have a
	 * mountpoint (because it is a volume or a snapshot), we place it at the
	 * end of the list, because it doesn't affect our change at all.
	 */
	hasmounta = (zfs_prop_get(ca->cn_handle, ZFS_PROP_MOUNTPOINT, mounta,
	    sizeof (mounta), NULL, NULL, 0, B_FALSE) == 0);
	hasmountb = (zfs_prop_get(cb->cn_handle, ZFS_PROP_MOUNTPOINT, mountb,
	    sizeof (mountb), NULL, NULL, 0, B_FALSE) == 0);

	if (!hasmounta && hasmountb)
		return (-1);
	else if (hasmounta && !hasmountb)
		return (1);
	else if (!hasmounta && !hasmountb)
		return (0);
	else
		return (strcmp(mountb, mounta));
}