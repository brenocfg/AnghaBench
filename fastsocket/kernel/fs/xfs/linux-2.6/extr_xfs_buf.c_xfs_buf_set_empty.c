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
struct xfs_buf {size_t b_buffer_length; size_t b_count_desired; int /*<<< orphan*/  b_flags; int /*<<< orphan*/  b_bn; scalar_t__ b_file_offset; int /*<<< orphan*/ * b_addr; scalar_t__ b_page_count; int /*<<< orphan*/ * b_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  XBF_MAPPED ; 
 int /*<<< orphan*/  XFS_BUF_DADDR_NULL ; 
 int /*<<< orphan*/  _xfs_buf_free_pages (struct xfs_buf*) ; 

void
xfs_buf_set_empty(
	struct xfs_buf		*bp,
	size_t			len)
{
	if (bp->b_pages)
		_xfs_buf_free_pages(bp);

	bp->b_pages = NULL;
	bp->b_page_count = 0;
	bp->b_addr = NULL;
	bp->b_file_offset = 0;
	bp->b_buffer_length = bp->b_count_desired = len;
	bp->b_bn = XFS_BUF_DADDR_NULL;
	bp->b_flags &= ~XBF_MAPPED;
}