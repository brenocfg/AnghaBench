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
struct TYPE_3__ {int /*<<< orphan*/  delay; int /*<<< orphan*/  status; } ;
struct qlcnic_hardware_context {int msix_supported; scalar_t__ reset_context; TYPE_1__ idc; int /*<<< orphan*/  mbx_lock; } ;
struct qlcnic_adapter {int /*<<< orphan*/  state; int /*<<< orphan*/  idc_aen_work; TYPE_2__* pdev; int /*<<< orphan*/  flags; scalar_t__ need_fw_reset; scalar_t__ fw_fail_cnt; struct qlcnic_hardware_context* ahw; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QLCNIC_TX_INTR_SHARED ; 
 int /*<<< orphan*/  QLC_83XX_IDC_FW_POLL_DELAY ; 
 int /*<<< orphan*/  QLC_83XX_MBX_READY ; 
 int /*<<< orphan*/  QLC_83XX_MODULE_LOADED ; 
 int /*<<< orphan*/  __QLCNIC_RESETTING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  qlcnic_83xx_idc_aen_work ; 
 scalar_t__ qlcnic_read_mac_addr (struct qlcnic_adapter*) ; 
 int qlcnic_sriov_check_dev_ready (struct qlcnic_adapter*) ; 
 int qlcnic_sriov_setup_vf (struct qlcnic_adapter*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int qlcnic_sriov_vf_init(struct qlcnic_adapter *adapter, int pci_using_dac)
{
	struct qlcnic_hardware_context *ahw = adapter->ahw;
	int err;

	spin_lock_init(&ahw->mbx_lock);
	set_bit(QLC_83XX_MBX_READY, &ahw->idc.status);
	set_bit(QLC_83XX_MODULE_LOADED, &ahw->idc.status);
	ahw->idc.delay = QLC_83XX_IDC_FW_POLL_DELAY;
	ahw->reset_context = 0;
	adapter->fw_fail_cnt = 0;
	ahw->msix_supported = 1;
	adapter->need_fw_reset = 0;
	adapter->flags |= QLCNIC_TX_INTR_SHARED;

	err = qlcnic_sriov_check_dev_ready(adapter);
	if (err)
		return err;

	err = qlcnic_sriov_setup_vf(adapter, pci_using_dac);
	if (err)
		return err;

	if (qlcnic_read_mac_addr(adapter))
		dev_warn(&adapter->pdev->dev, "failed to read mac addr\n");

	INIT_DELAYED_WORK(&adapter->idc_aen_work, qlcnic_83xx_idc_aen_work);

	clear_bit(__QLCNIC_RESETTING, &adapter->state);
	return 0;
}