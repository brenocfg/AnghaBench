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
struct writeback_control {scalar_t__ sync_mode; scalar_t__ nonblocking; } ;
struct page {int /*<<< orphan*/  index; TYPE_1__* mapping; } ;
struct nfs_pageio_descriptor {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  NFSIOS_VFSWRITEPAGE ; 
 int /*<<< orphan*/  NFSIOS_WRITEPAGES ; 
 scalar_t__ WB_SYNC_NONE ; 
 int /*<<< orphan*/  nfs_add_stats (struct inode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfs_inc_stats (struct inode*,int /*<<< orphan*/ ) ; 
 int nfs_page_async_flush (struct nfs_pageio_descriptor*,struct page*,int) ; 
 int /*<<< orphan*/  nfs_pageio_cond_complete (struct nfs_pageio_descriptor*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  redirty_page_for_writepage (struct writeback_control*,struct page*) ; 

__attribute__((used)) static int nfs_do_writepage(struct page *page, struct writeback_control *wbc, struct nfs_pageio_descriptor *pgio)
{
	struct inode *inode = page->mapping->host;
	int ret;

	nfs_inc_stats(inode, NFSIOS_VFSWRITEPAGE);
	nfs_add_stats(inode, NFSIOS_WRITEPAGES, 1);

	nfs_pageio_cond_complete(pgio, page->index);
	ret = nfs_page_async_flush(pgio, page,
			wbc->sync_mode == WB_SYNC_NONE ||
			wbc->nonblocking != 0);
	if (ret == -EAGAIN) {
		redirty_page_for_writepage(wbc, page);
		ret = 0;
	}
	return ret;
}