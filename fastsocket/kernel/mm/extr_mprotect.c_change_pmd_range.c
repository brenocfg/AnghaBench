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
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 unsigned long HPAGE_PMD_SIZE ; 
 scalar_t__ change_huge_pmd (struct vm_area_struct*,int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  change_pte_range (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long,unsigned long,int /*<<< orphan*/ ,int) ; 
 unsigned long pmd_addr_end (unsigned long,unsigned long) ; 
 scalar_t__ pmd_none_or_clear_bad (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ pmd_trans_huge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  split_huge_page_pmd (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void change_pmd_range(struct vm_area_struct *vma, pud_t *pud,
		unsigned long addr, unsigned long end, pgprot_t newprot,
		int dirty_accountable)
{
	pmd_t *pmd;
	unsigned long next;

	pmd = pmd_offset(pud, addr);
	do {
		next = pmd_addr_end(addr, end);
		if (pmd_trans_huge(*pmd)) {
			if (next - addr != HPAGE_PMD_SIZE)
				split_huge_page_pmd(vma->vm_mm, pmd);
			else if (change_huge_pmd(vma, pmd, addr, newprot))
				continue;
			/* fall through */
		}
		if (pmd_none_or_clear_bad(pmd))
			continue;
		change_pte_range(vma->vm_mm, pmd, addr, next, newprot,
				 dirty_accountable);
	} while (pmd++, addr = next, addr != end);
}