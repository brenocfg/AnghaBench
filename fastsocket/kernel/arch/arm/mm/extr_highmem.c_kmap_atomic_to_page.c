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
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 unsigned long FIXADDR_START ; 
 int /*<<< orphan*/ * TOP_PTE (unsigned long) ; 
 struct page* pte_page (int /*<<< orphan*/ ) ; 
 struct page* virt_to_page (void const*) ; 

struct page *kmap_atomic_to_page(const void *ptr)
{
	unsigned long vaddr = (unsigned long)ptr;
	pte_t *pte;

	if (vaddr < FIXADDR_START)
		return virt_to_page(ptr);

	pte = TOP_PTE(vaddr);
	return pte_page(*pte);
}