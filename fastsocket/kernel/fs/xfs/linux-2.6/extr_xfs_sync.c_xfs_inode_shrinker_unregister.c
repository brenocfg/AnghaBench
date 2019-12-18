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
struct xfs_mount {int /*<<< orphan*/  m_inode_shrink; } ;

/* Variables and functions */
 int /*<<< orphan*/  unregister_shrinker (int /*<<< orphan*/ *) ; 

void
xfs_inode_shrinker_unregister(
	struct xfs_mount	*mp)
{
	unregister_shrinker(&mp->m_inode_shrink);
}