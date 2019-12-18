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
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct qlcnic_vport {int* mac; } ;
struct qlcnic_macvlan_mbx {int mac_addr0; int mac_addr1; int mac_addr2; int mac_addr3; int mac_addr4; int mac_addr5; scalar_t__ vlan; } ;
struct TYPE_3__ {int* arg; } ;
struct qlcnic_cmd_args {TYPE_1__ req; } ;
struct qlcnic_adapter {TYPE_2__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BIT_31 ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  QLCNIC_CMD_CONFIG_MAC_VLAN ; 
 int QLCNIC_MAC_ADD ; 
 int QLCNIC_MAC_VLAN_ADD ; 
 int QLCNIC_MAC_VLAN_DEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  memcpy (int*,struct qlcnic_macvlan_mbx*,int) ; 
 scalar_t__ qlcnic_alloc_mbx_args (struct qlcnic_cmd_args*,struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_free_mbx_args (struct qlcnic_cmd_args*) ; 
 int qlcnic_issue_cmd (struct qlcnic_adapter*,struct qlcnic_cmd_args*) ; 
 int qlcnic_sriov_pf_get_vport_handle (struct qlcnic_adapter*,scalar_t__) ; 

__attribute__((used)) static int qlcnic_sriov_cfg_vf_def_mac(struct qlcnic_adapter *adapter,
				       struct qlcnic_vport *vp,
				       u16 func, u16 vlan, u8 op)
{
	struct qlcnic_cmd_args cmd;
	struct qlcnic_macvlan_mbx mv;
	u8 *addr;
	int err;
	u32 *buf;
	int vpid;

	if (qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_CONFIG_MAC_VLAN))
		return -ENOMEM;

	vpid = qlcnic_sriov_pf_get_vport_handle(adapter, func);
	if (vpid < 0) {
		err = -EINVAL;
		goto out;
	}

	if (vlan)
		op = ((op == QLCNIC_MAC_ADD || op == QLCNIC_MAC_VLAN_ADD) ?
		      QLCNIC_MAC_VLAN_ADD : QLCNIC_MAC_VLAN_DEL);

	cmd.req.arg[1] = op | (1 << 8) | (3 << 6);
	cmd.req.arg[1] |= ((vpid & 0xffff) << 16) | BIT_31;

	addr = vp->mac;
	mv.vlan = vlan;
	mv.mac_addr0 = addr[0];
	mv.mac_addr1 = addr[1];
	mv.mac_addr2 = addr[2];
	mv.mac_addr3 = addr[3];
	mv.mac_addr4 = addr[4];
	mv.mac_addr5 = addr[5];
	buf = &cmd.req.arg[2];
	memcpy(buf, &mv, sizeof(struct qlcnic_macvlan_mbx));

	err = qlcnic_issue_cmd(adapter, &cmd);

	if (err)
		dev_err(&adapter->pdev->dev,
			"MAC-VLAN %s to CAM failed, err=%d.\n",
			((op == 1) ? "add " : "delete "), err);

out:
	qlcnic_free_mbx_args(&cmd);
	return err;
}