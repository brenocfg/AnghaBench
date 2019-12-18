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
struct vm_area_struct {int /*<<< orphan*/  vm_mm; } ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int HPAGE_SHIFT ; 
 int PAGE_SHIFT ; 
 scalar_t__ is_vm_hugetlb_page (struct vm_area_struct*) ; 
 int pgd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pgd_offset (int /*<<< orphan*/ ,unsigned long) ; 
 int pmd_large (int /*<<< orphan*/ ) ; 
 int pmd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pte_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_kernel (int /*<<< orphan*/ *,unsigned long) ; 
 int pte_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_write (int /*<<< orphan*/ ) ; 
 int pud_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int atomic_pte_lookup(struct vm_area_struct *vma, unsigned long vaddr,
	int write, unsigned long *paddr, int *pageshift)
{
	pgd_t *pgdp;
	pmd_t *pmdp;
	pud_t *pudp;
	pte_t pte;

	pgdp = pgd_offset(vma->vm_mm, vaddr);
	if (unlikely(pgd_none(*pgdp)))
		goto err;

	pudp = pud_offset(pgdp, vaddr);
	if (unlikely(pud_none(*pudp)))
		goto err;

	pmdp = pmd_offset(pudp, vaddr);
	if (unlikely(pmd_none(*pmdp)))
		goto err;
#ifdef CONFIG_X86_64
	if (unlikely(pmd_large(*pmdp)))
		pte = *(pte_t *) pmdp;
	else
#endif
		pte = *pte_offset_kernel(pmdp, vaddr);

	if (unlikely(!pte_present(pte) ||
		     (write && (!pte_write(pte) || !pte_dirty(pte)))))
		return 1;

	*paddr = pte_pfn(pte) << PAGE_SHIFT;
#ifdef CONFIG_HUGETLB_PAGE
	*pageshift = is_vm_hugetlb_page(vma) ? HPAGE_SHIFT : PAGE_SHIFT;
#else
	*pageshift = PAGE_SHIFT;
#endif
	return 0;

err:
	return 1;
}