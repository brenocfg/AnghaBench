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
 scalar_t__ FIXADDR_START ; 
 scalar_t__ FIX_KMAP_BEGIN ; 
 int KM_TYPE_NR ; 
 int /*<<< orphan*/  LAST_PKMAP ; 
 unsigned long PAGE_MASK ; 
 unsigned long PKMAP_ADDR (int /*<<< orphan*/ ) ; 
 size_t PKMAP_NR (unsigned long) ; 
 int /*<<< orphan*/  TOP_PTE (unsigned long) ; 
 int /*<<< orphan*/  __cpuc_flush_dcache_page (void*) ; 
 unsigned long __fix_to_virt (scalar_t__) ; 
 int /*<<< orphan*/  __pte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_high (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_flush_tlb_kernel_page (unsigned long) ; 
 int /*<<< orphan*/  pagefault_enable () ; 
 int /*<<< orphan*/ * pkmap_page_table ; 
 int /*<<< orphan*/  pte_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pte_ext (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int smp_processor_id () ; 

void kunmap_atomic(void *kvaddr, enum km_type type)
{
	unsigned long vaddr = (unsigned long) kvaddr & PAGE_MASK;
	unsigned int idx = type + KM_TYPE_NR * smp_processor_id();

	if (kvaddr >= (void *)FIXADDR_START) {
		__cpuc_flush_dcache_page((void *)vaddr);
#ifdef CONFIG_DEBUG_HIGHMEM
		BUG_ON(vaddr != __fix_to_virt(FIX_KMAP_BEGIN + idx));
		set_pte_ext(TOP_PTE(vaddr), __pte(0), 0);
		local_flush_tlb_kernel_page(vaddr);
#else
		(void) idx;  /* to kill a warning */
#endif
	} else if (vaddr >= PKMAP_ADDR(0) && vaddr < PKMAP_ADDR(LAST_PKMAP)) {
		/* this address was obtained through kmap_high_get() */
		kunmap_high(pte_page(pkmap_page_table[PKMAP_NR(vaddr)]));
	}
	pagefault_enable();
}