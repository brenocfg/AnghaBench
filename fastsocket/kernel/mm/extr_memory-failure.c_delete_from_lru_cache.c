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

/* Variables and functions */
 int /*<<< orphan*/  ClearPageActive (struct page*) ; 
 int /*<<< orphan*/  ClearPageUnevictable (struct page*) ; 
 int EIO ; 
 int /*<<< orphan*/  isolate_lru_page (struct page*) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 

__attribute__((used)) static int delete_from_lru_cache(struct page *p)
{
	if (!isolate_lru_page(p)) {
		/*
		 * Clear sensible page flags, so that the buddy system won't
		 * complain when the page is unpoison-and-freed.
		 */
		ClearPageActive(p);
		ClearPageUnevictable(p);
		/*
		 * drop the page count elevated by isolate_lru_page()
		 */
		page_cache_release(p);
		return 0;
	}
	return -EIO;
}