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
struct qlcnic_adapter {TYPE_1__* ahw; int /*<<< orphan*/  state; } ;
struct TYPE_2__ {int /*<<< orphan*/  op_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_MGMT_FUNC ; 
 int /*<<< orphan*/  QLCNIC_SRIOV_PF_FUNC ; 
 int /*<<< orphan*/  __QLCNIC_SRIOV_ENABLE ; 
 int /*<<< orphan*/  __qlcnic_sriov_cleanup (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int qlcnic_sriov_init (struct qlcnic_adapter*,int) ; 
 int qlcnic_sriov_pf_create_flr_queue (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_sriov_pf_del_flr_queue (struct qlcnic_adapter*) ; 
 int qlcnic_sriov_pf_enable (struct qlcnic_adapter*,int) ; 
 int qlcnic_sriov_pf_init (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __qlcnic_pci_sriov_enable(struct qlcnic_adapter *adapter,
				     int num_vfs)
{
	int err = 0;

	set_bit(__QLCNIC_SRIOV_ENABLE, &adapter->state);
	adapter->ahw->op_mode = QLCNIC_SRIOV_PF_FUNC;

	err = qlcnic_sriov_init(adapter, num_vfs);
	if (err)
		goto clear_op_mode;

	err = qlcnic_sriov_pf_create_flr_queue(adapter);
	if (err)
		goto sriov_cleanup;

	err = qlcnic_sriov_pf_init(adapter);
	if (err)
		goto del_flr_queue;

	err = qlcnic_sriov_pf_enable(adapter, num_vfs);
	return err;

del_flr_queue:
	qlcnic_sriov_pf_del_flr_queue(adapter);

sriov_cleanup:
	__qlcnic_sriov_cleanup(adapter);

clear_op_mode:
	clear_bit(__QLCNIC_SRIOV_ENABLE, &adapter->state);
	adapter->ahw->op_mode = QLCNIC_MGMT_FUNC;
	return err;
}