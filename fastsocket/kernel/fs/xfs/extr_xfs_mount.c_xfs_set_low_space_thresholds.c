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
struct TYPE_2__ {int sb_dblocks; } ;
struct xfs_mount {int* m_low_space; TYPE_1__ m_sb; } ;
typedef  int __uint64_t ;

/* Variables and functions */
 int XFS_LOWSP_MAX ; 
 int /*<<< orphan*/  do_div (int,int) ; 

void
xfs_set_low_space_thresholds(
	struct xfs_mount	*mp)
{
	int i;

	for (i = 0; i < XFS_LOWSP_MAX; i++) {
		__uint64_t space = mp->m_sb.sb_dblocks;

		do_div(space, 100);
		mp->m_low_space[i] = space * (i + 1);
	}
}