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
struct TYPE_2__ {int /*<<< orphan*/ * stub_pages; } ;
struct mm_struct {TYPE_1__ context; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  STUB_CODE ; 
 int /*<<< orphan*/  STUB_DATA ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pte_clear (struct mm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * virt_to_pte (struct mm_struct*,int /*<<< orphan*/ ) ; 

void arch_exit_mmap(struct mm_struct *mm)
{
	pte_t *pte;

	if (mm->context.stub_pages != NULL)
		kfree(mm->context.stub_pages);
	pte = virt_to_pte(mm, STUB_CODE);
	if (pte != NULL)
		pte_clear(mm, STUB_CODE, pte);

	pte = virt_to_pte(mm, STUB_DATA);
	if (pte == NULL)
		return;

	pte_clear(mm, STUB_DATA, pte);
}