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
struct vm_area_struct {unsigned long vm_start; int vm_flags; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; } ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;
struct TYPE_2__ {int /*<<< orphan*/  min_flt; int /*<<< orphan*/  maj_flt; struct mm_struct* mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCH_IS_STACKGROW (unsigned long) ; 
 int /*<<< orphan*/  BUG () ; 
 int EACCES ; 
 int EFAULT ; 
 int /*<<< orphan*/  FAULT_FLAG_WRITE ; 
 int SEGV_ACCERR ; 
 int SEGV_MAPERR ; 
 int VM_EXEC ; 
 int VM_FAULT_ERROR ; 
 int VM_FAULT_MAJOR ; 
 int VM_FAULT_OOM ; 
 int VM_FAULT_SIGBUS ; 
 int VM_GROWSDOWN ; 
 int VM_READ ; 
 int VM_WRITE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 scalar_t__ expand_stack (struct vm_area_struct*,unsigned long) ; 
 struct vm_area_struct* find_vma (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/  flush_tlb_page (struct vm_area_struct*,unsigned long) ; 
 int handle_mm_fault (struct mm_struct*,struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ in_atomic () ; 
 int /*<<< orphan*/  pagefault_out_of_memory () ; 
 int /*<<< orphan*/ * pgd_offset (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pte_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_kernel (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pte_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_young (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int handle_page_fault(unsigned long address, unsigned long ip,
		      int is_write, int is_user, int *code_out)
{
	struct mm_struct *mm = current->mm;
	struct vm_area_struct *vma;
	pgd_t *pgd;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;
	int err = -EFAULT;

	*code_out = SEGV_MAPERR;

	/*
	 * If the fault was during atomic operation, don't take the fault, just
	 * fail.
	 */
	if (in_atomic())
		goto out_nosemaphore;

	down_read(&mm->mmap_sem);
	vma = find_vma(mm, address);
	if (!vma)
		goto out;
	else if (vma->vm_start <= address)
		goto good_area;
	else if (!(vma->vm_flags & VM_GROWSDOWN))
		goto out;
	else if (is_user && !ARCH_IS_STACKGROW(address))
		goto out;
	else if (expand_stack(vma, address))
		goto out;

good_area:
	*code_out = SEGV_ACCERR;
	if (is_write && !(vma->vm_flags & VM_WRITE))
		goto out;

	/* Don't require VM_READ|VM_EXEC for write faults! */
	if (!is_write && !(vma->vm_flags & (VM_READ | VM_EXEC)))
		goto out;

	do {
		int fault;

		fault = handle_mm_fault(mm, vma, address, is_write ? FAULT_FLAG_WRITE : 0);
		if (unlikely(fault & VM_FAULT_ERROR)) {
			if (fault & VM_FAULT_OOM) {
				goto out_of_memory;
			} else if (fault & VM_FAULT_SIGBUS) {
				err = -EACCES;
				goto out;
			}
			BUG();
		}
		if (fault & VM_FAULT_MAJOR)
			current->maj_flt++;
		else
			current->min_flt++;

		pgd = pgd_offset(mm, address);
		pud = pud_offset(pgd, address);
		pmd = pmd_offset(pud, address);
		pte = pte_offset_kernel(pmd, address);
	} while (!pte_present(*pte));
	err = 0;
	/*
	 * The below warning was added in place of
	 *	pte_mkyoung(); if (is_write) pte_mkdirty();
	 * If it's triggered, we'd see normally a hang here (a clean pte is
	 * marked read-only to emulate the dirty bit).
	 * However, the generic code can mark a PTE writable but clean on a
	 * concurrent read fault, triggering this harmlessly. So comment it out.
	 */
#if 0
	WARN_ON(!pte_young(*pte) || (is_write && !pte_dirty(*pte)));
#endif
	flush_tlb_page(vma, address);
out:
	up_read(&mm->mmap_sem);
out_nosemaphore:
	return err;

out_of_memory:
	/*
	 * We ran out of memory, call the OOM killer, and return the userspace
	 * (which will retry the fault, or kill us if we got oom-killed).
	 */
	up_read(&mm->mmap_sem);
	pagefault_out_of_memory();
	return 0;
}