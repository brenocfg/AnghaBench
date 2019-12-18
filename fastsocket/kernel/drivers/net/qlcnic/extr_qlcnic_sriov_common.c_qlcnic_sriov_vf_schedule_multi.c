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
struct qlcnic_back_channel {int dummy; } ;
struct qlcnic_adapter {scalar_t__ need_fw_reset; TYPE_2__* ahw; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* sriov; } ;
struct TYPE_3__ {struct qlcnic_back_channel bc; } ;

/* Variables and functions */
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  qlcnic_sriov_handle_async_multi ; 
 int /*<<< orphan*/  qlcnic_sriov_schedule_bc_async_work (struct qlcnic_back_channel*,int /*<<< orphan*/ ,struct net_device*) ; 

void qlcnic_sriov_vf_schedule_multi(struct net_device *netdev)
{
	struct qlcnic_adapter *adapter = netdev_priv(netdev);
	struct qlcnic_back_channel *bc = &adapter->ahw->sriov->bc;

	if (adapter->need_fw_reset)
		return;

	qlcnic_sriov_schedule_bc_async_work(bc, qlcnic_sriov_handle_async_multi,
					    netdev);
}