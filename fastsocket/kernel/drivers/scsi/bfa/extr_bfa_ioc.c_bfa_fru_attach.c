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
struct bfa_trc_mod_s {int dummy; } ;
struct bfa_ioc_s {int /*<<< orphan*/  notify_q; } ;
struct TYPE_3__ {int /*<<< orphan*/  qe; } ;
struct bfa_fru_s {scalar_t__ dbuf_pa; int /*<<< orphan*/ * dbuf_kva; struct bfa_ioc_s* ioc; TYPE_1__ ioc_notify; scalar_t__ op_busy; int /*<<< orphan*/ * cbarg; int /*<<< orphan*/ * cbfn; struct bfa_trc_mod_s* trcmod; } ;
typedef  scalar_t__ bfa_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  BFI_MC_FRU ; 
 int /*<<< orphan*/  bfa_fru_intr ; 
 int /*<<< orphan*/  bfa_fru_notify ; 
 int /*<<< orphan*/  bfa_ioc_mbox_regisr (struct bfa_ioc_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bfa_fru_s*) ; 
 int /*<<< orphan*/  bfa_ioc_notify_init (TYPE_1__*,int /*<<< orphan*/ ,struct bfa_fru_s*) ; 
 int /*<<< orphan*/  bfa_q_qe_init (TYPE_1__*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
bfa_fru_attach(struct bfa_fru_s *fru, struct bfa_ioc_s *ioc, void *dev,
	struct bfa_trc_mod_s *trcmod, bfa_boolean_t mincfg)
{
	fru->ioc = ioc;
	fru->trcmod = trcmod;
	fru->cbfn = NULL;
	fru->cbarg = NULL;
	fru->op_busy = 0;

	bfa_ioc_mbox_regisr(fru->ioc, BFI_MC_FRU, bfa_fru_intr, fru);
	bfa_q_qe_init(&fru->ioc_notify);
	bfa_ioc_notify_init(&fru->ioc_notify, bfa_fru_notify, fru);
	list_add_tail(&fru->ioc_notify.qe, &fru->ioc->notify_q);

	/* min driver doesn't need fru */
	if (mincfg) {
		fru->dbuf_kva = NULL;
		fru->dbuf_pa = 0;
	}
}