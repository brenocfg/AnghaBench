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
struct qlcnic_hardware_context {int /*<<< orphan*/  fw_hal_version; int /*<<< orphan*/  op_mode; } ;
struct qlcnic_adapter {int /*<<< orphan*/  state; int /*<<< orphan*/ * nic_ops; TYPE_1__* pdev; struct qlcnic_hardware_context* ahw; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_SRIOV_VF_FUNC ; 
 int /*<<< orphan*/  __QLCNIC_SRIOV_ENABLE ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_sriov_vf_ops ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void qlcnic_sriov_vf_set_ops(struct qlcnic_adapter *adapter)
{
	struct qlcnic_hardware_context *ahw = adapter->ahw;

	ahw->op_mode = QLCNIC_SRIOV_VF_FUNC;
	dev_info(&adapter->pdev->dev,
		 "HAL Version: %d Non Privileged SRIOV function\n",
		 ahw->fw_hal_version);
	adapter->nic_ops = &qlcnic_sriov_vf_ops;
	set_bit(__QLCNIC_SRIOV_ENABLE, &adapter->state);
	return;
}