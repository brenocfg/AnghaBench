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

/* Variables and functions */
 scalar_t__ FIX_KMAP_BEGIN ; 
 unsigned long KM_L2_CACHE ; 
 unsigned long KM_TYPE_NR ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 unsigned long PAGE_MASK ; 
 int PAGE_SHIFT ; 
 unsigned long PSR_I_BIT ; 
 int /*<<< orphan*/  TOP_PTE (unsigned long) ; 
 unsigned long __fix_to_virt (scalar_t__) ; 
 unsigned long __phys_to_virt (unsigned long) ; 
 int /*<<< orphan*/  local_flush_tlb_kernel_page (unsigned long) ; 
 int /*<<< orphan*/  pfn_pte (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  set_pte_ext (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long smp_processor_id () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline unsigned long l2_map_va(unsigned long pa, unsigned long prev_va,
				      unsigned long flags)
{
#ifdef CONFIG_HIGHMEM
	unsigned long va = prev_va & PAGE_MASK;
	unsigned long pa_offset = pa << (32 - PAGE_SHIFT);
	if (unlikely(pa_offset < (prev_va << (32 - PAGE_SHIFT)))) {
		/*
		 * Switching to a new page.  Because cache ops are
		 * using virtual addresses only, we must put a mapping
		 * in place for it.  We also enable interrupts for a
		 * short while and disable them again to protect this
		 * mapping.
		 */
		unsigned long idx;
		raw_local_irq_restore(flags);
		idx = KM_L2_CACHE + KM_TYPE_NR * smp_processor_id();
		va = __fix_to_virt(FIX_KMAP_BEGIN + idx);
		raw_local_irq_restore(flags | PSR_I_BIT);
		set_pte_ext(TOP_PTE(va), pfn_pte(pa >> PAGE_SHIFT, PAGE_KERNEL), 0);
		local_flush_tlb_kernel_page(va);
	}
	return va + (pa_offset >> (32 - PAGE_SHIFT));
#else
	return __phys_to_virt(pa);
#endif
}