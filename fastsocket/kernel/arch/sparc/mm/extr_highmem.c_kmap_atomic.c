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
 unsigned long __fix_to_virt (scalar_t__) ; 
 int /*<<< orphan*/  __flush_cache_one (unsigned long) ; 
 int /*<<< orphan*/  __flush_tlb_one (unsigned long) ; 
 int /*<<< orphan*/  debug_kmap_atomic (int) ; 
 int /*<<< orphan*/  flush_cache_all () ; 
 int /*<<< orphan*/  flush_tlb_all () ; 
 int /*<<< orphan*/  kmap_prot ; 
 int /*<<< orphan*/ * kmap_pte ; 
 int /*<<< orphan*/  mk_pte (struct page*,int /*<<< orphan*/ ) ; 
 void* page_address (struct page*) ; 
 int /*<<< orphan*/  pagefault_disable () ; 
 int /*<<< orphan*/  pte_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pte (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int smp_processor_id () ; 

void *kmap_atomic(struct page *page, enum km_type type)
{
	unsigned long idx;
	unsigned long vaddr;

	/* even !CONFIG_PREEMPT needs this, for in_atomic in do_page_fault */
	pagefault_disable();
	if (!PageHighMem(page))
		return page_address(page);

	debug_kmap_atomic(type);
	idx = type + KM_TYPE_NR*smp_processor_id();
	vaddr = __fix_to_virt(FIX_KMAP_BEGIN + idx);

/* XXX Fix - Anton */
#if 0
	__flush_cache_one(vaddr);
#else
	flush_cache_all();
#endif

#ifdef CONFIG_DEBUG_HIGHMEM
	BUG_ON(!pte_none(*(kmap_pte-idx)));
#endif
	set_pte(kmap_pte-idx, mk_pte(page, kmap_prot));
/* XXX Fix - Anton */
#if 0
	__flush_tlb_one(vaddr);
#else
	flush_tlb_all();
#endif

	return (void*) vaddr;
}