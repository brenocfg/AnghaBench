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
typedef  int /*<<< orphan*/  swp_entry_t ;
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 scalar_t__ PAGE_MIGRATION ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  __ptep_modify_prot_commit (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ptep_modify_prot_start (struct mm_struct*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arch_enter_lazy_mmu_mode () ; 
 int /*<<< orphan*/  arch_leave_lazy_mmu_mode () ; 
 scalar_t__ is_write_migration_entry (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  make_migration_entry_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  paravirt_enabled () ; 
 scalar_t__ pte_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_mkwrite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_modify (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_map_lock (struct mm_struct*,int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ **) ; 
 scalar_t__ pte_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_to_swp_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_unmap_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptep_modify_prot_commit (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptep_modify_prot_start (struct mm_struct*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_pte_at (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swp_entry_to_pte (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void change_pte_range(struct mm_struct *mm, pmd_t *pmd,
		unsigned long addr, unsigned long end, pgprot_t newprot,
		int dirty_accountable)
{
	pte_t *pte, oldpte;
	spinlock_t *ptl;

	pte = pte_offset_map_lock(mm, pmd, addr, &ptl);
	arch_enter_lazy_mmu_mode();
	do {
		oldpte = *pte;
		if (pte_present(oldpte)) {
			pte_t ptent;

#ifdef CONFIG_PARAVIRT
			if (likely(!paravirt_enabled()))
				ptent = __ptep_modify_prot_start(mm, addr, pte);
			else
#endif
				ptent = ptep_modify_prot_start(mm, addr, pte);
			ptent = pte_modify(ptent, newprot);

			/*
			 * Avoid taking write faults for pages we know to be
			 * dirty.
			 */
			if (dirty_accountable && pte_dirty(ptent))
				ptent = pte_mkwrite(ptent);

#ifdef CONFIG_PARAVIRT
			if (likely(!paravirt_enabled()))
				__ptep_modify_prot_commit(mm, addr, pte, ptent);
			else
#endif
				ptep_modify_prot_commit(mm, addr, pte, ptent);
		} else if (PAGE_MIGRATION && !pte_file(oldpte)) {
			swp_entry_t entry = pte_to_swp_entry(oldpte);

			if (is_write_migration_entry(entry)) {
				/*
				 * A protection check is difficult so
				 * just be safe and disable write
				 */
				make_migration_entry_read(&entry);
				set_pte_at(mm, addr, pte,
					swp_entry_to_pte(entry));
			}
		}
	} while (pte++, addr += PAGE_SIZE, addr != end);
	arch_leave_lazy_mmu_mode();
	pte_unmap_unlock(pte - 1, ptl);
}