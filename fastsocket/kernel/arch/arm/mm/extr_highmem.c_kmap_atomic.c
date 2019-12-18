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
typedef  enum km_type { ____Placeholder_km_type } km_type ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ FIX_KMAP_BEGIN ; 
 int KM_TYPE_NR ; 
 int /*<<< orphan*/  PageHighMem (struct page*) ; 
 int /*<<< orphan*/ * TOP_PTE (unsigned long) ; 
 unsigned long __fix_to_virt (scalar_t__) ; 
 int /*<<< orphan*/  debug_kmap_atomic (int) ; 
 void* kmap_high_get (struct page*) ; 
 int /*<<< orphan*/  kmap_prot ; 
 int /*<<< orphan*/  local_flush_tlb_kernel_page (unsigned long) ; 
 int /*<<< orphan*/  mk_pte (struct page*,int /*<<< orphan*/ ) ; 
 void* page_address (struct page*) ; 
 int /*<<< orphan*/  pagefault_disable () ; 
 int /*<<< orphan*/  pte_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pte_ext (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int smp_processor_id () ; 

void *kmap_atomic(struct page *page, enum km_type type)
{
	unsigned int idx;
	unsigned long vaddr;
	void *kmap;

	pagefault_disable();
	if (!PageHighMem(page))
		return page_address(page);

	debug_kmap_atomic(type);

	kmap = kmap_high_get(page);
	if (kmap)
		return kmap;

	idx = type + KM_TYPE_NR * smp_processor_id();
	vaddr = __fix_to_virt(FIX_KMAP_BEGIN + idx);
#ifdef CONFIG_DEBUG_HIGHMEM
	/*
	 * With debugging enabled, kunmap_atomic forces that entry to 0.
	 * Make sure it was indeed properly unmapped.
	 */
	BUG_ON(!pte_none(*(TOP_PTE(vaddr))));
#endif
	set_pte_ext(TOP_PTE(vaddr), mk_pte(page, kmap_prot), 0);
	/*
	 * When debugging is off, kunmap_atomic leaves the previous mapping
	 * in place, so this TLB flush ensures the TLB is updated with the
	 * new mapping.
	 */
	local_flush_tlb_kernel_page(vaddr);

	return (void *)vaddr;
}