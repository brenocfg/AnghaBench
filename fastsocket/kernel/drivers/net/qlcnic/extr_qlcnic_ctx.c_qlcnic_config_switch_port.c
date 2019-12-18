#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct qlcnic_esw_func_cfg {int pci_func; int op_mode; int offload_flags; int vlan_id; int /*<<< orphan*/  mac_anti_spoof; int /*<<< orphan*/  mac_override; int /*<<< orphan*/  promisc_mode; int /*<<< orphan*/  discard_tagged; } ;
struct TYPE_8__ {int* arg; } ;
struct qlcnic_cmd_args {TYPE_4__ req; } ;
struct qlcnic_adapter {TYPE_3__* ahw; TYPE_2__* npars; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_7__ {scalar_t__ op_mode; int capabilities; } ;
struct TYPE_6__ {int phy_port; } ;
struct TYPE_5__ {struct device dev; } ;

/* Variables and functions */
 int BIT_0 ; 
 int BIT_1 ; 
 int BIT_2 ; 
 int BIT_3 ; 
 int BIT_4 ; 
 int BIT_5 ; 
 int BIT_6 ; 
 int BIT_7 ; 
 int EIO ; 
#define  QLCNIC_ADD_VLAN 130 
 int /*<<< orphan*/  QLCNIC_CMD_CONFIGURE_ESWITCH ; 
#define  QLCNIC_DEL_VLAN 129 
 int QLCNIC_FW_CAPABILITY_TSO ; 
 scalar_t__ QLCNIC_MGMT_FUNC ; 
#define  QLCNIC_PORT_DEFAULTS 128 
 int QLCNIC_RCODE_SUCCESS ; 
 scalar_t__ __qlcnic_get_eswitch_port_config (struct qlcnic_adapter*,int*,int*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int) ; 
 int /*<<< orphan*/  qlcnic_alloc_mbx_args (struct qlcnic_cmd_args*,struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_free_mbx_args (struct qlcnic_cmd_args*) ; 
 int qlcnic_is_valid_nic_func (struct qlcnic_adapter*,int) ; 
 int qlcnic_issue_cmd (struct qlcnic_adapter*,struct qlcnic_cmd_args*) ; 

int qlcnic_config_switch_port(struct qlcnic_adapter *adapter,
		struct qlcnic_esw_func_cfg *esw_cfg)
{
	struct device *dev = &adapter->pdev->dev;
	struct qlcnic_cmd_args cmd;
	int err = -EIO, index;
	u32 arg1, arg2 = 0;
	u8 pci_func;

	if (adapter->ahw->op_mode != QLCNIC_MGMT_FUNC)
		return err;
	pci_func = esw_cfg->pci_func;
	index = qlcnic_is_valid_nic_func(adapter, pci_func);
	if (index < 0)
		return err;
	arg1 = (adapter->npars[index].phy_port & BIT_0);
	arg1 |= (pci_func << 8);

	if (__qlcnic_get_eswitch_port_config(adapter, &arg1, &arg2))
		return err;
	arg1 &= ~(0x0ff << 8);
	arg1 |= (pci_func << 8);
	arg1 &= ~(BIT_2 | BIT_3);
	switch (esw_cfg->op_mode) {
	case QLCNIC_PORT_DEFAULTS:
		arg1 |= (BIT_4 | BIT_6 | BIT_7);
		arg2 |= (BIT_0 | BIT_1);
		if (adapter->ahw->capabilities & QLCNIC_FW_CAPABILITY_TSO)
			arg2 |= (BIT_2 | BIT_3);
		if (!(esw_cfg->discard_tagged))
			arg1 &= ~BIT_4;
		if (!(esw_cfg->promisc_mode))
			arg1 &= ~BIT_6;
		if (!(esw_cfg->mac_override))
			arg1 &= ~BIT_7;
		if (!(esw_cfg->mac_anti_spoof))
			arg2 &= ~BIT_0;
		if (!(esw_cfg->offload_flags & BIT_0))
			arg2 &= ~(BIT_1 | BIT_2 | BIT_3);
		if (!(esw_cfg->offload_flags & BIT_1))
			arg2 &= ~BIT_2;
		if (!(esw_cfg->offload_flags & BIT_2))
			arg2 &= ~BIT_3;
		break;
	case QLCNIC_ADD_VLAN:
			arg1 |= (BIT_2 | BIT_5);
			arg1 |= (esw_cfg->vlan_id << 16);
			break;
	case QLCNIC_DEL_VLAN:
			arg1 |= (BIT_3 | BIT_5);
			arg1 &= ~(0x0ffff << 16);
			break;
	default:
		return err;
	}

	qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_CONFIGURE_ESWITCH);
	cmd.req.arg[1] = arg1;
	cmd.req.arg[2] = arg2;
	err = qlcnic_issue_cmd(adapter, &cmd);
	qlcnic_free_mbx_args(&cmd);

	if (err != QLCNIC_RCODE_SUCCESS)
		dev_err(dev, "Failed to configure eswitch for vNIC function %d\n",
			pci_func);
	else
		dev_info(dev, "Configured eSwitch for vNIC function %d\n",
			 pci_func);

	return err;
}