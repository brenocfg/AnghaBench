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
struct mmu_gather {TYPE_1__* mm; } ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgtable_t ;
struct TYPE_2__ {int /*<<< orphan*/  nr_ptes; } ;

/* Variables and functions */
 int /*<<< orphan*/  pmd_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmd_pgtable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_free_tlb (struct mmu_gather*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void free_pte_range(struct mmu_gather *tlb, pmd_t *pmd,
			   unsigned long addr)
{
	pgtable_t token = pmd_pgtable(*pmd);
	pmd_clear(pmd);
	pte_free_tlb(tlb, token, addr);
	tlb->mm->nr_ptes--;
}