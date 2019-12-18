#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {scalar_t__ vm_mm; } ;
typedef  int /*<<< orphan*/  pud_t ;
struct TYPE_6__ {int pte_high; } ;
typedef  TYPE_1__ pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;
struct TYPE_7__ {scalar_t__ active_mm; } ;

/* Variables and functions */
 int ASID_MASK ; 
 int /*<<< orphan*/  ENTER_CRITICAL (unsigned long) ; 
 int /*<<< orphan*/  EXIT_CRITICAL (unsigned long) ; 
 int /*<<< orphan*/  FLUSH_ITLB_VM (struct vm_area_struct*) ; 
 int HPAGE_SIZE ; 
 int PAGE_MASK ; 
 int /*<<< orphan*/  PM_DEFAULT_MASK ; 
 int /*<<< orphan*/  PM_HUGE_MASK ; 
 TYPE_4__* current ; 
 int /*<<< orphan*/  mtc0_tlbw_hazard () ; 
 int /*<<< orphan*/ * pgd_offset (scalar_t__,unsigned long) ; 
 scalar_t__ pmd_huge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_1__* pte_offset_map (int /*<<< orphan*/ *,unsigned long) ; 
 int pte_val (TYPE_1__) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int read_c0_entryhi () ; 
 int read_c0_index () ; 
 int /*<<< orphan*/  tlb_probe () ; 
 int /*<<< orphan*/  tlb_probe_hazard () ; 
 int /*<<< orphan*/  tlb_write_indexed () ; 
 int /*<<< orphan*/  tlb_write_random () ; 
 int /*<<< orphan*/  tlbw_use_hazard () ; 
 int /*<<< orphan*/  write_c0_entryhi (unsigned long) ; 
 int /*<<< orphan*/  write_c0_entrylo0 (int) ; 
 int /*<<< orphan*/  write_c0_entrylo1 (int) ; 
 int /*<<< orphan*/  write_c0_pagemask (int /*<<< orphan*/ ) ; 

void __update_tlb(struct vm_area_struct * vma, unsigned long address, pte_t pte)
{
	unsigned long flags;
	pgd_t *pgdp;
	pud_t *pudp;
	pmd_t *pmdp;
	pte_t *ptep;
	int idx, pid;

	/*
	 * Handle debugger faulting in for debugee.
	 */
	if (current->active_mm != vma->vm_mm)
		return;

	ENTER_CRITICAL(flags);

	pid = read_c0_entryhi() & ASID_MASK;
	address &= (PAGE_MASK << 1);
	write_c0_entryhi(address | pid);
	pgdp = pgd_offset(vma->vm_mm, address);
	mtc0_tlbw_hazard();
	tlb_probe();
	tlb_probe_hazard();
	pudp = pud_offset(pgdp, address);
	pmdp = pmd_offset(pudp, address);
	idx = read_c0_index();
#ifdef CONFIG_HUGETLB_PAGE
	/* this could be a huge page  */
	if (pmd_huge(*pmdp)) {
		unsigned long lo;
		write_c0_pagemask(PM_HUGE_MASK);
		ptep = (pte_t *)pmdp;
		lo = pte_val(*ptep) >> 6;
		write_c0_entrylo0(lo);
		write_c0_entrylo1(lo + (HPAGE_SIZE >> 7));

		mtc0_tlbw_hazard();
		if (idx < 0)
			tlb_write_random();
		else
			tlb_write_indexed();
		write_c0_pagemask(PM_DEFAULT_MASK);
	} else
#endif
	{
		ptep = pte_offset_map(pmdp, address);

#if defined(CONFIG_64BIT_PHYS_ADDR) && defined(CONFIG_CPU_MIPS32)
		write_c0_entrylo0(ptep->pte_high);
		ptep++;
		write_c0_entrylo1(ptep->pte_high);
#else
		write_c0_entrylo0(pte_val(*ptep++) >> 6);
		write_c0_entrylo1(pte_val(*ptep) >> 6);
#endif
		mtc0_tlbw_hazard();
		if (idx < 0)
			tlb_write_random();
		else
			tlb_write_indexed();
	}
	tlbw_use_hazard();
	FLUSH_ITLB_VM(vma);
	EXIT_CRITICAL(flags);
}