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
struct TYPE_2__ {int /*<<< orphan*/  huge_pte_count; } ;
struct mm_struct {TYPE_1__ context; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 unsigned long HPAGE_MASK ; 
 int HUGETLB_PAGE_ORDER ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  pte_clear (struct mm_struct*,unsigned long,int /*<<< orphan*/ *) ; 
 scalar_t__ pte_present (int /*<<< orphan*/ ) ; 

pte_t huge_ptep_get_and_clear(struct mm_struct *mm, unsigned long addr,
			      pte_t *ptep)
{
	pte_t entry;
	int i;

	entry = *ptep;
	if (pte_present(entry))
		mm->context.huge_pte_count--;

	addr &= HPAGE_MASK;

	for (i = 0; i < (1 << HUGETLB_PAGE_ORDER); i++) {
		pte_clear(mm, addr, ptep);
		addr += PAGE_SIZE;
		ptep++;
	}

	return entry;
}