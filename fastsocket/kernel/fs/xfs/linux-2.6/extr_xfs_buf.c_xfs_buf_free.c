#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int b_flags; size_t b_page_count; scalar_t__ b_addr; struct page** b_pages; scalar_t__ b_offset; int /*<<< orphan*/  b_lru; } ;
typedef  TYPE_1__ xfs_buf_t ;
typedef  size_t uint ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int _XBF_KMEM ; 
 int _XBF_PAGES ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 int /*<<< orphan*/  _xfs_buf_free_pages (TYPE_1__*) ; 
 int /*<<< orphan*/  kmem_free (scalar_t__) ; 
 int /*<<< orphan*/  kmem_zone_free (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xfs_buf_free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_unmap_ram (scalar_t__,size_t) ; 
 scalar_t__ xfs_buf_is_vmapped (TYPE_1__*) ; 
 int /*<<< orphan*/  xfs_buf_zone ; 

void
xfs_buf_free(
	xfs_buf_t		*bp)
{
	trace_xfs_buf_free(bp, _RET_IP_);

	ASSERT(list_empty(&bp->b_lru));

	if (bp->b_flags & _XBF_PAGES) {
		uint		i;

		if (xfs_buf_is_vmapped(bp))
			vm_unmap_ram(bp->b_addr - bp->b_offset,
					bp->b_page_count);

		for (i = 0; i < bp->b_page_count; i++) {
			struct page	*page = bp->b_pages[i];

			__free_page(page);
		}
	} else if (bp->b_flags & _XBF_KMEM)
		kmem_free(bp->b_addr);
	_xfs_buf_free_pages(bp);
	kmem_zone_free(xfs_buf_zone, bp);
}