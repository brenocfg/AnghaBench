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
struct vm_area_struct {int dummy; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;
struct TYPE_2__ {int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 int FOLL_TOUCH ; 
 int FOLL_WRITE ; 
 unsigned long long IA64_MAX_PHYS_BITS ; 
 unsigned long KERNEL_START ; 
 unsigned long KERNEL_TR_PAGE_SIZE ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 int REGION_NUMBER (unsigned long) ; 
 unsigned long long REGION_OFFSET (unsigned long) ; 
 unsigned long TASK_SIZE ; 
 unsigned long _PFN_MASK ; 
 unsigned long __pa (unsigned long) ; 
 TYPE_1__* current ; 
 struct vm_area_struct* find_extend_vma (int /*<<< orphan*/ ,unsigned long) ; 
 struct page* follow_page (struct vm_area_struct*,unsigned long,int) ; 
 int /*<<< orphan*/  ia64_tpa (unsigned long) ; 
 unsigned long kernel_virtual_offset ; 
 unsigned long page_to_pfn (struct page*) ; 
 scalar_t__ pgd_bad (int /*<<< orphan*/ ) ; 
 scalar_t__ pgd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pgd_offset_k (unsigned long) ; 
 scalar_t__ pmd_bad (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/ * pte_offset_kernel (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long pte_val (int /*<<< orphan*/ ) ; 
 scalar_t__ pud_bad (int /*<<< orphan*/ ) ; 
 scalar_t__ pud_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,unsigned long) ; 

unsigned long
xencomm_vtop(unsigned long vaddr)
{
	struct page *page;
	struct vm_area_struct *vma;

	if (vaddr == 0)
		return 0UL;

	if (REGION_NUMBER(vaddr) == 5) {
		pgd_t *pgd;
		pud_t *pud;
		pmd_t *pmd;
		pte_t *ptep;

		/* On ia64, TASK_SIZE refers to current.  It is not initialized
		   during boot.
		   Furthermore the kernel is relocatable and __pa() doesn't
		   work on  addresses.  */
		if (vaddr >= KERNEL_START
		    && vaddr < (KERNEL_START + KERNEL_TR_PAGE_SIZE))
			return vaddr - kernel_virtual_offset;

		/* In kernel area -- virtually mapped.  */
		pgd = pgd_offset_k(vaddr);
		if (pgd_none(*pgd) || pgd_bad(*pgd))
			return ~0UL;

		pud = pud_offset(pgd, vaddr);
		if (pud_none(*pud) || pud_bad(*pud))
			return ~0UL;

		pmd = pmd_offset(pud, vaddr);
		if (pmd_none(*pmd) || pmd_bad(*pmd))
			return ~0UL;

		ptep = pte_offset_kernel(pmd, vaddr);
		if (!ptep)
			return ~0UL;

		return (pte_val(*ptep) & _PFN_MASK) | (vaddr & ~PAGE_MASK);
	}

	if (vaddr > TASK_SIZE) {
		/* percpu variables */
		if (REGION_NUMBER(vaddr) == 7 &&
		    REGION_OFFSET(vaddr) >= (1ULL << IA64_MAX_PHYS_BITS))
			ia64_tpa(vaddr);

		/* kernel address */
		return __pa(vaddr);
	}

	/* XXX double-check (lack of) locking */
	vma = find_extend_vma(current->mm, vaddr);
	if (!vma)
		return ~0UL;

	/* We assume the page is modified.  */
	page = follow_page(vma, vaddr, FOLL_WRITE | FOLL_TOUCH);
	if (!page)
		return ~0UL;

	return (page_to_pfn(page) << PAGE_SHIFT) | (vaddr & ~PAGE_MASK);
}