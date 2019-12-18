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
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int /*<<< orphan*/  __do_tlb_refill (unsigned long,unsigned long long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pgd_offset_k (unsigned long) ; 
 scalar_t__ pmd_none_or_clear_bad (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ pte_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_kernel (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pte_present (int /*<<< orphan*/ ) ; 
 unsigned long pte_val (int /*<<< orphan*/ ) ; 
 scalar_t__ pud_none_or_clear_bad (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int handle_vmalloc_fault(struct mm_struct *mm,
				unsigned long protection_flags,
                                unsigned long long textaccess,
				unsigned long address)
{
	pgd_t *dir;
	pud_t *pud;
	pmd_t *pmd;
	static pte_t *pte;
	pte_t entry;

	dir = pgd_offset_k(address);

	pud = pud_offset(dir, address);
	if (pud_none_or_clear_bad(pud))
		return 0;

	pmd = pmd_offset(pud, address);
	if (pmd_none_or_clear_bad(pmd))
		return 0;

	pte = pte_offset_kernel(pmd, address);
	entry = *pte;

	if (pte_none(entry) || !pte_present(entry))
		return 0;
	if ((pte_val(entry) & protection_flags) != protection_flags)
		return 0;

        __do_tlb_refill(address, textaccess, pte);

	return 1;
}