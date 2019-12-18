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
typedef  int u64 ;
struct timer_list {int dummy; } ;
struct nodepda_s {struct bteinfo_s* bte_if; struct timer_list bte_recovery_timer; } ;
struct bteinfo_s {int /*<<< orphan*/  bh_error; int /*<<< orphan*/  bte_cnode; } ;
typedef  int /*<<< orphan*/  nasid_t ;

/* Variables and functions */
 int BTES_PER_NODE ; 
 int BTE_LNSTAT_LOAD (struct bteinfo_s*) ; 
 int /*<<< orphan*/  BTE_PRINTK (char*) ; 
 int /*<<< orphan*/  BTE_SHUB2_ERROR (int) ; 
 int HZ ; 
 int IBLS_BUSY ; 
 int IBLS_ERROR ; 
 int /*<<< orphan*/  cnodeid_to_nasid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer (struct timer_list*) ; 
 scalar_t__ ia64_sn_bte_recovery (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (struct timer_list*,scalar_t__) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

int shub2_bte_error_handler(unsigned long _nodepda)
{
	struct nodepda_s *err_nodepda = (struct nodepda_s *)_nodepda;
	struct timer_list *recovery_timer = &err_nodepda->bte_recovery_timer;
	struct bteinfo_s *bte;
	nasid_t nasid;
	u64 status;
	int i;

	nasid = cnodeid_to_nasid(err_nodepda->bte_if[0].bte_cnode);

	/*
	 * Verify that all the BTEs are complete
	 */
	for (i = 0; i < BTES_PER_NODE; i++) {
		bte = &err_nodepda->bte_if[i];
		status = BTE_LNSTAT_LOAD(bte);
		if (status & IBLS_ERROR) {
			bte->bh_error = BTE_SHUB2_ERROR(status);
			continue;
		}
		if (!(status & IBLS_BUSY))
			continue;
		mod_timer(recovery_timer, jiffies + (HZ * 5));
		BTE_PRINTK(("eh:%p:%d Marked Giving up\n", err_nodepda,
			    smp_processor_id()));
		return 1;
	}
	if (ia64_sn_bte_recovery(nasid))
		panic("bte_error_handler(): Fatal BTE Error");

	del_timer(recovery_timer);
	return 0;
}