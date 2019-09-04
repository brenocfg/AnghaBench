#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct modctl {struct modctl* mod_next; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* dtps_provide_module ) (int /*<<< orphan*/ ,struct modctl*) ;int /*<<< orphan*/  (* dtps_provide ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  dtpv_arg; TYPE_1__ dtpv_pops; struct TYPE_6__* dtpv_next; } ;
typedef  TYPE_2__ dtrace_provider_t ;
typedef  int /*<<< orphan*/  dtrace_probedesc_t ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 struct modctl* dtrace_modctl_list ; 
 TYPE_2__* dtrace_provider ; 
 int /*<<< orphan*/  dtrace_provider_lock ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_lock ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,struct modctl*) ; 

__attribute__((used)) static void
dtrace_probe_provide(dtrace_probedesc_t *desc, dtrace_provider_t *prv)
{
	struct modctl *ctl;
	int all = 0;

	LCK_MTX_ASSERT(&dtrace_provider_lock, LCK_MTX_ASSERT_OWNED);

	if (prv == NULL) {
		all = 1;
		prv = dtrace_provider;
	}
		 
	do {
		/*
		 * First, call the blanket provide operation.
		 */
		prv->dtpv_pops.dtps_provide(prv->dtpv_arg, desc);
		
		/*
		 * Now call the per-module provide operation.  We will grab
		 * mod_lock to prevent the list from being modified.  Note
		 * that this also prevents the mod_busy bits from changing.
		 * (mod_busy can only be changed with mod_lock held.)
		 */
		lck_mtx_lock(&mod_lock);
		
		ctl = dtrace_modctl_list;
		while (ctl) {
			prv->dtpv_pops.dtps_provide_module(prv->dtpv_arg, ctl);
			ctl = ctl->mod_next;
		}
		
		lck_mtx_unlock(&mod_lock);
	} while (all && (prv = prv->dtpv_next) != NULL);
}