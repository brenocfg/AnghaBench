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
struct page {int /*<<< orphan*/  mapping; } ;
struct buffer_head {struct page* b_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  page_cache_get (struct page*) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 int /*<<< orphan*/  put_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  try_to_free_buffers (struct page*) ; 
 scalar_t__ trylock_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static void release_buffer_page(struct buffer_head *bh)
{
	struct page *page = bh->b_page;
	if (!page->mapping && trylock_page(page)) {
		page_cache_get(page);
		put_bh(bh);
		if (!page->mapping)
			try_to_free_buffers(page);
		unlock_page(page);
		page_cache_release(page);
	} else {
		put_bh(bh);
	}
}