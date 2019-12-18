#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int err_code; int /*<<< orphan*/  status; } ;
struct qlcnic_hardware_context {TYPE_3__ idc; int /*<<< orphan*/  mbx_lock; } ;
struct TYPE_5__ {int /*<<< orphan*/  work; } ;
struct qlcnic_adapter {struct qlcnic_hardware_context* ahw; TYPE_2__ fw_work; int /*<<< orphan*/  idc_aen_work; TYPE_1__* nic_ops; } ;
struct TYPE_4__ {scalar_t__ (* init_driver ) (struct qlcnic_adapter*) ;} ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QLC_83XX_MBX_READY ; 
 scalar_t__ qlcnic_83xx_check_hw_status (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_clear_function_resources (struct qlcnic_adapter*) ; 
 scalar_t__ qlcnic_83xx_configure_opmode (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_idc_aen_work ; 
 scalar_t__ qlcnic_83xx_idc_init (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_idc_poll_dev_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qlcnic_83xx_read_flash_descriptor_table (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_read_flash_mfg_id (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_register_nic_idc_func (struct qlcnic_adapter*,int) ; 
 scalar_t__ qlcnic_sriov_vf_check (struct qlcnic_adapter*) ; 
 int qlcnic_sriov_vf_init (struct qlcnic_adapter*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct qlcnic_adapter*) ; 

int qlcnic_83xx_init(struct qlcnic_adapter *adapter, int pci_using_dac)
{
	struct qlcnic_hardware_context *ahw = adapter->ahw;

	if (qlcnic_sriov_vf_check(adapter))
		return qlcnic_sriov_vf_init(adapter, pci_using_dac);

	if (qlcnic_83xx_check_hw_status(adapter))
		return -EIO;

	/* Initilaize 83xx mailbox spinlock */
	spin_lock_init(&ahw->mbx_lock);

	set_bit(QLC_83XX_MBX_READY, &adapter->ahw->idc.status);
	qlcnic_83xx_clear_function_resources(adapter);

	/* register for NIC IDC AEN Events */
	qlcnic_83xx_register_nic_idc_func(adapter, 1);

	if (!qlcnic_83xx_read_flash_descriptor_table(adapter))
		qlcnic_83xx_read_flash_mfg_id(adapter);

	if (qlcnic_83xx_idc_init(adapter))
		return -EIO;

	/* Configure default, SR-IOV or Virtual NIC mode of operation */
	if (qlcnic_83xx_configure_opmode(adapter))
		return -EIO;

	/* Perform operating mode specific initialization */
	if (adapter->nic_ops->init_driver(adapter))
		return -EIO;

	INIT_DELAYED_WORK(&adapter->idc_aen_work, qlcnic_83xx_idc_aen_work);

	/* Periodically monitor device status */
	qlcnic_83xx_idc_poll_dev_state(&adapter->fw_work.work);

	return adapter->ahw->idc.err_code;
}