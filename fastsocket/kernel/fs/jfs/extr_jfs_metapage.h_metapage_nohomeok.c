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
struct metapage {int /*<<< orphan*/  nohomeok; struct page* page; } ;

/* Variables and functions */
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  mark_metapage_dirty (struct metapage*) ; 
 int /*<<< orphan*/  page_cache_get (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  wait_on_page_writeback (struct page*) ; 

__attribute__((used)) static inline void metapage_nohomeok(struct metapage *mp)
{
	struct page *page = mp->page;
	lock_page(page);
	if (!mp->nohomeok++) {
		mark_metapage_dirty(mp);
		page_cache_get(page);
		wait_on_page_writeback(page);
	}
	unlock_page(page);
}