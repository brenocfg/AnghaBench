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
struct vm_area_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 scalar_t__ mincore_huge_pmd (struct vm_area_struct*,int /*<<< orphan*/ *,unsigned long,unsigned long,unsigned char*) ; 
 int /*<<< orphan*/  mincore_pte_range (struct vm_area_struct*,int /*<<< orphan*/ *,unsigned long,unsigned long,unsigned char*) ; 
 int /*<<< orphan*/  mincore_unmapped_range (struct vm_area_struct*,unsigned long,unsigned long,unsigned char*) ; 
 unsigned long pmd_addr_end (unsigned long,unsigned long) ; 
 scalar_t__ pmd_none_or_trans_huge_or_clear_bad (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ pmd_trans_huge (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mincore_pmd_range(struct vm_area_struct *vma, pud_t *pud,
			unsigned long addr, unsigned long end,
			unsigned char *vec)
{
	unsigned long next;
	pmd_t *pmd;

	pmd = pmd_offset(pud, addr);
	do {
		next = pmd_addr_end(addr, end);
		if (pmd_trans_huge(*pmd)) {
			if (mincore_huge_pmd(vma, pmd, addr, next, vec)) {
				vec += (next - addr) >> PAGE_SHIFT;
				continue;
			}
			/* fall through */
		}
		if (pmd_none_or_trans_huge_or_clear_bad(pmd))
			mincore_unmapped_range(vma, addr, next, vec);
		else
			mincore_pte_range(vma, pmd, addr, next, vec);
		vec += (next - addr) >> PAGE_SHIFT;
	} while (pmd++, addr = next, addr != end);
}