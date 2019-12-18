#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pte_low; int /*<<< orphan*/  pte_high; } ;
typedef  TYPE_1__ pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_STATS (int /*<<< orphan*/ ,int) ; 
 scalar_t__ PARAVIRT_LAZY_MMU ; 
 scalar_t__ paravirt_get_lazy_mode () ; 
 int /*<<< orphan*/  pte_update ; 
 int /*<<< orphan*/  pte_update_batched ; 
 int /*<<< orphan*/  smp_wmb () ; 

void xen_set_pte(pte_t *ptep, pte_t pte)
{
	ADD_STATS(pte_update, 1);
//	ADD_STATS(pte_update_pinned, xen_page_pinned(ptep));
	ADD_STATS(pte_update_batched, paravirt_get_lazy_mode() == PARAVIRT_LAZY_MMU);

#ifdef CONFIG_X86_PAE
	ptep->pte_high = pte.pte_high;
	smp_wmb();
	ptep->pte_low = pte.pte_low;
#else
	*ptep = pte;
#endif
}