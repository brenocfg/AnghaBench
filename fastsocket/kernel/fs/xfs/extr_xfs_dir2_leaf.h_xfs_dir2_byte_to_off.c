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
typedef  int /*<<< orphan*/  xfs_dir2_off_t ;
typedef  int /*<<< orphan*/  xfs_dir2_data_aoff_t ;
struct TYPE_2__ {int sb_blocklog; int sb_dirblklog; } ;
struct xfs_mount {TYPE_1__ m_sb; } ;
typedef  int /*<<< orphan*/  by ;

/* Variables and functions */

__attribute__((used)) static inline xfs_dir2_data_aoff_t
xfs_dir2_byte_to_off(struct xfs_mount *mp, xfs_dir2_off_t by)
{
	return (xfs_dir2_data_aoff_t)((by) & \
		((1 << ((mp)->m_sb.sb_blocklog + (mp)->m_sb.sb_dirblklog)) - 1));
}