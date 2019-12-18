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
struct qlcnic_adapter {TYPE_2__* ahw; } ;
struct TYPE_3__ {int /*<<< orphan*/  status; } ;
struct TYPE_4__ {TYPE_1__ idc; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_BC_CMD_CHANNEL_INIT ; 
 int /*<<< orphan*/  QLCNIC_BC_CMD_CHANNEL_TERM ; 
 int /*<<< orphan*/  QLC_83XX_MBX_READY ; 
 int /*<<< orphan*/  qlcnic_83xx_enable_mbx_intrpt (struct qlcnic_adapter*) ; 
 int qlcnic_sriov_cfg_bc_intr (struct qlcnic_adapter*,int) ; 
 int qlcnic_sriov_channel_cfg_cmd (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int qlcnic_sriov_vf_init_driver (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qlcnic_sriov_vf_reinit_driver(struct qlcnic_adapter *adapter)
{
	int err;

	set_bit(QLC_83XX_MBX_READY, &adapter->ahw->idc.status);
	qlcnic_83xx_enable_mbx_intrpt(adapter);

	err = qlcnic_sriov_cfg_bc_intr(adapter, 1);
	if (err)
		return err;

	err = qlcnic_sriov_channel_cfg_cmd(adapter, QLCNIC_BC_CMD_CHANNEL_INIT);
	if (err)
		goto err_out_cleanup_bc_intr;

	err = qlcnic_sriov_vf_init_driver(adapter);
	if (err)
		goto err_out_term_channel;

	return 0;

err_out_term_channel:
	qlcnic_sriov_channel_cfg_cmd(adapter, QLCNIC_BC_CMD_CHANNEL_TERM);

err_out_cleanup_bc_intr:
	qlcnic_sriov_cfg_bc_intr(adapter, 0);
	return err;
}