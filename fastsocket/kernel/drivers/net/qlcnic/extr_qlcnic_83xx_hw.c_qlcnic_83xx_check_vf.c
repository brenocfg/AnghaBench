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
typedef  scalar_t__ u32 ;
struct qlcnic_hardware_context {int fw_hal_version; scalar_t__ op_mode; int /*<<< orphan*/  pci_func; } ;
struct qlcnic_adapter {int /*<<< orphan*/ * nic_ops; int /*<<< orphan*/  state; TYPE_1__* pdev; struct qlcnic_hardware_context* ahw; } ;
struct pci_device_id {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_EXT_CAP_ID_SRIOV ; 
 scalar_t__ QLCNIC_MGMT_FUNC ; 
 scalar_t__ QLCNIC_NON_PRIV_FUNC ; 
 scalar_t__ QLCRDX (struct qlcnic_hardware_context*,int /*<<< orphan*/ ) ; 
 scalar_t__ QLC_83XX_DEFAULT_OPMODE ; 
 int /*<<< orphan*/  QLC_83XX_DRV_OP_MODE ; 
 scalar_t__ QLC_83XX_GET_FUNC_PRIVILEGE (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __QLCNIC_SRIOV_CAPABLE ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ pci_find_ext_capability (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_83xx_ops ; 
 int /*<<< orphan*/  qlcnic_get_func_no (struct qlcnic_adapter*) ; 
 scalar_t__ qlcnic_sriov_vf_check (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_sriov_vf_set_ops (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_vf_ops ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void qlcnic_83xx_check_vf(struct qlcnic_adapter *adapter,
			  const struct pci_device_id *ent)
{
	u32 op_mode, priv_level;
	struct qlcnic_hardware_context *ahw = adapter->ahw;

	ahw->fw_hal_version = 2;
	qlcnic_get_func_no(adapter);

	if (qlcnic_sriov_vf_check(adapter)) {
		qlcnic_sriov_vf_set_ops(adapter);
		return;
	}

	/* Determine function privilege level */
	op_mode = QLCRDX(adapter->ahw, QLC_83XX_DRV_OP_MODE);
	if (op_mode == QLC_83XX_DEFAULT_OPMODE)
		priv_level = QLCNIC_MGMT_FUNC;
	else
		priv_level = QLC_83XX_GET_FUNC_PRIVILEGE(op_mode,
							 ahw->pci_func);

	if (priv_level == QLCNIC_NON_PRIV_FUNC) {
		ahw->op_mode = QLCNIC_NON_PRIV_FUNC;
		dev_info(&adapter->pdev->dev,
			 "HAL Version: %d Non Privileged function\n",
			 ahw->fw_hal_version);
		adapter->nic_ops = &qlcnic_vf_ops;
	} else {
		if (pci_find_ext_capability(adapter->pdev,
					    PCI_EXT_CAP_ID_SRIOV))
			set_bit(__QLCNIC_SRIOV_CAPABLE, &adapter->state);
		adapter->nic_ops = &qlcnic_83xx_ops;
	}
}