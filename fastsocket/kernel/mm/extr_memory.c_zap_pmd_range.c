#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct zap_details {int dummy; } ;
struct vm_area_struct {int /*<<< orphan*/  vm_mm; } ;
struct mmu_gather {TYPE_1__* mm; } ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pmd_t ;
struct TYPE_2__ {int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 unsigned long HPAGE_PMD_SIZE ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 unsigned long pmd_addr_end (unsigned long,unsigned long) ; 
 scalar_t__ pmd_none_or_trans_huge_or_clear_bad (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ pmd_trans_huge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rwsem_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  split_huge_page_pmd (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ zap_huge_pmd (struct mmu_gather*,struct vm_area_struct*,int /*<<< orphan*/ *) ; 
 unsigned long zap_pte_range (struct mmu_gather*,struct vm_area_struct*,int /*<<< orphan*/ *,unsigned long,unsigned long,long*,struct zap_details*) ; 

__attribute__((used)) static inline unsigned long zap_pmd_range(struct mmu_gather *tlb,
				struct vm_area_struct *vma, pud_t *pud,
				unsigned long addr, unsigned long end,
				long *zap_work, struct zap_details *details)
{
	pmd_t *pmd;
	unsigned long next;

	pmd = pmd_offset(pud, addr);
	do {
		next = pmd_addr_end(addr, end);
		if (pmd_trans_huge(*pmd)) {
			if (next-addr != HPAGE_PMD_SIZE) {
				VM_BUG_ON(!rwsem_is_locked(&tlb->mm->mmap_sem));
				split_huge_page_pmd(vma->vm_mm, pmd);
			} else if (zap_huge_pmd(tlb, vma, pmd)) {
				(*zap_work)--;
				continue;
			}
			/* fall through */
		}
		/*
		 * Here there can be other concurrent MADV_DONTNEED or
		 * trans huge page faults running, and if the pmd is
		 * none or trans huge it can change under us. This is
		 * because MADV_DONTNEED holds the mmap_sem in read
		 * mode.
		 */
		if (pmd_none_or_trans_huge_or_clear_bad(pmd)) {
			(*zap_work)--;
			continue;
		}
		next = zap_pte_range(tlb, vma, pmd, addr, next,
						zap_work, details);
	} while (pmd++, addr = next, (addr != end && *zap_work > 0));

	return addr;
}