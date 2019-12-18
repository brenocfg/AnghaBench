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
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned long FIXADDR_START ; 
 unsigned long FIXADDR_TOP ; 
 unsigned long FIX_KMAP_BEGIN ; 
 int PAGE_SHIFT ; 
 unsigned long PKMAP_BASE ; 
 unsigned long SRMMU_NOCACHE_VADDR ; 
 int __nocache_pa (unsigned long) ; 
 int /*<<< orphan*/ * kmap_pte ; 
 struct page* pfn_to_page (int) ; 
 struct page* pte_page (int /*<<< orphan*/ ) ; 
 unsigned long virt_to_fix (unsigned long) ; 
 struct page* virt_to_page (void*) ; 

struct page *kmap_atomic_to_page(void *ptr)
{
	unsigned long idx, vaddr = (unsigned long)ptr;
	pte_t *pte;

	if (vaddr < SRMMU_NOCACHE_VADDR)
		return virt_to_page(ptr);
	if (vaddr < PKMAP_BASE)
		return pfn_to_page(__nocache_pa(vaddr) >> PAGE_SHIFT);
	BUG_ON(vaddr < FIXADDR_START);
	BUG_ON(vaddr > FIXADDR_TOP);

	idx = virt_to_fix(vaddr);
	pte = kmap_pte - (idx - FIX_KMAP_BEGIN);
	return pte_page(*pte);
}