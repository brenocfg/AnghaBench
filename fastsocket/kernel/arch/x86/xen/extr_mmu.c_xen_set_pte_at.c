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
struct multicall_space {int /*<<< orphan*/  mc; } ;
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;
struct TYPE_2__ {struct mm_struct* mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_STATS (int /*<<< orphan*/ ,int) ; 
 scalar_t__ HYPERVISOR_update_va_mapping (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MULTI_update_va_mapping (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PARAVIRT_LAZY_MMU ; 
 TYPE_1__* current ; 
 struct mm_struct init_mm ; 
 scalar_t__ paravirt_get_lazy_mode () ; 
 int /*<<< orphan*/  set_pte_at ; 
 int /*<<< orphan*/  set_pte_at_batched ; 
 int /*<<< orphan*/  set_pte_at_current ; 
 int /*<<< orphan*/  set_pte_at_kernel ; 
 struct multicall_space xen_mc_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xen_mc_issue (scalar_t__) ; 
 int /*<<< orphan*/  xen_set_pte (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void xen_set_pte_at(struct mm_struct *mm, unsigned long addr,
		    pte_t *ptep, pte_t pteval)
{
	ADD_STATS(set_pte_at, 1);
//	ADD_STATS(set_pte_at_pinned, xen_page_pinned(ptep));
	ADD_STATS(set_pte_at_current, mm == current->mm);
	ADD_STATS(set_pte_at_kernel, mm == &init_mm);

	if (mm == current->mm || mm == &init_mm) {
		if (paravirt_get_lazy_mode() == PARAVIRT_LAZY_MMU) {
			struct multicall_space mcs;
			mcs = xen_mc_entry(0);

			MULTI_update_va_mapping(mcs.mc, addr, pteval, 0);
			ADD_STATS(set_pte_at_batched, 1);
			xen_mc_issue(PARAVIRT_LAZY_MMU);
			goto out;
		} else
			if (HYPERVISOR_update_va_mapping(addr, pteval, 0) == 0)
				goto out;
	}
	xen_set_pte(ptep, pteval);

out:	return;
}