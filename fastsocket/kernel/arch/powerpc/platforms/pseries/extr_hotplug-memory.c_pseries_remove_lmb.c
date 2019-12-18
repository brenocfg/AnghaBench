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
struct zone {int dummy; } ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 int __remove_pages (struct zone*,unsigned long,unsigned int) ; 
 scalar_t__ __va (unsigned long) ; 
 int /*<<< orphan*/  lmb_remove (unsigned long,unsigned int) ; 
 struct zone* page_zone (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfn_to_page (unsigned long) ; 
 int /*<<< orphan*/  pfn_valid (unsigned long) ; 
 int remove_section_mapping (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  vm_unmap_aliases () ; 

__attribute__((used)) static int pseries_remove_lmb(unsigned long base, unsigned int lmb_size)
{
	unsigned long start, start_pfn;
	struct zone *zone;
	int ret;

	start_pfn = base >> PAGE_SHIFT;

	if (!pfn_valid(start_pfn)) {
		lmb_remove(base, lmb_size);
		return 0;
	}

	zone = page_zone(pfn_to_page(start_pfn));

	/*
	 * Remove section mappings and sysfs entries for the
	 * section of the memory we are removing.
	 *
	 * NOTE: Ideally, this should be done in generic code like
	 * remove_memory(). But remove_memory() gets called by writing
	 * to sysfs "state" file and we can't remove sysfs entries
	 * while writing to it. So we have to defer it to here.
	 */
	ret = __remove_pages(zone, start_pfn, lmb_size >> PAGE_SHIFT);
	if (ret)
		return ret;

	/*
	 * Update memory regions for memory remove
	 */
	lmb_remove(base, lmb_size);

	/*
	 * Remove htab bolted mappings for this section of memory
	 */
	start = (unsigned long)__va(base);
	ret = remove_section_mapping(start, start + lmb_size);

	/* Ensure all vmalloc mappings are flushed in case they also
	 * hit that section of memory
	 */
	vm_unmap_aliases();

	return ret;
}