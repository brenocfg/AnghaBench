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
struct qlcnic_adapter {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ qlcnic_83xx_check_hw_status (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_idc_enter_failed_state (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_83xx_idc_enter_ready_state (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_83xx_idc_restart_hw (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_83xx_idc_update_audit_reg (struct qlcnic_adapter*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_83xx_idc_update_drv_presence_reg (struct qlcnic_adapter*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ qlcnic_load_fw_file ; 

__attribute__((used)) static int qlcnic_83xx_idc_cold_state_handler(struct qlcnic_adapter *adapter)
{
	qlcnic_83xx_idc_update_drv_presence_reg(adapter, 1, 0);
	qlcnic_83xx_idc_update_audit_reg(adapter, 1, 0);

	if (qlcnic_load_fw_file) {
		qlcnic_83xx_idc_restart_hw(adapter, 0);
	} else {
		if (qlcnic_83xx_check_hw_status(adapter)) {
			qlcnic_83xx_idc_enter_failed_state(adapter, 0);
			return -EIO;
		} else {
			qlcnic_83xx_idc_enter_ready_state(adapter, 0);
		}
	}
	return 0;
}