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
struct vm_area_struct {struct mm_struct* vm_mm; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct mm_struct {TYPE_1__ context; } ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  FINISH_FLUSH ; 
 scalar_t__ Hash ; 
 unsigned long TASK_SIZE ; 
 int /*<<< orphan*/  _tlbie (unsigned long) ; 
 int /*<<< orphan*/  flush_hash_pages (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int) ; 
 struct mm_struct init_mm ; 
 int /*<<< orphan*/  pgd_offset (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/  pmd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  pmd_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pud_offset (int /*<<< orphan*/ ,unsigned long) ; 

void flush_tlb_page(struct vm_area_struct *vma, unsigned long vmaddr)
{
	struct mm_struct *mm;
	pmd_t *pmd;

	if (Hash == 0) {
		_tlbie(vmaddr);
		return;
	}
	mm = (vmaddr < TASK_SIZE)? vma->vm_mm: &init_mm;
	pmd = pmd_offset(pud_offset(pgd_offset(mm, vmaddr), vmaddr), vmaddr);
	if (!pmd_none(*pmd))
		flush_hash_pages(mm->context.id, vmaddr, pmd_val(*pmd), 1);
	FINISH_FLUSH;
}