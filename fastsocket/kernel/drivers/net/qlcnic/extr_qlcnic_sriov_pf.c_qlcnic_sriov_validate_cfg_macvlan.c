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
typedef  int u8 ;
struct qlcnic_vport {int handle; scalar_t__ vlan_mode; int vlan; } ;
struct qlcnic_vf_info {int /*<<< orphan*/  pci_func; struct qlcnic_vport* vp; } ;
struct qlcnic_macvlan_mbx {int mac_addr0; } ;
struct TYPE_4__ {int* arg; } ;
struct qlcnic_cmd_args {TYPE_2__ req; } ;
struct qlcnic_adapter {TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BIT_0 ; 
 int BIT_31 ; 
 int BIT_8 ; 
 int EINVAL ; 
 int QLCNIC_MAC_ADD ; 
 int QLCNIC_MAC_VLAN_ADD ; 
 int QLCNIC_MAC_VLAN_DEL ; 
 scalar_t__ QLC_PVID_MODE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qlcnic_sriov_validate_cfg_macvlan(struct qlcnic_adapter *adapter,
					     struct qlcnic_vf_info *vf,
					     struct qlcnic_cmd_args *cmd)
{
	struct qlcnic_macvlan_mbx *macvlan;
	struct qlcnic_vport *vp = vf->vp;
	u8 op, new_op;

	if (!(cmd->req.arg[1] & BIT_8))
		return -EINVAL;

	cmd->req.arg[1] |= (vf->vp->handle << 16);
	cmd->req.arg[1] |= BIT_31;

	macvlan = (struct qlcnic_macvlan_mbx *)&cmd->req.arg[2];
	if (!(macvlan->mac_addr0 & BIT_0)) {
		dev_err(&adapter->pdev->dev,
			"MAC address change is not allowed from VF %d",
			vf->pci_func);
		return -EINVAL;
	}

	if (vp->vlan_mode == QLC_PVID_MODE) {
		op = cmd->req.arg[1] & 0x7;
		cmd->req.arg[1] &= ~0x7;
		new_op = (op == QLCNIC_MAC_ADD || op == QLCNIC_MAC_VLAN_ADD) ?
			 QLCNIC_MAC_VLAN_ADD : QLCNIC_MAC_VLAN_DEL;
		cmd->req.arg[3] |= vp->vlan << 16;
		cmd->req.arg[1] |= new_op;
	}

	return 0;
}