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
struct lg_cpu {int /*<<< orphan*/  cpu_pgd; } ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 unsigned long _PAGE_PRESENT ; 
 unsigned long _PAGE_RW ; 
 unsigned long pgd_flags (int /*<<< orphan*/ ) ; 
 unsigned long pmd_flags (int /*<<< orphan*/ ) ; 
 unsigned long pte_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * spgd_addr (struct lg_cpu*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/ * spmd_addr (struct lg_cpu*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/ * spte_addr (struct lg_cpu*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static bool page_writable(struct lg_cpu *cpu, unsigned long vaddr)
{
	pgd_t *spgd;
	unsigned long flags;

#ifdef CONFIG_X86_PAE
	pmd_t *spmd;
#endif
	/* Look at the current top level entry: is it present? */
	spgd = spgd_addr(cpu, cpu->cpu_pgd, vaddr);
	if (!(pgd_flags(*spgd) & _PAGE_PRESENT))
		return false;

#ifdef CONFIG_X86_PAE
	spmd = spmd_addr(cpu, *spgd, vaddr);
	if (!(pmd_flags(*spmd) & _PAGE_PRESENT))
		return false;
#endif

	/*
	 * Check the flags on the pte entry itself: it must be present and
	 * writable.
	 */
	flags = pte_flags(*(spte_addr(cpu, *spgd, vaddr)));

	return (flags & (_PAGE_PRESENT|_PAGE_RW)) == (_PAGE_PRESENT|_PAGE_RW);
}