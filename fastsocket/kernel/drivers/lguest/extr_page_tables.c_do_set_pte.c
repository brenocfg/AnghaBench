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
 int _PAGE_ACCESSED ; 
 int _PAGE_DIRTY ; 
 int _PAGE_PRESENT ; 
 int /*<<< orphan*/  __pte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_gpte (struct lg_cpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpte_to_spte (struct lg_cpu*,int /*<<< orphan*/ ,int) ; 
 int pgd_flags (int /*<<< orphan*/ ) ; 
 int pmd_flags (int /*<<< orphan*/ ) ; 
 int pte_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_pte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pte (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * spgd_addr (struct lg_cpu*,int,unsigned long) ; 
 int /*<<< orphan*/ * spmd_addr (struct lg_cpu*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/ * spte_addr (struct lg_cpu*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void do_set_pte(struct lg_cpu *cpu, int idx,
		       unsigned long vaddr, pte_t gpte)
{
	/* Look up the matching shadow page directory entry. */
	pgd_t *spgd = spgd_addr(cpu, idx, vaddr);
#ifdef CONFIG_X86_PAE
	pmd_t *spmd;
#endif

	/* If the top level isn't present, there's no entry to update. */
	if (pgd_flags(*spgd) & _PAGE_PRESENT) {
#ifdef CONFIG_X86_PAE
		spmd = spmd_addr(cpu, *spgd, vaddr);
		if (pmd_flags(*spmd) & _PAGE_PRESENT) {
#endif
			/* Otherwise, start by releasing the existing entry. */
			pte_t *spte = spte_addr(cpu, *spgd, vaddr);
			release_pte(*spte);

			/*
			 * If they're setting this entry as dirty or accessed,
			 * we might as well put that entry they've given us in
			 * now.  This shaves 10% off a copy-on-write
			 * micro-benchmark.
			 */
			if (pte_flags(gpte) & (_PAGE_DIRTY | _PAGE_ACCESSED)) {
				check_gpte(cpu, gpte);
				set_pte(spte,
					gpte_to_spte(cpu, gpte,
						pte_flags(gpte) & _PAGE_DIRTY));
			} else {
				/*
				 * Otherwise kill it and we can demand_page()
				 * it in later.
				 */
				set_pte(spte, __pte(0));
			}
#ifdef CONFIG_X86_PAE
		}
#endif
	}
}