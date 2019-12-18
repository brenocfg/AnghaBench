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
struct qlcnic_adapter {TYPE_1__* nic_ops; } ;
struct TYPE_2__ {scalar_t__ (* init_driver ) (struct qlcnic_adapter*) ;} ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ qlcnic_83xx_configure_opmode (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_enable_mbx_intrpt (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_idc_attach_driver (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_idc_enter_failed_state (struct qlcnic_adapter*,int) ; 
 int /*<<< orphan*/  qlcnic_83xx_register_nic_idc_func (struct qlcnic_adapter*,int) ; 
 int qlcnic_sriov_pf_reinit (struct qlcnic_adapter*) ; 
 scalar_t__ stub1 (struct qlcnic_adapter*) ; 

__attribute__((used)) static int qlcnic_83xx_idc_reattach_driver(struct qlcnic_adapter *adapter)
{
	int err;

	/* register for NIC IDC AEN Events */
	qlcnic_83xx_register_nic_idc_func(adapter, 1);

	err = qlcnic_sriov_pf_reinit(adapter);
	if (err)
		return err;

	qlcnic_83xx_enable_mbx_intrpt(adapter);

	if (qlcnic_83xx_configure_opmode(adapter)) {
		qlcnic_83xx_idc_enter_failed_state(adapter, 1);
		return -EIO;
	}

	if (adapter->nic_ops->init_driver(adapter)) {
		qlcnic_83xx_idc_enter_failed_state(adapter, 1);
		return -EIO;
	}

	qlcnic_83xx_idc_attach_driver(adapter);

	return 0;
}