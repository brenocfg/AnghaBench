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
struct lg_cpu {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int PAGE_SHIFT ; 
 int _PAGE_PRESENT ; 
 int /*<<< orphan*/ * __va (int) ; 
 int pgd_flags (int /*<<< orphan*/ ) ; 
 int pgd_pfn (int /*<<< orphan*/ ) ; 
 int pmd_flags (int /*<<< orphan*/ ) ; 
 int pmd_pfn (int /*<<< orphan*/ ) ; 
 size_t pte_index (unsigned long) ; 
 int /*<<< orphan*/ * spmd_addr (struct lg_cpu*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static pte_t *spte_addr(struct lg_cpu *cpu, pgd_t spgd, unsigned long vaddr)
{
#ifdef CONFIG_X86_PAE
	pmd_t *pmd = spmd_addr(cpu, spgd, vaddr);
	pte_t *page = __va(pmd_pfn(*pmd) << PAGE_SHIFT);

	/* You should never call this if the PMD entry wasn't valid */
	BUG_ON(!(pmd_flags(*pmd) & _PAGE_PRESENT));
#else
	pte_t *page = __va(pgd_pfn(spgd) << PAGE_SHIFT);
	/* You should never call this if the PGD entry wasn't valid */
	BUG_ON(!(pgd_flags(spgd) & _PAGE_PRESENT));
#endif

	return &page[pte_index(vaddr)];
}