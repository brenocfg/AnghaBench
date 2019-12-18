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
struct TYPE_2__ {int /*<<< orphan*/  seeks; int /*<<< orphan*/  shrink; } ;
struct xfs_mount {TYPE_1__ m_inode_shrink; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_SEEKS ; 
 int /*<<< orphan*/  register_shrinker (TYPE_1__*) ; 
 int /*<<< orphan*/  xfs_reclaim_inode_shrink ; 

void
xfs_inode_shrinker_register(
	struct xfs_mount	*mp)
{
	mp->m_inode_shrink.shrink = xfs_reclaim_inode_shrink;
	mp->m_inode_shrink.seeks = DEFAULT_SEEKS;
	register_shrinker(&mp->m_inode_shrink);
}