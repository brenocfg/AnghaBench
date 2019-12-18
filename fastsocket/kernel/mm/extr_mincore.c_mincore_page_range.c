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
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  mincore_pud_range (struct vm_area_struct*,int /*<<< orphan*/ *,unsigned long,unsigned long,unsigned char*) ; 
 int /*<<< orphan*/  mincore_unmapped_range (struct vm_area_struct*,unsigned long,unsigned long,unsigned char*) ; 
 unsigned long pgd_addr_end (unsigned long,unsigned long) ; 
 scalar_t__ pgd_none_or_clear_bad (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pgd_offset (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void mincore_page_range(struct vm_area_struct *vma,
			unsigned long addr, unsigned long end,
			unsigned char *vec)
{
	unsigned long next;
	pgd_t *pgd;

	pgd = pgd_offset(vma->vm_mm, addr);
	do {
		next = pgd_addr_end(addr, end);
		if (pgd_none_or_clear_bad(pgd))
			mincore_unmapped_range(vma, addr, next, vec);
		else
			mincore_pud_range(vma, pgd, addr, next, vec);
		vec += (next - addr) >> PAGE_SHIFT;
	} while (pgd++, addr = next, addr != end);
}