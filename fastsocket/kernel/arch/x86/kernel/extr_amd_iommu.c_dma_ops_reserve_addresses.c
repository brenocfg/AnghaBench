#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dma_ops_domain {unsigned int aperture_size; TYPE_1__** aperture; } ;
struct TYPE_2__ {int /*<<< orphan*/  bitmap; } ;

/* Variables and functions */
 unsigned int APERTURE_RANGE_PAGES ; 
 unsigned int PAGE_SHIFT ; 
 int /*<<< orphan*/  __set_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dma_ops_reserve_addresses(struct dma_ops_domain *dom,
				      unsigned long start_page,
				      unsigned int pages)
{
	unsigned int i, last_page = dom->aperture_size >> PAGE_SHIFT;

	if (start_page + pages > last_page)
		pages = last_page - start_page;

	for (i = start_page; i < start_page + pages; ++i) {
		int index = i / APERTURE_RANGE_PAGES;
		int page  = i % APERTURE_RANGE_PAGES;
		__set_bit(page, dom->aperture[index]->bitmap);
	}
}