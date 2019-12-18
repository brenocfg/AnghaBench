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
typedef  scalar_t__ u32 ;
struct qlcnic_adapter {int /*<<< orphan*/ * nic_ops; TYPE_2__* ahw; TYPE_1__* pdev; } ;
struct pci_device_id {int dummy; } ;
struct TYPE_4__ {void* fw_hal_version; scalar_t__ op_mode; int /*<<< orphan*/  pci_func; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_DRV_OP_MODE ; 
 int /*<<< orphan*/  QLCNIC_FW_API ; 
 scalar_t__ QLCNIC_MGMT_FUNC ; 
 scalar_t__ QLCNIC_NON_PRIV_FUNC ; 
 scalar_t__ QLC_DEV_DRV_DEFAULT ; 
 scalar_t__ QLC_DEV_GET_DRV (scalar_t__,int /*<<< orphan*/ ) ; 
 void* QLC_SHARED_REG_RD32 (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,void*) ; 
 int /*<<< orphan*/  qlcnic_get_func_no (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_ops ; 
 int /*<<< orphan*/  qlcnic_vf_ops ; 

__attribute__((used)) static void qlcnic_check_vf(struct qlcnic_adapter *adapter,
			    const struct pci_device_id *ent)
{
	u32 op_mode, priv_level;

	/* Determine FW API version */
	adapter->ahw->fw_hal_version = QLC_SHARED_REG_RD32(adapter,
							   QLCNIC_FW_API);

	/* Find PCI function number */
	qlcnic_get_func_no(adapter);

	/* Determine function privilege level */
	op_mode = QLC_SHARED_REG_RD32(adapter, QLCNIC_DRV_OP_MODE);
	if (op_mode == QLC_DEV_DRV_DEFAULT)
		priv_level = QLCNIC_MGMT_FUNC;
	else
		priv_level = QLC_DEV_GET_DRV(op_mode, adapter->ahw->pci_func);

	if (priv_level == QLCNIC_NON_PRIV_FUNC) {
		adapter->ahw->op_mode = QLCNIC_NON_PRIV_FUNC;
		dev_info(&adapter->pdev->dev,
			"HAL Version: %d Non Privileged function\n",
			 adapter->ahw->fw_hal_version);
		adapter->nic_ops = &qlcnic_vf_ops;
	} else
		adapter->nic_ops = &qlcnic_ops;
}