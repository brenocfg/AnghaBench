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
typedef  int u32 ;
struct qib_devdata {TYPE_1__* cspec; int /*<<< orphan*/  revision; int /*<<< orphan*/  f_tempsense_rd; int /*<<< orphan*/  f_writescratch; int /*<<< orphan*/  f_xgxs_reset; int /*<<< orphan*/  f_wantpiobuf_intr; int /*<<< orphan*/  f_update_usrhead; int /*<<< orphan*/  f_txchk_change; int /*<<< orphan*/  f_setextled; int /*<<< orphan*/  f_set_intr_state; int /*<<< orphan*/  f_set_ib_loopback; int /*<<< orphan*/  f_set_ib_cfg; int /*<<< orphan*/  f_get_ib_cfg; int /*<<< orphan*/  f_ibphys_portstate; int /*<<< orphan*/  f_iblink_state; int /*<<< orphan*/  f_set_cntr_sample; int /*<<< orphan*/  f_set_armlaunch; int /*<<< orphan*/  f_sendctrl; int /*<<< orphan*/  f_sdma_init_early; int /*<<< orphan*/  f_sdma_hw_start_up; int /*<<< orphan*/  f_sdma_hw_clean_up; int /*<<< orphan*/  f_sdma_update_tail; int /*<<< orphan*/  f_sdma_set_desc_cnt; int /*<<< orphan*/  f_sdma_sendctrl; int /*<<< orphan*/  f_sdma_gethead; int /*<<< orphan*/  f_sdma_busy; int /*<<< orphan*/  f_init_sdma_regs; int /*<<< orphan*/  f_reset; int /*<<< orphan*/  f_read_portcntrs; int /*<<< orphan*/  f_read_cntrs; int /*<<< orphan*/  f_rcvctrl; int /*<<< orphan*/  f_quiet_serdes; int /*<<< orphan*/  f_put_tid; int /*<<< orphan*/  f_portcntr; int /*<<< orphan*/  f_setpbc_control; int /*<<< orphan*/  f_late_initreg; int /*<<< orphan*/  f_intr_fallback; int /*<<< orphan*/  f_initvl15_bufs; int /*<<< orphan*/  f_init_ctxt; int /*<<< orphan*/  f_ib_updown; int /*<<< orphan*/  f_hdrqempty; int /*<<< orphan*/  f_eeprom_wen; int /*<<< orphan*/  f_gpio_mod; int /*<<< orphan*/  f_getsendbuf; int /*<<< orphan*/  f_get_msgheader; int /*<<< orphan*/  f_get_base_info; int /*<<< orphan*/  f_free_irq; int /*<<< orphan*/  f_clear_tids; int /*<<< orphan*/  f_cleanup; int /*<<< orphan*/  f_bringup_serdes; } ;
struct qib_chippport_specific {int dummy; } ;
struct qib_chip_specific {int dummy; } ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  irq; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BoardID ; 
 struct qib_devdata* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct qib_devdata*) ; 
 int QLOGIC_IB_HWE_SERDESPLLFAILED ; 
 int /*<<< orphan*/  Revision ; 
 int SYM_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_7220_mod ; 
 int /*<<< orphan*/  init_sdma_7220_regs ; 
 int /*<<< orphan*/  kr_hwdiagctrl ; 
 int /*<<< orphan*/  kr_hwerrclear ; 
 int /*<<< orphan*/  kr_hwerrstatus ; 
 int /*<<< orphan*/  qib_7220_bringup_serdes ; 
 int /*<<< orphan*/  qib_7220_clear_tids ; 
 int /*<<< orphan*/  qib_7220_eeprom_wen ; 
 int /*<<< orphan*/  qib_7220_free_irq ; 
 int /*<<< orphan*/  qib_7220_get_base_info ; 
 int /*<<< orphan*/  qib_7220_get_ib_cfg ; 
 int /*<<< orphan*/  qib_7220_get_msgheader ; 
 int /*<<< orphan*/  qib_7220_getsendbuf ; 
 int /*<<< orphan*/  qib_7220_hdrqempty ; 
 int /*<<< orphan*/  qib_7220_ib_updown ; 
 int /*<<< orphan*/  qib_7220_iblink_state ; 
 int /*<<< orphan*/  qib_7220_init_ctxt ; 
 int /*<<< orphan*/  qib_7220_init_hwerrors (struct qib_devdata*) ; 
 int /*<<< orphan*/  qib_7220_initvl15_bufs ; 
 int /*<<< orphan*/  qib_7220_intr_fallback ; 
 int /*<<< orphan*/  qib_7220_phys_portstate ; 
 int /*<<< orphan*/  qib_7220_put_tid ; 
 int /*<<< orphan*/  qib_7220_quiet_serdes ; 
 int /*<<< orphan*/  qib_7220_sdma_hw_clean_up ; 
 int /*<<< orphan*/  qib_7220_sdma_hw_start_up ; 
 int /*<<< orphan*/  qib_7220_sdma_init_early ; 
 int /*<<< orphan*/  qib_7220_sdma_sendctrl ; 
 int /*<<< orphan*/  qib_7220_set_ib_cfg ; 
 int /*<<< orphan*/  qib_7220_set_intr_state ; 
 int /*<<< orphan*/  qib_7220_set_loopback ; 
 int /*<<< orphan*/  qib_7220_setpbc_control ; 
 int /*<<< orphan*/  qib_7220_tempsense_rd ; 
 int /*<<< orphan*/  qib_7220_txchk_change ; 
 int /*<<< orphan*/  qib_7220_xgxs_reset ; 
 struct qib_devdata* qib_alloc_devdata (struct pci_dev*,int) ; 
 int /*<<< orphan*/  qib_dev_err (struct qib_devdata*,char*) ; 
 int /*<<< orphan*/  qib_free_devdata (struct qib_devdata*) ; 
 int qib_init_7220_variables (struct qib_devdata*) ; 
 int /*<<< orphan*/  qib_late_7220_initreg ; 
 scalar_t__ qib_mini_init ; 
 int /*<<< orphan*/  qib_pcie_ddcleanup (struct qib_devdata*) ; 
 int qib_pcie_ddinit (struct qib_devdata*,struct pci_dev*,struct pci_device_id const*) ; 
 scalar_t__ qib_pcie_params (struct qib_devdata*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qib_portcntr_7220 ; 
 int /*<<< orphan*/  qib_read_7220cntrs ; 
 int /*<<< orphan*/  qib_read_7220portcntrs ; 
 int qib_read_kreg64 (struct qib_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_sdma_7220_busy ; 
 int /*<<< orphan*/  qib_sdma_7220_gethead ; 
 int /*<<< orphan*/  qib_sdma_set_7220_desc_cnt ; 
 int /*<<< orphan*/  qib_sdma_update_7220_tail ; 
 int /*<<< orphan*/  qib_set_7220_armlaunch ; 
 int /*<<< orphan*/  qib_set_cntr_7220_sample ; 
 int /*<<< orphan*/  qib_setup_7220_cleanup ; 
 int /*<<< orphan*/  qib_setup_7220_interrupt (struct qib_devdata*) ; 
 int /*<<< orphan*/  qib_setup_7220_reset ; 
 int /*<<< orphan*/  qib_setup_7220_setextled ; 
 int /*<<< orphan*/  qib_update_7220_usrhead ; 
 int /*<<< orphan*/  qib_wantpiobuf_7220_intr ; 
 int /*<<< orphan*/  qib_write_kreg (struct qib_devdata*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rcvctrl_7220_mod ; 
 int /*<<< orphan*/  sendctrl_7220_mod ; 
 int /*<<< orphan*/  writescratch ; 

struct qib_devdata *qib_init_iba7220_funcs(struct pci_dev *pdev,
					   const struct pci_device_id *ent)
{
	struct qib_devdata *dd;
	int ret;
	u32 boardid, minwidth;

	dd = qib_alloc_devdata(pdev, sizeof(struct qib_chip_specific) +
		sizeof(struct qib_chippport_specific));
	if (IS_ERR(dd))
		goto bail;

	dd->f_bringup_serdes    = qib_7220_bringup_serdes;
	dd->f_cleanup           = qib_setup_7220_cleanup;
	dd->f_clear_tids        = qib_7220_clear_tids;
	dd->f_free_irq          = qib_7220_free_irq;
	dd->f_get_base_info     = qib_7220_get_base_info;
	dd->f_get_msgheader     = qib_7220_get_msgheader;
	dd->f_getsendbuf        = qib_7220_getsendbuf;
	dd->f_gpio_mod          = gpio_7220_mod;
	dd->f_eeprom_wen        = qib_7220_eeprom_wen;
	dd->f_hdrqempty         = qib_7220_hdrqempty;
	dd->f_ib_updown         = qib_7220_ib_updown;
	dd->f_init_ctxt         = qib_7220_init_ctxt;
	dd->f_initvl15_bufs     = qib_7220_initvl15_bufs;
	dd->f_intr_fallback     = qib_7220_intr_fallback;
	dd->f_late_initreg      = qib_late_7220_initreg;
	dd->f_setpbc_control    = qib_7220_setpbc_control;
	dd->f_portcntr          = qib_portcntr_7220;
	dd->f_put_tid           = qib_7220_put_tid;
	dd->f_quiet_serdes      = qib_7220_quiet_serdes;
	dd->f_rcvctrl           = rcvctrl_7220_mod;
	dd->f_read_cntrs        = qib_read_7220cntrs;
	dd->f_read_portcntrs    = qib_read_7220portcntrs;
	dd->f_reset             = qib_setup_7220_reset;
	dd->f_init_sdma_regs    = init_sdma_7220_regs;
	dd->f_sdma_busy         = qib_sdma_7220_busy;
	dd->f_sdma_gethead      = qib_sdma_7220_gethead;
	dd->f_sdma_sendctrl     = qib_7220_sdma_sendctrl;
	dd->f_sdma_set_desc_cnt = qib_sdma_set_7220_desc_cnt;
	dd->f_sdma_update_tail  = qib_sdma_update_7220_tail;
	dd->f_sdma_hw_clean_up  = qib_7220_sdma_hw_clean_up;
	dd->f_sdma_hw_start_up  = qib_7220_sdma_hw_start_up;
	dd->f_sdma_init_early   = qib_7220_sdma_init_early;
	dd->f_sendctrl          = sendctrl_7220_mod;
	dd->f_set_armlaunch     = qib_set_7220_armlaunch;
	dd->f_set_cntr_sample   = qib_set_cntr_7220_sample;
	dd->f_iblink_state      = qib_7220_iblink_state;
	dd->f_ibphys_portstate  = qib_7220_phys_portstate;
	dd->f_get_ib_cfg        = qib_7220_get_ib_cfg;
	dd->f_set_ib_cfg        = qib_7220_set_ib_cfg;
	dd->f_set_ib_loopback   = qib_7220_set_loopback;
	dd->f_set_intr_state    = qib_7220_set_intr_state;
	dd->f_setextled         = qib_setup_7220_setextled;
	dd->f_txchk_change      = qib_7220_txchk_change;
	dd->f_update_usrhead    = qib_update_7220_usrhead;
	dd->f_wantpiobuf_intr   = qib_wantpiobuf_7220_intr;
	dd->f_xgxs_reset        = qib_7220_xgxs_reset;
	dd->f_writescratch      = writescratch;
	dd->f_tempsense_rd	= qib_7220_tempsense_rd;
	/*
	 * Do remaining pcie setup and save pcie values in dd.
	 * Any error printing is already done by the init code.
	 * On return, we have the chip mapped, but chip registers
	 * are not set up until start of qib_init_7220_variables.
	 */
	ret = qib_pcie_ddinit(dd, pdev, ent);
	if (ret < 0)
		goto bail_free;

	/* initialize chip-specific variables */
	ret = qib_init_7220_variables(dd);
	if (ret)
		goto bail_cleanup;

	if (qib_mini_init)
		goto bail;

	boardid = SYM_FIELD(dd->revision, Revision,
			    BoardID);
	switch (boardid) {
	case 0:
	case 2:
	case 10:
	case 12:
		minwidth = 16; /* x16 capable boards */
		break;
	default:
		minwidth = 8; /* x8 capable boards */
		break;
	}
	if (qib_pcie_params(dd, minwidth, NULL, NULL))
		qib_dev_err(dd,
			"Failed to setup PCIe or interrupts; continuing anyway\n");

	/* save IRQ for possible later use */
	dd->cspec->irq = pdev->irq;

	if (qib_read_kreg64(dd, kr_hwerrstatus) &
	    QLOGIC_IB_HWE_SERDESPLLFAILED)
		qib_write_kreg(dd, kr_hwerrclear,
			       QLOGIC_IB_HWE_SERDESPLLFAILED);

	/* setup interrupt handler (interrupt type handled above) */
	qib_setup_7220_interrupt(dd);
	qib_7220_init_hwerrors(dd);

	/* clear diagctrl register, in case diags were running and crashed */
	qib_write_kreg(dd, kr_hwdiagctrl, 0);

	goto bail;

bail_cleanup:
	qib_pcie_ddcleanup(dd);
bail_free:
	qib_free_devdata(dd);
	dd = ERR_PTR(ret);
bail:
	return dd;
}