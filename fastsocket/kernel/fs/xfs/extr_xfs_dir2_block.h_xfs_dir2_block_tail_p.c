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
typedef  int /*<<< orphan*/  xfs_dir2_block_tail_t ;
typedef  int /*<<< orphan*/  xfs_dir2_block_t ;
struct xfs_mount {scalar_t__ m_dirblksize; } ;
typedef  scalar_t__ block ;

/* Variables and functions */

__attribute__((used)) static inline xfs_dir2_block_tail_t *
xfs_dir2_block_tail_p(struct xfs_mount *mp, xfs_dir2_block_t *block)
{
	return (((xfs_dir2_block_tail_t *)
		((char *)(block) + (mp)->m_dirblksize)) - 1);
}