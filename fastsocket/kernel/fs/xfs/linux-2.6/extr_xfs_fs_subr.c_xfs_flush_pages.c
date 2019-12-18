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
typedef  int uint64_t ;
struct address_space {int dummy; } ;
struct TYPE_2__ {struct address_space* i_mapping; } ;

/* Variables and functions */
 int LLONG_MAX ; 
 TYPE_1__* VFS_I (int /*<<< orphan*/ *) ; 
 int XBF_ASYNC ; 
 int /*<<< orphan*/  XFS_ITRUNCATED ; 
 int filemap_fdatawrite_range (struct address_space*,int,int) ; 
 int /*<<< orphan*/  xfs_iflags_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int xfs_wait_on_pages (int /*<<< orphan*/ *,int,int) ; 

int
xfs_flush_pages(
	xfs_inode_t	*ip,
	xfs_off_t	first,
	xfs_off_t	last,
	uint64_t	flags,
	int		fiopt)
{
	struct address_space *mapping = VFS_I(ip)->i_mapping;
	int		ret = 0;
	int		ret2;

	xfs_iflags_clear(ip, XFS_ITRUNCATED);
	ret = -filemap_fdatawrite_range(mapping, first,
				last == -1 ? LLONG_MAX : last);
	if (flags & XBF_ASYNC)
		return ret;
	ret2 = xfs_wait_on_pages(ip, first, last);
	if (!ret)
		ret = ret2;
	return ret;
}