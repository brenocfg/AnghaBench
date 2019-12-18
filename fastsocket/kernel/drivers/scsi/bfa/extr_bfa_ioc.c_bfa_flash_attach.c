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
struct bfa_flash_s {scalar_t__ dbuf_pa; int /*<<< orphan*/ * dbuf_kva; struct bfa_ioc_s* ioc; TYPE_1__ ioc_notify; scalar_t__ op_busy; int /*<<< orphan*/ * cbarg; int /*<<< orphan*/ * cbfn; struct bfa_trc_mod_s* trcmod; } ;
typedef  scalar_t__ bfa_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  BFI_MC_FLASH ; 
 int /*<<< orphan*/  bfa_flash_intr ; 
 int /*<<< orphan*/  bfa_flash_notify ; 
 int /*<<< orphan*/  bfa_ioc_mbox_regisr (struct bfa_ioc_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bfa_flash_s*) ; 
 int /*<<< orphan*/  bfa_ioc_notify_init (TYPE_1__*,int /*<<< orphan*/ ,struct bfa_flash_s*) ; 
 int /*<<< orphan*/  bfa_q_qe_init (TYPE_1__*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
bfa_flash_attach(struct bfa_flash_s *flash, struct bfa_ioc_s *ioc, void *dev,
		struct bfa_trc_mod_s *trcmod, bfa_boolean_t mincfg)
{
	flash->ioc = ioc;
	flash->trcmod = trcmod;
	flash->cbfn = NULL;
	flash->cbarg = NULL;
	flash->op_busy = 0;

	bfa_ioc_mbox_regisr(flash->ioc, BFI_MC_FLASH, bfa_flash_intr, flash);
	bfa_q_qe_init(&flash->ioc_notify);
	bfa_ioc_notify_init(&flash->ioc_notify, bfa_flash_notify, flash);
	list_add_tail(&flash->ioc_notify.qe, &flash->ioc->notify_q);

	/* min driver doesn't need flash */
	if (mincfg) {
		flash->dbuf_kva = NULL;
		flash->dbuf_pa = 0;
	}
}