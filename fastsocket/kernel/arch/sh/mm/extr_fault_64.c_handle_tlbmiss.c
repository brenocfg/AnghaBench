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
 scalar_t__ TASK_SIZE ; 
 int /*<<< orphan*/  __do_tlb_refill (unsigned long,unsigned long long,int /*<<< orphan*/ *) ; 
 scalar_t__ pgd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pgd_offset (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/  pgd_present (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pmd_present (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_kernel (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pte_present (int /*<<< orphan*/ ) ; 
 unsigned long long pte_val (int /*<<< orphan*/ ) ; 
 scalar_t__ pud_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pud_present (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_tlbmiss(struct mm_struct *mm,
			  unsigned long long protection_flags,
			  unsigned long long textaccess,
			  unsigned long address)
{
	pgd_t *dir;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;
	pte_t entry;

	/* NB. The PGD currently only contains a single entry - there is no
	   page table tree stored for the top half of the address space since
	   virtual pages in that region should never be mapped in user mode.
	   (In kernel mode, the only things in that region are the 512Mb super
	   page (locked in), and vmalloc (modules) +  I/O device pages (handled
	   by handle_vmalloc_fault), so no PGD for the upper half is required
	   by kernel mode either).

	   See how mm->pgd is allocated and initialised in pgd_alloc to see why
	   the next test is necessary.  - RPC */
	if (address >= (unsigned long) TASK_SIZE)
		/* upper half - never has page table entries. */
		return 0;

	dir = pgd_offset(mm, address);
	if (pgd_none(*dir) || !pgd_present(*dir))
		return 0;
	if (!pgd_present(*dir))
		return 0;

	pud = pud_offset(dir, address);
	if (pud_none(*pud) || !pud_present(*pud))
		return 0;

	pmd = pmd_offset(pud, address);
	if (pmd_none(*pmd) || !pmd_present(*pmd))
		return 0;

	pte = pte_offset_kernel(pmd, address);
	entry = *pte;

	if (pte_none(entry) || !pte_present(entry))
		return 0;

	/*
	 * If the page doesn't have sufficient protection bits set to
	 * service the kind of fault being handled, there's not much
	 * point doing the TLB refill.  Punt the fault to the general
	 * handler.
	 */
	if ((pte_val(entry) & protection_flags) != protection_flags)
		return 0;

        __do_tlb_refill(address, textaccess, pte);

	return 1;
}