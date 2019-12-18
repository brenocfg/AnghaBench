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
 int /*<<< orphan*/  mark_page_accessed (struct page*) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

void ocfs2_unlock_and_free_pages(struct page **pages, int num_pages)
{
	int i;

	for(i = 0; i < num_pages; i++) {
		if (pages[i]) {
			unlock_page(pages[i]);
			mark_page_accessed(pages[i]);
			page_cache_release(pages[i]);
		}
	}
}