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
struct vm_area_struct {int /*<<< orphan*/  vm_ops; } ;
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 unsigned int FAULT_FLAG_WRITE ; 
 int /*<<< orphan*/  PGFAULT ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int VM_FAULT_OOM ; 
 int __pte_alloc (struct mm_struct*,struct vm_area_struct*,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  count_vm_event (int /*<<< orphan*/ ) ; 
 int do_huge_pmd_anonymous_page (struct mm_struct*,struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *,unsigned int) ; 
 int do_huge_pmd_wp_page (struct mm_struct*,struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int handle_pte_fault (struct mm_struct*,struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int hugetlb_fault (struct mm_struct*,struct vm_area_struct*,unsigned long,unsigned int) ; 
 int is_vm_hugetlb_page (struct vm_area_struct*) ; 
 int /*<<< orphan*/ * pgd_offset (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/ * pmd_alloc (struct mm_struct*,int /*<<< orphan*/ *,unsigned long) ; 
 int pmd_none (int /*<<< orphan*/ ) ; 
 int pmd_trans_huge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_trans_splitting (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_map (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/ * pud_alloc (struct mm_struct*,int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ transparent_hugepage_enabled (struct vm_area_struct*) ; 
 scalar_t__ unlikely (int) ; 

int handle_mm_fault(struct mm_struct *mm, struct vm_area_struct *vma,
		unsigned long address, unsigned int flags)
{
	pgd_t *pgd;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;

	__set_current_state(TASK_RUNNING);

	count_vm_event(PGFAULT);

	if (unlikely(is_vm_hugetlb_page(vma)))
		return hugetlb_fault(mm, vma, address, flags);

retry:
	pgd = pgd_offset(mm, address);
	pud = pud_alloc(mm, pgd, address);
	if (!pud)
		return VM_FAULT_OOM;
	pmd = pmd_alloc(mm, pud, address);
	if (!pmd)
		return VM_FAULT_OOM;
	if (pmd_none(*pmd) && transparent_hugepage_enabled(vma)) {
		if (!vma->vm_ops)
			return do_huge_pmd_anonymous_page(mm, vma, address,
							  pmd, flags);
	} else {
		pmd_t orig_pmd = *pmd;
		int ret;

		barrier();
		if (pmd_trans_huge(orig_pmd)) {
			if (flags & FAULT_FLAG_WRITE &&
			    !pmd_write(orig_pmd) &&
			    !pmd_trans_splitting(orig_pmd)) {
				ret = do_huge_pmd_wp_page(mm, vma, address, pmd,
							  orig_pmd);
				/*
				 * If COW results in an oom, the huge pmd will
				 * have been split, so retry the fault on the
				 * pte for a smaller charge.
				 */
				if (unlikely(ret & VM_FAULT_OOM))
					goto retry;
				return ret;
			}
			return 0;
		}
	}

	/*
	 * Use __pte_alloc instead of pte_alloc_map, because we can't
	 * run pte_offset_map on the pmd, if an huge pmd could
	 * materialize from under us from a different thread.
	 */
	if (unlikely(pmd_none(*pmd)) &&
	    unlikely(__pte_alloc(mm, vma, pmd, address)))
		return VM_FAULT_OOM;
	/* if an huge pmd materialized from under us just retry later */
	if (unlikely(pmd_trans_huge(*pmd)))
		return 0;
	/*
	 * A regular pmd is established and it can't morph into a huge pmd
	 * from under us anymore at this point because we hold the mmap_sem
	 * read mode and khugepaged takes it in write mode. So now it's
	 * safe to run pte_offset_map().
	 */
	pte = pte_offset_map(pmd, address);

	return handle_pte_fault(mm, vma, address, pte, pmd, flags);
}