#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;
struct TYPE_7__ {scalar_t__ kvm_seq; } ;
struct TYPE_11__ {TYPE_1__ context; } ;
struct TYPE_10__ {TYPE_6__* active_mm; } ;
struct TYPE_8__ {scalar_t__ kvm_seq; } ;
struct TYPE_9__ {TYPE_2__ context; } ;

/* Variables and functions */
 scalar_t__ PGDIR_SIZE ; 
 int PMD_TYPE_MASK ; 
 int PMD_TYPE_TABLE ; 
 int SZ_1M ; 
 int /*<<< orphan*/  __check_kvm_seq (TYPE_6__*) ; 
 TYPE_5__* current ; 
 int /*<<< orphan*/  flush_cache_vunmap (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  flush_tlb_kernel_range (unsigned long,unsigned long) ; 
 TYPE_3__ init_mm ; 
 int /*<<< orphan*/ * pgd_offset_k (unsigned long) ; 
 int /*<<< orphan*/  pmd_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pmd_page_vaddr (int /*<<< orphan*/ ) ; 
 int pmd_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_free_kernel (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unmap_area_sections(unsigned long virt, unsigned long size)
{
	unsigned long addr = virt, end = virt + (size & ~(SZ_1M - 1));
	pgd_t *pgd;

	flush_cache_vunmap(addr, end);
	pgd = pgd_offset_k(addr);
	do {
		pmd_t pmd, *pmdp = pmd_offset(pgd, addr);

		pmd = *pmdp;
		if (!pmd_none(pmd)) {
			/*
			 * Clear the PMD from the page table, and
			 * increment the kvm sequence so others
			 * notice this change.
			 *
			 * Note: this is still racy on SMP machines.
			 */
			pmd_clear(pmdp);
			init_mm.context.kvm_seq++;

			/*
			 * Free the page table, if there was one.
			 */
			if ((pmd_val(pmd) & PMD_TYPE_MASK) == PMD_TYPE_TABLE)
				pte_free_kernel(&init_mm, pmd_page_vaddr(pmd));
		}

		addr += PGDIR_SIZE;
		pgd++;
	} while (addr < end);

	/*
	 * Ensure that the active_mm is up to date - we want to
	 * catch any use-after-iounmap cases.
	 */
	if (current->active_mm->context.kvm_seq != init_mm.context.kvm_seq)
		__check_kvm_seq(current->active_mm);

	flush_tlb_kernel_range(virt, end);
}