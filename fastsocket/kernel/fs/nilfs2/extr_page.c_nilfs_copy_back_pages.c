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
struct pagevec {struct page** pages; } ;
struct page {struct address_space* mapping; scalar_t__ index; } ;
struct address_space {int /*<<< orphan*/  tree_lock; int /*<<< orphan*/  page_tree; int /*<<< orphan*/  nrpages; } ;
typedef  scalar_t__ pgoff_t ;

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/  PAGECACHE_TAG_DIRTY ; 
 int /*<<< orphan*/  PAGEVEC_SIZE ; 
 int PageDirty (struct page*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cond_resched () ; 
 struct page* find_lock_page (struct address_space*,scalar_t__) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  nilfs_copy_page (struct page*,struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 unsigned int pagevec_count (struct pagevec*) ; 
 int /*<<< orphan*/  pagevec_init (struct pagevec*,int /*<<< orphan*/ ) ; 
 unsigned int pagevec_lookup (struct pagevec*,struct address_space*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pagevec_release (struct pagevec*) ; 
 struct page* radix_tree_delete (int /*<<< orphan*/ *,scalar_t__) ; 
 int radix_tree_insert (int /*<<< orphan*/ *,scalar_t__,struct page*) ; 
 int /*<<< orphan*/  radix_tree_tag_set (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

void nilfs_copy_back_pages(struct address_space *dmap,
			   struct address_space *smap)
{
	struct pagevec pvec;
	unsigned int i, n;
	pgoff_t index = 0;
	int err;

	pagevec_init(&pvec, 0);
repeat:
	n = pagevec_lookup(&pvec, smap, index, PAGEVEC_SIZE);
	if (!n)
		return;
	index = pvec.pages[n - 1]->index + 1;

	for (i = 0; i < pagevec_count(&pvec); i++) {
		struct page *page = pvec.pages[i], *dpage;
		pgoff_t offset = page->index;

		lock_page(page);
		dpage = find_lock_page(dmap, offset);
		if (dpage) {
			/* override existing page on the destination cache */
			WARN_ON(PageDirty(dpage));
			nilfs_copy_page(dpage, page, 0);
			unlock_page(dpage);
			page_cache_release(dpage);
		} else {
			struct page *page2;

			/* move the page to the destination cache */
			spin_lock_irq(&smap->tree_lock);
			page2 = radix_tree_delete(&smap->page_tree, offset);
			WARN_ON(page2 != page);

			smap->nrpages--;
			spin_unlock_irq(&smap->tree_lock);

			spin_lock_irq(&dmap->tree_lock);
			err = radix_tree_insert(&dmap->page_tree, offset, page);
			if (unlikely(err < 0)) {
				WARN_ON(err == -EEXIST);
				page->mapping = NULL;
				page_cache_release(page); /* for cache */
			} else {
				page->mapping = dmap;
				dmap->nrpages++;
				if (PageDirty(page))
					radix_tree_tag_set(&dmap->page_tree,
							   offset,
							   PAGECACHE_TAG_DIRTY);
			}
			spin_unlock_irq(&dmap->tree_lock);
		}
		unlock_page(page);
	}
	pagevec_release(&pvec);
	cond_resched();

	goto repeat;
}