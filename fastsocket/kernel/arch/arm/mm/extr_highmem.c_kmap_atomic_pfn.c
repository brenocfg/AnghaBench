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
typedef  enum km_type { ____Placeholder_km_type } km_type ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ FIX_KMAP_BEGIN ; 
 int KM_TYPE_NR ; 
 int /*<<< orphan*/ * TOP_PTE (unsigned long) ; 
 unsigned long __fix_to_virt (scalar_t__) ; 
 int /*<<< orphan*/  kmap_prot ; 
 int /*<<< orphan*/  local_flush_tlb_kernel_page (unsigned long) ; 
 int /*<<< orphan*/  pagefault_disable () ; 
 int /*<<< orphan*/  pfn_pte (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pte_ext (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int smp_processor_id () ; 

void *kmap_atomic_pfn(unsigned long pfn, enum km_type type)
{
	unsigned int idx;
	unsigned long vaddr;

	pagefault_disable();

	idx = type + KM_TYPE_NR * smp_processor_id();
	vaddr = __fix_to_virt(FIX_KMAP_BEGIN + idx);
#ifdef CONFIG_DEBUG_HIGHMEM
	BUG_ON(!pte_none(*(TOP_PTE(vaddr))));
#endif
	set_pte_ext(TOP_PTE(vaddr), pfn_pte(pfn, kmap_prot), 0);
	local_flush_tlb_kernel_page(vaddr);

	return (void *)vaddr;
}