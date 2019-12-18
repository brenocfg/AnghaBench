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
struct page {scalar_t__ index; } ;
struct inode {struct address_space* i_mapping; } ;
struct fscache_cookie {int dummy; } ;
struct address_space {scalar_t__ nrpages; } ;
typedef  scalar_t__ pgoff_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGEVEC_SIZE ; 
 scalar_t__ PageFsCache (struct page*) ; 
 int /*<<< orphan*/  __fscache_uncache_page (struct fscache_cookie*,struct page*) ; 
 int /*<<< orphan*/  __fscache_wait_on_page_write (struct fscache_cookie*,struct page*) ; 
 int /*<<< orphan*/  _enter (char*,struct fscache_cookie*,struct inode*) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int pagevec_count (struct pagevec*) ; 
 int /*<<< orphan*/  pagevec_init (struct pagevec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pagevec_lookup (struct pagevec*,struct address_space*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pagevec_release (struct pagevec*) ; 

void __fscache_uncache_all_inode_pages(struct fscache_cookie *cookie,
				       struct inode *inode)
{
	struct address_space *mapping = inode->i_mapping;
	struct pagevec pvec;
	pgoff_t next;
	int i;

	_enter("%p,%p", cookie, inode);

	if (!mapping || mapping->nrpages == 0) {
		_leave(" [no pages]");
		return;
	}

	pagevec_init(&pvec, 0);
	next = 0;
	do {
		if (!pagevec_lookup(&pvec, mapping, next, PAGEVEC_SIZE))
			break;
		for (i = 0; i < pagevec_count(&pvec); i++) {
			struct page *page = pvec.pages[i];
			next = page->index;
			if (PageFsCache(page)) {
				__fscache_wait_on_page_write(cookie, page);
				__fscache_uncache_page(cookie, page);
			}
		}
		pagevec_release(&pvec);
		cond_resched();
	} while (++next);

	_leave("");
}