#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct page {int /*<<< orphan*/  flags; int /*<<< orphan*/  index; TYPE_1__* mapping; } ;
struct afs_writeback {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  vnode; int /*<<< orphan*/  vid; } ;
struct afs_vnode {int /*<<< orphan*/  cache; TYPE_2__ fid; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_3__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 struct afs_vnode* AFS_FS_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ClearPagePrivate (struct page*) ; 
 scalar_t__ PagePrivate (struct page*) ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  afs_put_writeback (struct afs_writeback*) ; 
 int /*<<< orphan*/  fscache_maybe_release_page (int /*<<< orphan*/ ,struct page*,int /*<<< orphan*/ ) ; 
 scalar_t__ page_private (struct page*) ; 
 int /*<<< orphan*/  set_page_private (struct page*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int afs_releasepage(struct page *page, gfp_t gfp_flags)
{
	struct afs_writeback *wb = (struct afs_writeback *) page_private(page);
	struct afs_vnode *vnode = AFS_FS_I(page->mapping->host);

	_enter("{{%x:%u}[%lu],%lx},%x",
	       vnode->fid.vid, vnode->fid.vnode, page->index, page->flags,
	       gfp_flags);

	/* deny if page is being written to the cache and the caller hasn't
	 * elected to wait */
#ifdef CONFIG_AFS_FSCACHE
	if (!fscache_maybe_release_page(vnode->cache, page, gfp_flags)) {
		_leave(" = F [cache busy]");
		return 0;
	}
#endif

	if (PagePrivate(page)) {
		if (wb) {
			set_page_private(page, 0);
			afs_put_writeback(wb);
		}
		ClearPagePrivate(page);
	}

	/* indicate that the page can be released */
	_leave(" = T");
	return 1;
}