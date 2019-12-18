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
struct st_buffer {struct page** mapped_pages; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SetPageDirty (struct page*) ; 
 int /*<<< orphan*/  kfree (struct page**) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 

__attribute__((used)) static int sgl_unmap_user_pages(struct st_buffer *STbp,
				const unsigned int nr_pages, int dirtied)
{
	int i;

	for (i=0; i < nr_pages; i++) {
		struct page *page = STbp->mapped_pages[i];

		if (dirtied)
			SetPageDirty(page);
		/* FIXME: cache flush missing for rw==READ
		 * FIXME: call the correct reference counting function
		 */
		page_cache_release(page);
	}
	kfree(STbp->mapped_pages);
	STbp->mapped_pages = NULL;

	return 0;
}