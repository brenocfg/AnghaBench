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
struct hstate {unsigned long resv_huge_pages; scalar_t__ order; int /*<<< orphan*/  surplus_huge_pages; } ;

/* Variables and functions */
 scalar_t__ MAX_ORDER ; 
 size_t N_HIGH_MEMORY ; 
 int /*<<< orphan*/  free_pool_huge_page (struct hstate*,int /*<<< orphan*/ *,int) ; 
 unsigned long min (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * node_states ; 

__attribute__((used)) static void return_unused_surplus_pages(struct hstate *h,
					unsigned long unused_resv_pages)
{
	unsigned long nr_pages;

	/* Uncommit the reservation */
	h->resv_huge_pages -= unused_resv_pages;

	/* Cannot return gigantic pages currently */
	if (h->order >= MAX_ORDER)
		return;

	nr_pages = min(unused_resv_pages, h->surplus_huge_pages);

	/*
	 * We want to release as many surplus pages as possible, spread
	 * evenly across all nodes with memory. Iterate across these nodes
	 * until we can no longer free unreserved surplus pages. This occurs
	 * when the nodes with surplus pages have no free pages.
	 * free_pool_huge_page() will balance the the freed pages across the
	 * on-line nodes with memory and will handle the hstate accounting.
	 */
	while (nr_pages--) {
		if (!free_pool_huge_page(h, &node_states[N_HIGH_MEMORY], 1))
			break;
	}
}