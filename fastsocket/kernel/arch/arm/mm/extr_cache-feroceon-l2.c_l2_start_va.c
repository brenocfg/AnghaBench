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
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  TOP_PTE (unsigned long) ; 
 unsigned long __fix_to_virt (scalar_t__) ; 
 unsigned long __phys_to_virt (unsigned long) ; 
 int /*<<< orphan*/  local_flush_tlb_kernel_page (unsigned long) ; 
 int /*<<< orphan*/  pfn_pte (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pte_ext (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long smp_processor_id () ; 

__attribute__((used)) static inline unsigned long l2_start_va(unsigned long paddr)
{
#ifdef CONFIG_HIGHMEM
	/*
	 * Let's do our own fixmap stuff in a minimal way here.
	 * Because range ops can't be done on physical addresses,
	 * we simply install a virtual mapping for it only for the
	 * TLB lookup to occur, hence no need to flush the untouched
	 * memory mapping.  This is protected with the disabling of
	 * interrupts by the caller.
	 */
	unsigned long idx = KM_L2_CACHE + KM_TYPE_NR * smp_processor_id();
	unsigned long vaddr = __fix_to_virt(FIX_KMAP_BEGIN + idx);
	set_pte_ext(TOP_PTE(vaddr), pfn_pte(paddr >> PAGE_SHIFT, PAGE_KERNEL), 0);
	local_flush_tlb_kernel_page(vaddr);
	return vaddr + (paddr & ~PAGE_MASK);
#else
	return __phys_to_virt(paddr);
#endif
}