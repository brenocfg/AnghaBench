#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ nvecs; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* hw_reginit ) (struct bfa_s*) ;int /*<<< orphan*/  hw_rspq_ack; int /*<<< orphan*/ * hw_isr_mode_set; scalar_t__ cpe_vec_q0; scalar_t__ rme_vec_q0; int /*<<< orphan*/  hw_msix_get_rme_range; int /*<<< orphan*/  hw_msix_getvecs; int /*<<< orphan*/  hw_msix_uninstall; int /*<<< orphan*/  hw_msix_queue_install; int /*<<< orphan*/  hw_msix_ctrl_install; int /*<<< orphan*/  hw_msix_init; int /*<<< orphan*/ * hw_reqq_ack; } ;
struct bfa_iocfc_cfg_s {int dummy; } ;
struct bfa_iocfc_s {TYPE_1__ hwif; struct bfa_iocfc_cfg_s cfg; struct bfa_s* bfa; } ;
struct bfa_s {TYPE_2__ msix; int /*<<< orphan*/  ioc; void* bfad; struct bfa_iocfc_s iocfc; } ;
struct bfa_pcidev_s {int dummy; } ;

/* Variables and functions */
 int BFI_IOC_MAX_CQS ; 
 scalar_t__ BFI_MSIX_CPE_QMIN_CB ; 
 scalar_t__ BFI_MSIX_CPE_QMIN_CT ; 
 scalar_t__ BFI_MSIX_RME_QMIN_CB ; 
 scalar_t__ BFI_MSIX_RME_QMIN_CT ; 
 scalar_t__ bfa_asic_id_ct2 (int /*<<< orphan*/ ) ; 
 scalar_t__ bfa_asic_id_ctc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bfa_hwcb_isr_mode_set ; 
 int /*<<< orphan*/  bfa_hwcb_msix_ctrl_install ; 
 int /*<<< orphan*/  bfa_hwcb_msix_get_rme_range ; 
 int /*<<< orphan*/  bfa_hwcb_msix_getvecs ; 
 int /*<<< orphan*/  bfa_hwcb_msix_init ; 
 int /*<<< orphan*/  bfa_hwcb_msix_queue_install ; 
 int /*<<< orphan*/  bfa_hwcb_msix_uninstall ; 
 int /*<<< orphan*/  bfa_hwcb_reginit (struct bfa_s*) ; 
 int /*<<< orphan*/  bfa_hwcb_rspq_ack ; 
 int /*<<< orphan*/  bfa_hwct2_reginit (struct bfa_s*) ; 
 int /*<<< orphan*/  bfa_hwct2_rspq_ack ; 
 int /*<<< orphan*/ * bfa_hwct_isr_mode_set ; 
 int /*<<< orphan*/  bfa_hwct_msix_ctrl_install ; 
 int /*<<< orphan*/  bfa_hwct_msix_get_rme_range ; 
 int /*<<< orphan*/  bfa_hwct_msix_getvecs ; 
 int /*<<< orphan*/  bfa_hwct_msix_init ; 
 int /*<<< orphan*/  bfa_hwct_msix_queue_install ; 
 int /*<<< orphan*/  bfa_hwct_msix_uninstall ; 
 int /*<<< orphan*/  bfa_hwct_reginit (struct bfa_s*) ; 
 int /*<<< orphan*/ * bfa_hwct_reqq_ack ; 
 int /*<<< orphan*/  bfa_hwct_rspq_ack ; 
 int /*<<< orphan*/  bfa_ioc_devid (int /*<<< orphan*/ *) ; 
 int bfa_ioc_pcifn (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct bfa_s*) ; 

__attribute__((used)) static void
bfa_iocfc_init_mem(struct bfa_s *bfa, void *bfad, struct bfa_iocfc_cfg_s *cfg,
		   struct bfa_pcidev_s *pcidev)
{
	struct bfa_iocfc_s	*iocfc = &bfa->iocfc;

	bfa->bfad = bfad;
	iocfc->bfa = bfa;
	iocfc->cfg = *cfg;

	/*
	 * Initialize chip specific handlers.
	 */
	if (bfa_asic_id_ctc(bfa_ioc_devid(&bfa->ioc))) {
		iocfc->hwif.hw_reginit = bfa_hwct_reginit;
		iocfc->hwif.hw_reqq_ack = bfa_hwct_reqq_ack;
		iocfc->hwif.hw_rspq_ack = bfa_hwct_rspq_ack;
		iocfc->hwif.hw_msix_init = bfa_hwct_msix_init;
		iocfc->hwif.hw_msix_ctrl_install = bfa_hwct_msix_ctrl_install;
		iocfc->hwif.hw_msix_queue_install = bfa_hwct_msix_queue_install;
		iocfc->hwif.hw_msix_uninstall = bfa_hwct_msix_uninstall;
		iocfc->hwif.hw_isr_mode_set = bfa_hwct_isr_mode_set;
		iocfc->hwif.hw_msix_getvecs = bfa_hwct_msix_getvecs;
		iocfc->hwif.hw_msix_get_rme_range = bfa_hwct_msix_get_rme_range;
		iocfc->hwif.rme_vec_q0 = BFI_MSIX_RME_QMIN_CT;
		iocfc->hwif.cpe_vec_q0 = BFI_MSIX_CPE_QMIN_CT;
	} else {
		iocfc->hwif.hw_reginit = bfa_hwcb_reginit;
		iocfc->hwif.hw_reqq_ack = NULL;
		iocfc->hwif.hw_rspq_ack = bfa_hwcb_rspq_ack;
		iocfc->hwif.hw_msix_init = bfa_hwcb_msix_init;
		iocfc->hwif.hw_msix_ctrl_install = bfa_hwcb_msix_ctrl_install;
		iocfc->hwif.hw_msix_queue_install = bfa_hwcb_msix_queue_install;
		iocfc->hwif.hw_msix_uninstall = bfa_hwcb_msix_uninstall;
		iocfc->hwif.hw_isr_mode_set = bfa_hwcb_isr_mode_set;
		iocfc->hwif.hw_msix_getvecs = bfa_hwcb_msix_getvecs;
		iocfc->hwif.hw_msix_get_rme_range = bfa_hwcb_msix_get_rme_range;
		iocfc->hwif.rme_vec_q0 = BFI_MSIX_RME_QMIN_CB +
			bfa_ioc_pcifn(&bfa->ioc) * BFI_IOC_MAX_CQS;
		iocfc->hwif.cpe_vec_q0 = BFI_MSIX_CPE_QMIN_CB +
			bfa_ioc_pcifn(&bfa->ioc) * BFI_IOC_MAX_CQS;
	}

	if (bfa_asic_id_ct2(bfa_ioc_devid(&bfa->ioc))) {
		iocfc->hwif.hw_reginit = bfa_hwct2_reginit;
		iocfc->hwif.hw_isr_mode_set = NULL;
		iocfc->hwif.hw_rspq_ack = bfa_hwct2_rspq_ack;
	}

	iocfc->hwif.hw_reginit(bfa);
	bfa->msix.nvecs = 0;
}