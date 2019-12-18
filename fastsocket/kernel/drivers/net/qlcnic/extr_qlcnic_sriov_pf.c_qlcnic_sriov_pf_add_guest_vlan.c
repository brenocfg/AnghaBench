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
struct qlcnic_vport {int vlan; } ;
struct qlcnic_vf_info {int /*<<< orphan*/  pci_func; int /*<<< orphan*/  rx_ctx_id; struct qlcnic_vport* vp; } ;
struct TYPE_2__ {int* arg; } ;
struct qlcnic_cmd_args {TYPE_1__ req; } ;
struct qlcnic_adapter {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  QLCNIC_MAC_ADD ; 
 int /*<<< orphan*/  QLCNIC_MAC_DEL ; 
 int qlcnic_sriov_cfg_vf_def_mac (struct qlcnic_adapter*,struct qlcnic_vport*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qlcnic_sriov_pf_add_guest_vlan(struct qlcnic_adapter *adapter,
					  struct qlcnic_vf_info *vf,
					  struct qlcnic_cmd_args *cmd)
{
	struct qlcnic_vport *vp = vf->vp;
	int err = -EIO;

	if (vp->vlan)
		return err;

	if (!vf->rx_ctx_id) {
		vp->vlan = cmd->req.arg[1] >> 16;
		return 0;
	}

	err = qlcnic_sriov_cfg_vf_def_mac(adapter, vp, vf->pci_func,
					  0, QLCNIC_MAC_DEL);
	if (err)
		return err;

	vp->vlan = cmd->req.arg[1] >> 16;
	err = qlcnic_sriov_cfg_vf_def_mac(adapter, vp, vf->pci_func,
					  vp->vlan, QLCNIC_MAC_ADD);

	if (err) {
		qlcnic_sriov_cfg_vf_def_mac(adapter, vp, vf->pci_func,
					    0, QLCNIC_MAC_ADD);
		vp->vlan = 0;
	}

	return err;
}