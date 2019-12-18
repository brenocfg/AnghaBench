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
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ PageHighMem (struct page*) ; 
 int /*<<< orphan*/  check_poison_mem (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_page_poison (struct page*) ; 
 void* page_address (struct page*) ; 
 scalar_t__ page_poison (struct page*) ; 
 int /*<<< orphan*/  unpoison_highpage (struct page*) ; 

__attribute__((used)) static void unpoison_page(struct page *page)
{
	if (PageHighMem(page)) {
		unpoison_highpage(page);
		return;
	}
	if (page_poison(page)) {
		void *addr = page_address(page);

		check_poison_mem(addr, PAGE_SIZE);
		clear_page_poison(page);
	}
}