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

/* Variables and functions */
 unsigned long EHCA_HUGEPAGE_SIZE ; 
 unsigned long EHCA_SECTSIZE ; 
 unsigned long PAGE_SIZE ; 
 scalar_t__ ehca_is_hugepage (unsigned long) ; 
 int ehca_update_busmap (unsigned long,unsigned long) ; 

__attribute__((used)) static int ehca_create_busmap_callback(unsigned long initial_pfn,
				       unsigned long total_nr_pages, void *arg)
{
	int ret;
	unsigned long pfn, start_pfn, end_pfn, nr_pages;

	if ((total_nr_pages * PAGE_SIZE) < EHCA_HUGEPAGE_SIZE)
		return ehca_update_busmap(initial_pfn, total_nr_pages);

	/* Given chunk is >= 16GB -> check for hugepages */
	start_pfn = initial_pfn;
	end_pfn = initial_pfn + total_nr_pages;
	pfn = start_pfn;

	while (pfn < end_pfn) {
		if (ehca_is_hugepage(pfn)) {
			/* Add mem found in front of the hugepage */
			nr_pages = pfn - start_pfn;
			ret = ehca_update_busmap(start_pfn, nr_pages);
			if (ret)
				return ret;
			/* Skip the hugepage */
			pfn += (EHCA_HUGEPAGE_SIZE / PAGE_SIZE);
			start_pfn = pfn;
		} else
			pfn += (EHCA_SECTSIZE / PAGE_SIZE);
	}

	/* Add mem found behind the hugepage(s)  */
	nr_pages = pfn - start_pfn;
	return ehca_update_busmap(start_pfn, nr_pages);
}