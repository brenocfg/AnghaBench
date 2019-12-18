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
 scalar_t__ PageBuddy (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 scalar_t__ page_count (struct page*) ; 
 int page_order (struct page*) ; 
 int /*<<< orphan*/  page_to_pfn (struct page*) ; 
 scalar_t__ page_zone_id (struct page*) ; 
 int /*<<< orphan*/  pfn_valid_within (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int page_is_buddy(struct page *page, struct page *buddy,
								int order)
{
	if (!pfn_valid_within(page_to_pfn(buddy)))
		return 0;

	if (page_zone_id(page) != page_zone_id(buddy))
		return 0;

	if (PageBuddy(buddy) && page_order(buddy) == order) {
		VM_BUG_ON(page_count(buddy) != 0);
		return 1;
	}
	return 0;
}