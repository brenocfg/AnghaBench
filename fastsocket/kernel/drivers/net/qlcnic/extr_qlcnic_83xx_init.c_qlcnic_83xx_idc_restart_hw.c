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
 int /*<<< orphan*/  qlcnic_83xx_idc_clear_registers (struct qlcnic_adapter*,int) ; 
 int /*<<< orphan*/  qlcnic_83xx_idc_enter_failed_state (struct qlcnic_adapter*,int) ; 
 int qlcnic_83xx_idc_enter_ready_state (struct qlcnic_adapter*,int) ; 
 int qlcnic_83xx_restart_hw (struct qlcnic_adapter*) ; 

__attribute__((used)) static int qlcnic_83xx_idc_restart_hw(struct qlcnic_adapter *adapter, int lock)
{
	int ret = 0;

	ret = qlcnic_83xx_restart_hw(adapter);

	if (ret) {
		qlcnic_83xx_idc_enter_failed_state(adapter, lock);
	} else {
		qlcnic_83xx_idc_clear_registers(adapter, lock);
		ret = qlcnic_83xx_idc_enter_ready_state(adapter, lock);
	}

	return ret;
}