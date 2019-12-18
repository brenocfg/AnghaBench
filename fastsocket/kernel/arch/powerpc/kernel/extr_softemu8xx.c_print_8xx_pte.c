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
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 int /*<<< orphan*/ * pgd_offset (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ pmd_present (int /*<<< orphan*/ ) ; 
 int pp ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/ * pte_offset_kernel (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ pte_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pud_offset (int /*<<< orphan*/ *,unsigned long) ; 

void print_8xx_pte(struct mm_struct *mm, unsigned long addr)
{
	pgd_t *pgd;
	pmd_t *pmd;
	pte_t *pte;

	printk(" pte @ 0x%8lx: ", addr);
	pgd = pgd_offset(mm, addr & PAGE_MASK);
	if (pgd) {
		pmd = pmd_offset(pud_offset(pgd, addr & PAGE_MASK),
		                 addr & PAGE_MASK);
		if (pmd && pmd_present(*pmd)) {
			pte = pte_offset_kernel(pmd, addr & PAGE_MASK);
			if (pte) {
				printk(" (0x%08lx)->(0x%08lx)->0x%08lx\n",
				        (long)pgd, (long)pte, (long)pte_val(*pte));
#define pp ((long)pte_val(*pte))
				printk(" RPN: %05lx PP: %lx SPS: %lx SH: %lx "
				       "CI: %lx v: %lx\n",
				       pp>>12,    /* rpn */
				       (pp>>10)&3, /* pp */
				       (pp>>3)&1, /* small */
				       (pp>>2)&1, /* shared */
				       (pp>>1)&1, /* cache inhibit */
				       pp&1       /* valid */
				       );
#undef pp
			}
			else {
				printk("no pte\n");
			}
		}
		else {
			printk("no pmd\n");
		}
	}
	else {
		printk("no pgd\n");
	}
}