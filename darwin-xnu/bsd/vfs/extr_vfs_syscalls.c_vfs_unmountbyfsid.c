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
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  scalar_t__ mount_t ;
typedef  int /*<<< orphan*/  fsid_t ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  mount_iterdrop (scalar_t__) ; 
 scalar_t__ mount_list_lookupby_fsid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mount_ref (scalar_t__,int /*<<< orphan*/ ) ; 
 int safedounmount (scalar_t__,int,int /*<<< orphan*/ ) ; 

int
vfs_unmountbyfsid(fsid_t *fsid, int flags, vfs_context_t ctx)
{
	mount_t mp;

	mp = mount_list_lookupby_fsid(fsid, 0, 1);
	if (mp == (mount_t)0) {
		return(ENOENT);
	}
	mount_ref(mp, 0);
	mount_iterdrop(mp);
	/* safedounmount consumes the mount ref */
	return(safedounmount(mp, flags, ctx));
}