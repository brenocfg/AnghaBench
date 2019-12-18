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
struct address_space {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  balance_dirty_pages_ratelimited (struct address_space*) ; 
 struct address_space* page_mapping (struct page*) ; 
 scalar_t__ set_page_dirty (struct page*) ; 

void set_page_dirty_balance(struct page *page, int page_mkwrite)
{
	if (set_page_dirty(page) || page_mkwrite) {
		struct address_space *mapping = page_mapping(page);

		if (mapping)
			balance_dirty_pages_ratelimited(mapping);
	}
}