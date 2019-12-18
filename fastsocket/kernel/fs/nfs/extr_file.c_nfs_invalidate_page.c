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
struct page {TYPE_1__* mapping; } ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGECACHE ; 
 int /*<<< orphan*/  dfprintk (int /*<<< orphan*/ ,char*,struct page*,unsigned long) ; 
 int /*<<< orphan*/  nfs_fscache_invalidate_page (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_wb_page_cancel (int /*<<< orphan*/ ,struct page*) ; 

__attribute__((used)) static void nfs_invalidate_page(struct page *page, unsigned long offset)
{
	dfprintk(PAGECACHE, "NFS: invalidate_page(%p, %lu)\n", page, offset);

	if (offset != 0)
		return;
	/* Cancel any unstarted writes on this page */
	nfs_wb_page_cancel(page->mapping->host, page);

	nfs_fscache_invalidate_page(page, page->mapping->host);
}