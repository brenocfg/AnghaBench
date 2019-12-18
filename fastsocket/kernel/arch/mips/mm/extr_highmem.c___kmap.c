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
 int /*<<< orphan*/  PageHighMem (struct page*) ; 
 int /*<<< orphan*/  flush_tlb_one (unsigned long) ; 
 void* kmap_high (struct page*) ; 
 int /*<<< orphan*/  might_sleep () ; 
 void* page_address (struct page*) ; 

void *__kmap(struct page *page)
{
	void *addr;

	might_sleep();
	if (!PageHighMem(page))
		return page_address(page);
	addr = kmap_high(page);
	flush_tlb_one((unsigned long)addr);

	return addr;
}