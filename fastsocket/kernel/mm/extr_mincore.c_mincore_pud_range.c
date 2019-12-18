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
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  mincore_pmd_range (struct vm_area_struct*,int /*<<< orphan*/ *,unsigned long,unsigned long,unsigned char*) ; 
 int /*<<< orphan*/  mincore_unmapped_range (struct vm_area_struct*,unsigned long,unsigned long,unsigned char*) ; 
 unsigned long pud_addr_end (unsigned long,unsigned long) ; 
 scalar_t__ pud_none_or_clear_bad (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void mincore_pud_range(struct vm_area_struct *vma, pgd_t *pgd,
			unsigned long addr, unsigned long end,
			unsigned char *vec)
{
	unsigned long next;
	pud_t *pud;

	pud = pud_offset(pgd, addr);
	do {
		next = pud_addr_end(addr, end);
		if (pud_none_or_clear_bad(pud))
			mincore_unmapped_range(vma, addr, next, vec);
		else
			mincore_pmd_range(vma, pud, addr, next, vec);
		vec += (next - addr) >> PAGE_SHIFT;
	} while (pud++, addr = next, addr != end);
}