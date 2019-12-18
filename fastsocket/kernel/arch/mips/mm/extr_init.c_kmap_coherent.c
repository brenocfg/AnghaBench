#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct TYPE_5__ {unsigned long pte_high; } ;
typedef  TYPE_1__ pte_t ;
typedef  enum fixed_addresses { ____Placeholder_fixed_addresses } fixed_addresses ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENTER_CRITICAL (unsigned long) ; 
 int /*<<< orphan*/  EXIT_CRITICAL (unsigned long) ; 
 int FIX_CMAP_END ; 
 int FIX_N_COLOURS ; 
 int NR_CPUS ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 int PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  Page_dcache_dirty (struct page*) ; 
 unsigned long __fix_to_virt (int) ; 
 scalar_t__ in_interrupt () ; 
 int /*<<< orphan*/  inc_preempt_count () ; 
 int kmap_coherent_pte ; 
 TYPE_1__ mk_pte (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtc0_tlbw_hazard () ; 
 int pte_val (TYPE_1__) ; 
 unsigned long read_c0_entryhi () ; 
 int read_c0_index () ; 
 int read_c0_wired () ; 
 int /*<<< orphan*/  set_pte (int,TYPE_1__) ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  tlb_probe () ; 
 int /*<<< orphan*/  tlb_probe_hazard () ; 
 int /*<<< orphan*/  tlb_write_indexed () ; 
 int /*<<< orphan*/  tlb_write_random () ; 
 int /*<<< orphan*/  tlbw_use_hazard () ; 
 int /*<<< orphan*/  write_c0_entryhi (unsigned long) ; 
 int /*<<< orphan*/  write_c0_entrylo0 (unsigned long) ; 
 int /*<<< orphan*/  write_c0_entrylo1 (unsigned long) ; 
 int /*<<< orphan*/  write_c0_index (int) ; 
 int /*<<< orphan*/  write_c0_wired (int) ; 

void *kmap_coherent(struct page *page, unsigned long addr)
{
	enum fixed_addresses idx;
	unsigned long vaddr, flags, entrylo;
	unsigned long old_ctx;
	pte_t pte;
	int tlbidx;

	BUG_ON(Page_dcache_dirty(page));

	inc_preempt_count();
	idx = (addr >> PAGE_SHIFT) & (FIX_N_COLOURS - 1);
#ifdef CONFIG_MIPS_MT_SMTC
	idx += FIX_N_COLOURS * smp_processor_id() +
		(in_interrupt() ? (FIX_N_COLOURS * NR_CPUS) : 0);
#else
	idx += in_interrupt() ? FIX_N_COLOURS : 0;
#endif
	vaddr = __fix_to_virt(FIX_CMAP_END - idx);
	pte = mk_pte(page, PAGE_KERNEL);
#if defined(CONFIG_64BIT_PHYS_ADDR) && defined(CONFIG_CPU_MIPS32)
	entrylo = pte.pte_high;
#else
	entrylo = pte_val(pte) >> 6;
#endif

	ENTER_CRITICAL(flags);
	old_ctx = read_c0_entryhi();
	write_c0_entryhi(vaddr & (PAGE_MASK << 1));
	write_c0_entrylo0(entrylo);
	write_c0_entrylo1(entrylo);
#ifdef CONFIG_MIPS_MT_SMTC
	set_pte(kmap_coherent_pte - (FIX_CMAP_END - idx), pte);
	/* preload TLB instead of local_flush_tlb_one() */
	mtc0_tlbw_hazard();
	tlb_probe();
	tlb_probe_hazard();
	tlbidx = read_c0_index();
	mtc0_tlbw_hazard();
	if (tlbidx < 0)
		tlb_write_random();
	else
		tlb_write_indexed();
#else
	tlbidx = read_c0_wired();
	write_c0_wired(tlbidx + 1);
	write_c0_index(tlbidx);
	mtc0_tlbw_hazard();
	tlb_write_indexed();
#endif
	tlbw_use_hazard();
	write_c0_entryhi(old_ctx);
	EXIT_CRITICAL(flags);

	return (void*) vaddr;
}