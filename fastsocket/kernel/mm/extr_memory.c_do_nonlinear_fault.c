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
struct vm_area_struct {int vm_flags; } ;
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgoff_t ;

/* Variables and functions */
 unsigned int FAULT_FLAG_NONLINEAR ; 
 int VM_FAULT_SIGBUS ; 
 int VM_NONLINEAR ; 
 int __do_fault (struct mm_struct*,struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_bad_pte (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pte_to_pgoff (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_unmap_same (struct mm_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int do_nonlinear_fault(struct mm_struct *mm, struct vm_area_struct *vma,
		unsigned long address, pte_t *page_table, pmd_t *pmd,
		unsigned int flags, pte_t orig_pte)
{
	pgoff_t pgoff;

	flags |= FAULT_FLAG_NONLINEAR;

	if (!pte_unmap_same(mm, pmd, page_table, orig_pte))
		return 0;

	if (unlikely(!(vma->vm_flags & VM_NONLINEAR))) {
		/*
		 * Page table corrupted: show pte and kill process.
		 */
		print_bad_pte(vma, address, orig_pte, NULL);
		return VM_FAULT_SIGBUS;
	}

	pgoff = pte_to_pgoff(orig_pte);
	return __do_fault(mm, vma, address, pmd, pgoff, flags, orig_pte);
}