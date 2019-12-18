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
 int LLONG_MAX ; 
 TYPE_1__* VFS_I (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XFS_ITRUNCATED ; 
 int filemap_write_and_wait_range (struct address_space*,int,int) ; 
 int /*<<< orphan*/  trace_xfs_pagecache_inval (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  truncate_inode_pages_range (struct address_space*,int,int) ; 
 int /*<<< orphan*/  xfs_iflags_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
xfs_flushinval_pages(
	xfs_inode_t	*ip,
	xfs_off_t	first,
	xfs_off_t	last,
	int		fiopt)
{
	struct address_space *mapping = VFS_I(ip)->i_mapping;
	int		ret = 0;

	trace_xfs_pagecache_inval(ip, first, last);

	xfs_iflags_clear(ip, XFS_ITRUNCATED);
	ret = filemap_write_and_wait_range(mapping, first,
				last == -1 ? LLONG_MAX : last);
	if (!ret)
		truncate_inode_pages_range(mapping, first, last);
	return -ret;
}