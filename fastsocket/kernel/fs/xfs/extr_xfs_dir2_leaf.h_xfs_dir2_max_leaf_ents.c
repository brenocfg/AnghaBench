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
typedef  int /*<<< orphan*/  xfs_dir2_leaf_hdr_t ;
typedef  int /*<<< orphan*/  xfs_dir2_leaf_entry_t ;
typedef  int uint ;
struct xfs_mount {int m_dirblksize; } ;

/* Variables and functions */

__attribute__((used)) static inline int xfs_dir2_max_leaf_ents(struct xfs_mount *mp)
{
	return (int)(((mp)->m_dirblksize - (uint)sizeof(xfs_dir2_leaf_hdr_t)) /
	       (uint)sizeof(xfs_dir2_leaf_entry_t));
}