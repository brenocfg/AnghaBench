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
 int /*<<< orphan*/  PAGE_POISON ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ PageHighMem (struct page*) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* page_address (struct page*) ; 
 int /*<<< orphan*/  poison_highpage (struct page*) ; 
 int /*<<< orphan*/  set_page_poison (struct page*) ; 

__attribute__((used)) static void poison_page(struct page *page)
{
	void *addr;

	if (PageHighMem(page)) {
		poison_highpage(page);
		return;
	}
	set_page_poison(page);
	addr = page_address(page);
	memset(addr, PAGE_POISON, PAGE_SIZE);
}