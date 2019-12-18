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
 scalar_t__ pgd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pgd_offset (struct mm_struct*,unsigned long) ; 
 scalar_t__ pmd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ pte_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_kernel (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pte_present (int /*<<< orphan*/ ) ; 
 scalar_t__ pud_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static pte_t *lookup_pte(struct mm_struct *mm, unsigned long address)
{
	pgd_t *dir;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;
	pte_t entry;

	dir = pgd_offset(mm, address);
	if (pgd_none(*dir))
		return NULL;

	pud = pud_offset(dir, address);
	if (pud_none(*pud))
		return NULL;

	pmd = pmd_offset(pud, address);
	if (pmd_none(*pmd))
		return NULL;

	pte = pte_offset_kernel(pmd, address);
	entry = *pte;
	if (pte_none(entry) || !pte_present(entry))
		return NULL;

	return pte;
}