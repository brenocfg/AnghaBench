#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct qlcnic_vport {scalar_t__ vlan; } ;
struct qlcnic_vf_info {int /*<<< orphan*/  pci_func; int /*<<< orphan*/  rx_ctx_id; struct qlcnic_vport* vp; } ;
struct qlcnic_adapter {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  QLCNIC_MAC_ADD ; 
 int /*<<< orphan*/  QLCNIC_MAC_DEL ; 
 int /*<<< orphan*/  qlcnic_sriov_cfg_vf_def_mac (struct qlcnic_adapter*,struct qlcnic_vport*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qlcnic_sriov_pf_del_guest_vlan(struct qlcnic_adapter *adapter,
					  struct qlcnic_vf_info *vf)

{
	struct qlcnic_vport *vp = vf->vp;

	if (!vp->vlan)
		return -EINVAL;

	if (!vf->rx_ctx_id) {
		vp->vlan = 0;
		return 0;
	}

	qlcnic_sriov_cfg_vf_def_mac(adapter, vp, vf->pci_func,
				    vp->vlan, QLCNIC_MAC_DEL);
	vp->vlan = 0;
	qlcnic_sriov_cfg_vf_def_mac(adapter, vp, vf->pci_func,
				    0, QLCNIC_MAC_ADD);
	return 0;
}