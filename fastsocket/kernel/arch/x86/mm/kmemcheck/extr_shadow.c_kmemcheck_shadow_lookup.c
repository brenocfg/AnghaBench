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
struct page {void* shadow; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/ * kmemcheck_pte_lookup (unsigned long) ; 
 int /*<<< orphan*/  virt_addr_valid (unsigned long) ; 
 struct page* virt_to_page (unsigned long) ; 

void *kmemcheck_shadow_lookup(unsigned long address)
{
	pte_t *pte;
	struct page *page;

	if (!virt_addr_valid(address))
		return NULL;

	pte = kmemcheck_pte_lookup(address);
	if (!pte)
		return NULL;

	page = virt_to_page(address);
	if (!page->shadow)
		return NULL;
	return page->shadow + (address & (PAGE_SIZE - 1));
}