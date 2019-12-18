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
struct nfs_page {int dummy; } ;
struct inode {int /*<<< orphan*/  i_lock; } ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int EAGAIN ; 
 struct nfs_page* ERR_PTR (int) ; 
 scalar_t__ nfs_lock_request (struct nfs_page*) ; 
 struct nfs_page* nfs_page_find_request_locked (struct page*) ; 
 int /*<<< orphan*/  nfs_release_request (struct nfs_page*) ; 
 int nfs_wait_on_request (struct nfs_page*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct nfs_page *nfs_find_and_lock_request(struct page *page, bool nonblock)
{
	struct inode *inode = page->mapping->host;
	struct nfs_page *req;
	int ret;

	spin_lock(&inode->i_lock);
	for (;;) {
		req = nfs_page_find_request_locked(page);
		if (req == NULL)
			break;
		if (nfs_lock_request(req))
			break;
		/* Note: If we hold the page lock, as is the case in nfs_writepage,
		 *	 then the call to nfs_lock_request() will always
		 *	 succeed provided that someone hasn't already marked the
		 *	 request as dirty (in which case we don't care).
		 */
		spin_unlock(&inode->i_lock);
		if (!nonblock)
			ret = nfs_wait_on_request(req);
		else
			ret = -EAGAIN;
		nfs_release_request(req);
		if (ret != 0)
			return ERR_PTR(ret);
		spin_lock(&inode->i_lock);
	}
	spin_unlock(&inode->i_lock);
	return req;
}