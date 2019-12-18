#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ xfs_caddr_t ;
struct TYPE_4__ {int b_flags; struct page** b_pages; scalar_t__ b_offset; } ;
typedef  TYPE_1__ xfs_buf_t ;
struct page {int dummy; } ;

/* Variables and functions */
 size_t PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int XBF_MAPPED ; 
 scalar_t__ XFS_BUF_PTR (TYPE_1__*) ; 
 scalar_t__ page_address (struct page*) ; 

xfs_caddr_t
xfs_buf_offset(
	xfs_buf_t		*bp,
	size_t			offset)
{
	struct page		*page;

	if (bp->b_flags & XBF_MAPPED)
		return XFS_BUF_PTR(bp) + offset;

	offset += bp->b_offset;
	page = bp->b_pages[offset >> PAGE_SHIFT];
	return (xfs_caddr_t)page_address(page) + (offset & (PAGE_SIZE-1));
}