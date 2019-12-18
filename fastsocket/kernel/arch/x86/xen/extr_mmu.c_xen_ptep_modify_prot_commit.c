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
struct mmu_update {int ptr; int /*<<< orphan*/  val; } ;
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;
struct TYPE_2__ {int maddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_STATS (int /*<<< orphan*/ ,int) ; 
 int MMU_PT_UPDATE_PRESERVE_AD ; 
 scalar_t__ PARAVIRT_LAZY_MMU ; 
 TYPE_1__ arbitrary_virt_to_machine (int /*<<< orphan*/ *) ; 
 scalar_t__ paravirt_get_lazy_mode () ; 
 int /*<<< orphan*/  prot_commit ; 
 int /*<<< orphan*/  prot_commit_batched ; 
 int /*<<< orphan*/  pte_val_ma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xen_extend_mmu_update (struct mmu_update*) ; 
 int /*<<< orphan*/  xen_mc_batch () ; 
 int /*<<< orphan*/  xen_mc_issue (scalar_t__) ; 

void xen_ptep_modify_prot_commit(struct mm_struct *mm, unsigned long addr,
				 pte_t *ptep, pte_t pte)
{
	struct mmu_update u;

	xen_mc_batch();

	u.ptr = arbitrary_virt_to_machine(ptep).maddr | MMU_PT_UPDATE_PRESERVE_AD;
	u.val = pte_val_ma(pte);
	xen_extend_mmu_update(&u);

	ADD_STATS(prot_commit, 1);
	ADD_STATS(prot_commit_batched, paravirt_get_lazy_mode() == PARAVIRT_LAZY_MMU);

	xen_mc_issue(PARAVIRT_LAZY_MMU);
}