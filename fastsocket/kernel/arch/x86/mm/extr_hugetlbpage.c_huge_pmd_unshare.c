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
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 unsigned long ALIGN (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned long HPAGE_SIZE ; 
 unsigned long PTRS_PER_PTE ; 
 int page_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pgd_offset (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/  pud_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_page (int /*<<< orphan*/ *) ; 

int huge_pmd_unshare(struct mm_struct *mm, unsigned long *addr, pte_t *ptep)
{
	pgd_t *pgd = pgd_offset(mm, *addr);
	pud_t *pud = pud_offset(pgd, *addr);

	BUG_ON(page_count(virt_to_page(ptep)) == 0);
	if (page_count(virt_to_page(ptep)) == 1)
		return 0;

	pud_clear(pud);
	put_page(virt_to_page(ptep));
	*addr = ALIGN(*addr, HPAGE_SIZE * PTRS_PER_PTE) - HPAGE_SIZE;
	return 1;
}