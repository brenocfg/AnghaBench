#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_3__* i_itemp; } ;
typedef  TYPE_1__ xfs_inode_t ;
struct TYPE_5__ {scalar_t__ ili_root_size; int /*<<< orphan*/  ili_orig_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_zone_free (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  xfs_ili_zone ; 

void
xfs_inode_item_destroy(
	xfs_inode_t	*ip)
{
#ifdef XFS_TRANS_DEBUG
	if (ip->i_itemp->ili_root_size != 0) {
		kmem_free(ip->i_itemp->ili_orig_root);
	}
#endif
	kmem_zone_free(xfs_ili_zone, ip->i_itemp);
}