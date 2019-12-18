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
 unsigned long PAGE_SHIFT ; 
 unsigned long PAGE_SIZE ; 
 scalar_t__ PageHighMem (struct page*) ; 
 int /*<<< orphan*/  _PAGE_CACHE_MASK ; 
 int /*<<< orphan*/  __pgprot (int /*<<< orphan*/ ) ; 
 int cpa_clear_pages_array (struct page**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_memtype (unsigned long,unsigned long) ; 
 unsigned long page_to_pfn (struct page*) ; 

int set_pages_array_wb(struct page **pages, int addrinarray)
{
	int retval;
	unsigned long start;
	unsigned long end;
	int i;

	retval = cpa_clear_pages_array(pages, addrinarray,
			__pgprot(_PAGE_CACHE_MASK));
	if (retval)
		return retval;

	for (i = 0; i < addrinarray; i++) {
		if (PageHighMem(pages[i]))
			continue;
		start = page_to_pfn(pages[i]) << PAGE_SHIFT;
		end = start + PAGE_SIZE;
		free_memtype(start, end);
	}

	return 0;
}