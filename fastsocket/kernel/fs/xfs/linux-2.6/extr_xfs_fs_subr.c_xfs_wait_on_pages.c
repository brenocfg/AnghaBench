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
struct address_space {int dummy; } ;
struct TYPE_2__ {struct address_space* i_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGECACHE_TAG_WRITEBACK ; 
 TYPE_1__* VFS_I (int /*<<< orphan*/ *) ; 
 int XFS_ISIZE (int /*<<< orphan*/ *) ; 
 int filemap_fdatawait_range (struct address_space*,int,int) ; 
 scalar_t__ mapping_tagged (struct address_space*,int /*<<< orphan*/ ) ; 

int
xfs_wait_on_pages(
	xfs_inode_t	*ip,
	xfs_off_t	first,
	xfs_off_t	last)
{
	struct address_space *mapping = VFS_I(ip)->i_mapping;

	if (mapping_tagged(mapping, PAGECACHE_TAG_WRITEBACK)) {
		return -filemap_fdatawait_range(mapping, first,
					last == -1 ? XFS_ISIZE(ip) - 1 : last);
	}
	return 0;
}