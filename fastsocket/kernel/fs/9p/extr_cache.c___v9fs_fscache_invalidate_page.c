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
struct v9fs_cookie {int /*<<< orphan*/  fscache; } ;
struct page {TYPE_1__* mapping; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ PageFsCache (struct page*) ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int /*<<< orphan*/  fscache_uncache_page (int /*<<< orphan*/ ,struct page*) ; 
 int /*<<< orphan*/  fscache_wait_on_page_write (int /*<<< orphan*/ ,struct page*) ; 
 struct v9fs_cookie* v9fs_inode2cookie (struct inode*) ; 

void __v9fs_fscache_invalidate_page(struct page *page)
{
	struct inode *inode = page->mapping->host;
	struct v9fs_cookie *vcookie = v9fs_inode2cookie(inode);

	BUG_ON(!vcookie->fscache);

	if (PageFsCache(page)) {
		fscache_wait_on_page_write(vcookie->fscache, page);
		BUG_ON(!PageLocked(page));
		fscache_uncache_page(vcookie->fscache, page);
	}
}