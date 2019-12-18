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
struct page {TYPE_1__* mapping; int /*<<< orphan*/  index; } ;
struct afs_writeback {int dummy; } ;
struct afs_vnode {int /*<<< orphan*/  cache; } ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 struct afs_vnode* AFS_FS_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ClearPagePrivate (struct page*) ; 
 scalar_t__ PageFsCache (struct page*) ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 scalar_t__ PagePrivate (struct page*) ; 
 int /*<<< orphan*/  PageWriteback (struct page*) ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  afs_put_writeback (struct afs_writeback*) ; 
 int /*<<< orphan*/  fscache_uncache_page (int /*<<< orphan*/ ,struct page*) ; 
 int /*<<< orphan*/  fscache_wait_on_page_write (int /*<<< orphan*/ ,struct page*) ; 
 scalar_t__ page_private (struct page*) ; 
 int /*<<< orphan*/  set_page_private (struct page*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void afs_invalidatepage(struct page *page, unsigned long offset)
{
	struct afs_writeback *wb = (struct afs_writeback *) page_private(page);

	_enter("{%lu},%lu", page->index, offset);

	BUG_ON(!PageLocked(page));

	/* we clean up only if the entire page is being invalidated */
	if (offset == 0) {
#ifdef CONFIG_AFS_FSCACHE
		if (PageFsCache(page)) {
			struct afs_vnode *vnode = AFS_FS_I(page->mapping->host);
			fscache_wait_on_page_write(vnode->cache, page);
			fscache_uncache_page(vnode->cache, page);
		}
#endif

		if (PagePrivate(page)) {
			if (wb && !PageWriteback(page)) {
				set_page_private(page, 0);
				afs_put_writeback(wb);
			}

			if (!page_private(page))
				ClearPagePrivate(page);
		}
	}

	_leave("");
}