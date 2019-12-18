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
struct qlcnic_nic_template {int /*<<< orphan*/  init_driver; } ;
struct TYPE_4__ {int /*<<< orphan*/  vnic_wait_limit; int /*<<< orphan*/  vnic_state; void* state_entry; } ;
struct qlcnic_hardware_context {int op_mode; int capabilities; TYPE_2__ idc; int /*<<< orphan*/  pci_func; } ;
struct qlcnic_adapter {int /*<<< orphan*/  flags; TYPE_1__* pdev; struct qlcnic_hardware_context* ahw; struct qlcnic_nic_template* nic_ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BIT_23 ; 
 int EIO ; 
 int /*<<< orphan*/  QLCNIC_DEV_NPAR_NON_OPER ; 
 int /*<<< orphan*/  QLCNIC_DEV_NPAR_OPER_TIMEO ; 
 int /*<<< orphan*/  QLCNIC_ESWITCH_ENABLED ; 
#define  QLCNIC_MGMT_FUNC 130 
#define  QLCNIC_NON_PRIV_FUNC 129 
#define  QLCNIC_PRIV_FUNC 128 
 scalar_t__ QLCRDX (struct qlcnic_hardware_context*,int /*<<< orphan*/ ) ; 
 scalar_t__ QLC_83XX_DEFAULT_OPMODE ; 
 int /*<<< orphan*/  QLC_83XX_DRV_OP_MODE ; 
 scalar_t__ QLC_83XX_GET_FUNC_PRIVILEGE (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 void* qlcnic_83xx_idc_ready_state_entry ; 
 void* qlcnic_83xx_idc_vnic_pf_entry ; 
 int /*<<< orphan*/  qlcnic_83xx_init_mgmt_vnic ; 
 int /*<<< orphan*/  qlcnic_83xx_init_non_privileged_vnic ; 
 int /*<<< orphan*/  qlcnic_83xx_init_privileged_vnic ; 
 int /*<<< orphan*/  qlcnic_get_func_no (struct qlcnic_adapter*) ; 

int qlcnic_83xx_config_vnic_opmode(struct qlcnic_adapter *adapter)
{
	u32 op_mode, priv_level;
	struct qlcnic_hardware_context *ahw = adapter->ahw;
	struct qlcnic_nic_template *nic_ops = adapter->nic_ops;

	qlcnic_get_func_no(adapter);
	op_mode = QLCRDX(adapter->ahw, QLC_83XX_DRV_OP_MODE);

	if (op_mode == QLC_83XX_DEFAULT_OPMODE)
		priv_level = QLCNIC_MGMT_FUNC;
	else
		priv_level = QLC_83XX_GET_FUNC_PRIVILEGE(op_mode,
							 ahw->pci_func);
	switch (priv_level) {
	case QLCNIC_NON_PRIV_FUNC:
		ahw->op_mode = QLCNIC_NON_PRIV_FUNC;
		ahw->idc.state_entry = qlcnic_83xx_idc_ready_state_entry;
		nic_ops->init_driver = qlcnic_83xx_init_non_privileged_vnic;
		break;
	case QLCNIC_PRIV_FUNC:
		ahw->op_mode = QLCNIC_PRIV_FUNC;
		ahw->idc.state_entry = qlcnic_83xx_idc_vnic_pf_entry;
		nic_ops->init_driver = qlcnic_83xx_init_privileged_vnic;
		break;
	case QLCNIC_MGMT_FUNC:
		ahw->op_mode = QLCNIC_MGMT_FUNC;
		ahw->idc.state_entry = qlcnic_83xx_idc_ready_state_entry;
		nic_ops->init_driver = qlcnic_83xx_init_mgmt_vnic;
		break;
	default:
		dev_err(&adapter->pdev->dev, "Invalid Virtual NIC opmode\n");
		return -EIO;
	}

	if (ahw->capabilities & BIT_23)
		adapter->flags |= QLCNIC_ESWITCH_ENABLED;
	else
		adapter->flags &= ~QLCNIC_ESWITCH_ENABLED;

	ahw->idc.vnic_state = QLCNIC_DEV_NPAR_NON_OPER;
	ahw->idc.vnic_wait_limit = QLCNIC_DEV_NPAR_OPER_TIMEO;

	return 0;
}