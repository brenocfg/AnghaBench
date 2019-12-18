#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mm_struct {int /*<<< orphan*/  pgd; } ;
struct TYPE_3__ {int /*<<< orphan*/  pte_low; int /*<<< orphan*/  pte_high; } ;
typedef  TYPE_1__ pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  LHCALL_SET_PTE ; 
 int /*<<< orphan*/  __pa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lazy_hcall3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lazy_hcall4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lguest_pte_update(struct mm_struct *mm, unsigned long addr,
			       pte_t *ptep)
{
#ifdef CONFIG_X86_PAE
	/* PAE needs to hand a 64 bit page table entry, so it uses two args. */
	lazy_hcall4(LHCALL_SET_PTE, __pa(mm->pgd), addr,
		    ptep->pte_low, ptep->pte_high);
#else
	lazy_hcall3(LHCALL_SET_PTE, __pa(mm->pgd), addr, ptep->pte_low);
#endif
}