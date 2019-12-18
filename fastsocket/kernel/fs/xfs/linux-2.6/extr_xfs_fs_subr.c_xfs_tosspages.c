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
typedef  int xfs_off_t ;
typedef  int /*<<< orphan*/  xfs_inode_t ;
struct TYPE_2__ {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 TYPE_1__* VFS_I (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  truncate_inode_pages_range (int /*<<< orphan*/ ,int,int) ; 

void
xfs_tosspages(
	xfs_inode_t	*ip,
	xfs_off_t	first,
	xfs_off_t	last,
	int		fiopt)
{
	/* can't toss partial tail pages, so mask them out */
	last &= ~(PAGE_SIZE - 1);
	truncate_inode_pages_range(VFS_I(ip)->i_mapping, first, last - 1);
}