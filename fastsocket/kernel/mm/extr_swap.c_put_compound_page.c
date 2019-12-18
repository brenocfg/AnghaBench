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
struct page {int /*<<< orphan*/  _count; int /*<<< orphan*/  _mapcount; struct page* first_page; } ;

/* Variables and functions */
 scalar_t__ PageHead (struct page*) ; 
 scalar_t__ PageSlab (struct page*) ; 
 int PageTail (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  __put_compound_page (struct page*) ; 
 int /*<<< orphan*/  __put_single_page (struct page*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 unsigned long compound_lock_irqsave (struct page*) ; 
 struct page* compound_trans_head (struct page*) ; 
 int /*<<< orphan*/  compound_unlock_irqrestore (struct page*,unsigned long) ; 
 scalar_t__ get_page_unless_zero (struct page*) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ page_mapcount (struct page*) ; 
 scalar_t__ put_page_testzero (struct page*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void put_compound_page(struct page *page)
{
	if (unlikely(PageTail(page))) {
		/* __split_huge_page_refcount can run under us */
		struct page *page_head = compound_trans_head(page);
		if (likely(page != page_head &&
			   get_page_unless_zero(page_head))) {
			unsigned long flags;

			/*
			 * THP can not break up slab pages so avoid taking
			 * compound_lock().  Slab performs non-atomic bit ops
			 * on page->flags for better performance.  In particular
			 * slab_unlock() in slub used to be a hot path.  It is
			 * still hot on arches that do not support
			 * this_cpu_cmpxchg_double().
			 */
			if (PageSlab(page_head)) {
				if (PageTail(page)) {
					if (put_page_testzero(page_head))
						VM_BUG_ON(1);

					atomic_dec(&page->_mapcount);
					goto skip_lock_tail;
				} else
					goto skip_lock;
			}
			/*
			 * page_head wasn't a dangling pointer but it
			 * may not be a head page anymore by the time
			 * we obtain the lock. That is ok as long as it
			 * can't be freed from under us.
			 */
			flags = compound_lock_irqsave(page_head);
			if (unlikely(!PageTail(page))) {
				/* __split_huge_page_refcount run before us */
				compound_unlock_irqrestore(page_head, flags);
skip_lock:
				if (put_page_testzero(page_head))
					__put_single_page(page_head);
out_put_single:
				if (put_page_testzero(page))
					__put_single_page(page);
				return;
			}
			VM_BUG_ON(page_head != page->first_page);
			/*
			 * We can release the refcount taken by
			 * get_page_unless_zero() now that
			 * __split_huge_page_refcount() is blocked on
			 * the compound_lock.
			 */
			if (put_page_testzero(page_head))
				VM_BUG_ON(1);
			/* __split_huge_page_refcount will wait now */
			VM_BUG_ON(page_mapcount(page) <= 0);
			atomic_dec(&page->_mapcount);
			VM_BUG_ON(atomic_read(&page_head->_count) <= 0);
			VM_BUG_ON(atomic_read(&page->_count) != 0);
			compound_unlock_irqrestore(page_head, flags);

skip_lock_tail:
			if (put_page_testzero(page_head)) {
				if (PageHead(page_head))
					__put_compound_page(page_head);
				else
					__put_single_page(page_head);
			}
		} else {
			/* page_head is a dangling pointer */
			VM_BUG_ON(PageTail(page));
			goto out_put_single;
		}
	} else if (put_page_testzero(page)) {
		if (PageHead(page))
			__put_compound_page(page);
		else
			__put_single_page(page);
	}
}