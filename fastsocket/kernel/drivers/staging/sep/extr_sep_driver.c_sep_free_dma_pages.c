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
 int /*<<< orphan*/  PageReserved (struct page*) ; 
 int /*<<< orphan*/  SetPageDirty (struct page*) ; 
 int /*<<< orphan*/  kfree (struct page**) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 

__attribute__((used)) static int sep_free_dma_pages(struct page **page_array_ptr, unsigned long num_pages, unsigned long dirtyFlag)
{
	unsigned long count;

	if (dirtyFlag) {
		for (count = 0; count < num_pages; count++) {
			/* the out array was written, therefore the data was changed */
			if (!PageReserved(page_array_ptr[count]))
				SetPageDirty(page_array_ptr[count]);
			page_cache_release(page_array_ptr[count]);
		}
	} else {
		/* free in pages - the data was only read, therefore no update was done
		   on those pages */
		for (count = 0; count < num_pages; count++)
			page_cache_release(page_array_ptr[count]);
	}

	if (page_array_ptr)
		/* free the array */
		kfree(page_array_ptr);

	return 0;
}