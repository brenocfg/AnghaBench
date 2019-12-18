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
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pte_fn_t ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int apply_to_pte_range (struct mm_struct*,int /*<<< orphan*/ *,unsigned long,unsigned long,int /*<<< orphan*/ ,void*) ; 
 unsigned long pmd_addr_end (unsigned long,unsigned long) ; 
 int /*<<< orphan*/ * pmd_alloc (struct mm_struct*,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pud_huge (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int apply_to_pmd_range(struct mm_struct *mm, pud_t *pud,
				     unsigned long addr, unsigned long end,
				     pte_fn_t fn, void *data)
{
	pmd_t *pmd;
	unsigned long next;
	int err;

	BUG_ON(pud_huge(*pud));

	pmd = pmd_alloc(mm, pud, addr);
	if (!pmd)
		return -ENOMEM;
	do {
		next = pmd_addr_end(addr, end);
		err = apply_to_pte_range(mm, pmd, addr, next, fn, data);
		if (err)
			break;
	} while (pmd++, addr = next, addr != end);
	return err;
}