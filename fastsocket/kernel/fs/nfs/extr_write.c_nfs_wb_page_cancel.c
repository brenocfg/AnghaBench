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
struct page {int dummy; } ;
struct nfs_page {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  PAGE_CACHE_SIZE ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int /*<<< orphan*/  cancel_dirty_page (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_clear_request_commit (struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_inode_remove_request (struct nfs_page*) ; 
 scalar_t__ nfs_lock_request (struct nfs_page*) ; 
 struct nfs_page* nfs_page_find_request (struct page*) ; 
 int /*<<< orphan*/  nfs_release_request (struct nfs_page*) ; 
 int /*<<< orphan*/  nfs_unlock_and_release_request (struct nfs_page*) ; 
 int nfs_wait_on_request (struct nfs_page*) ; 
 int /*<<< orphan*/  wait_on_page_writeback (struct page*) ; 

int nfs_wb_page_cancel(struct inode *inode, struct page *page)
{
	struct nfs_page *req;
	int ret = 0;

	BUG_ON(!PageLocked(page));
	for (;;) {
		wait_on_page_writeback(page);
		req = nfs_page_find_request(page);
		if (req == NULL)
			break;
		if (nfs_lock_request(req)) {
			nfs_clear_request_commit(req);
			nfs_inode_remove_request(req);
			/*
			 * In case nfs_inode_remove_request has marked the
			 * page as being dirty
			 */
			cancel_dirty_page(page, PAGE_CACHE_SIZE);
			nfs_unlock_and_release_request(req);
			break;
		}
		ret = nfs_wait_on_request(req);
		nfs_release_request(req);
		if (ret < 0)
			break;
	}
	return ret;
}