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
struct qlcnic_vf_info {int /*<<< orphan*/  pci_func; int /*<<< orphan*/  state; TYPE_1__* adapter; } ;
struct qlcnic_sriov {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLC_BC_VF_FLR ; 
 int /*<<< orphan*/  QLC_BC_VF_STATE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_sriov_pf_process_flr ; 
 int /*<<< orphan*/  qlcnic_sriov_schedule_flr (struct qlcnic_sriov*,struct qlcnic_vf_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void qlcnic_sriov_pf_handle_flr(struct qlcnic_sriov *sriov,
				struct qlcnic_vf_info *vf)
{
	struct net_device *dev = vf->adapter->netdev;

	if (!test_and_clear_bit(QLC_BC_VF_STATE, &vf->state)) {
		clear_bit(QLC_BC_VF_FLR, &vf->state);
		return;
	}

	if (test_and_set_bit(QLC_BC_VF_FLR, &vf->state)) {
		netdev_info(dev, "FLR for PCI func %d in progress\n",
			    vf->pci_func);
		return;
	}

	qlcnic_sriov_schedule_flr(sriov, vf, qlcnic_sriov_pf_process_flr);
	netdev_info(dev, "FLR received for PCI func %d\n", vf->pci_func);
}