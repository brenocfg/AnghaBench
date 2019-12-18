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
typedef  int u32 ;
struct TYPE_4__ {scalar_t__ quiesce_req; scalar_t__ collect_dump; int /*<<< orphan*/  status; scalar_t__ (* state_entry ) (struct qlcnic_adapter*) ;} ;
struct qlcnic_hardware_context {scalar_t__ temp; TYPE_2__ idc; scalar_t__ reset_context; } ;
struct qlcnic_adapter {struct qlcnic_hardware_context* ahw; int /*<<< orphan*/  state; int /*<<< orphan*/  flags; TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  QLCNIC_FW_HANG ; 
 scalar_t__ QLCNIC_TEMP_PANIC ; 
 int QLCRDX (struct qlcnic_hardware_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QLC_83XX_IDC_CTRL ; 
 int QLC_83XX_IDC_DISABLE_FW_RESET_RECOVERY ; 
 int QLC_83XX_IDC_GRACEFULL_RESET ; 
 int /*<<< orphan*/  QLC_83XX_MBX_READY ; 
 int /*<<< orphan*/  __QLCNIC_RESETTING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int qlcnic_83xx_check_heartbeat (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_idc_check_fan_failure (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_idc_detach_driver (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_idc_enter_failed_state (struct qlcnic_adapter*,int) ; 
 int /*<<< orphan*/  qlcnic_83xx_idc_enter_need_quiesce (struct qlcnic_adapter*,int) ; 
 int /*<<< orphan*/  qlcnic_83xx_idc_enter_need_reset_state (struct qlcnic_adapter*,int) ; 
 int /*<<< orphan*/  qlcnic_83xx_idc_tx_soft_reset (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_idc_update_audit_reg (struct qlcnic_adapter*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ qlcnic_check_temp (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct qlcnic_adapter*) ; 

__attribute__((used)) static int qlcnic_83xx_idc_ready_state(struct qlcnic_adapter *adapter)
{
	u32 val;
	struct qlcnic_hardware_context *ahw = adapter->ahw;
	int ret = 0;

	/* Perform NIC configuration based ready state entry actions */
	if (ahw->idc.state_entry(adapter))
		return -EIO;

	if (qlcnic_check_temp(adapter)) {
		if (ahw->temp == QLCNIC_TEMP_PANIC) {
			qlcnic_83xx_idc_check_fan_failure(adapter);
			dev_err(&adapter->pdev->dev,
				"Error: device temperature %d above limits\n",
				adapter->ahw->temp);
			clear_bit(QLC_83XX_MBX_READY, &ahw->idc.status);
			set_bit(__QLCNIC_RESETTING, &adapter->state);
			qlcnic_83xx_idc_detach_driver(adapter);
			qlcnic_83xx_idc_enter_failed_state(adapter, 1);
			return -EIO;
		}
	}

	val = QLCRDX(adapter->ahw, QLC_83XX_IDC_CTRL);
	ret = qlcnic_83xx_check_heartbeat(adapter);
	if (ret) {
		adapter->flags |= QLCNIC_FW_HANG;
		if (!(val & QLC_83XX_IDC_DISABLE_FW_RESET_RECOVERY)) {
			clear_bit(QLC_83XX_MBX_READY, &ahw->idc.status);
			set_bit(__QLCNIC_RESETTING, &adapter->state);
			qlcnic_83xx_idc_enter_need_reset_state(adapter, 1);
		}
		return -EIO;
	}

	if ((val & QLC_83XX_IDC_GRACEFULL_RESET) || ahw->idc.collect_dump) {
		/* Move to need reset state and prepare for reset */
		qlcnic_83xx_idc_enter_need_reset_state(adapter, 1);
		return ret;
	}

	/* Check for soft reset request */
	if (ahw->reset_context &&
	    !(val & QLC_83XX_IDC_DISABLE_FW_RESET_RECOVERY)) {
		adapter->ahw->reset_context = 0;
		qlcnic_83xx_idc_tx_soft_reset(adapter);
		return ret;
	}

	/* Move to need quiesce state if requested */
	if (adapter->ahw->idc.quiesce_req) {
		qlcnic_83xx_idc_enter_need_quiesce(adapter, 1);
		qlcnic_83xx_idc_update_audit_reg(adapter, 0, 1);
		return ret;
	}

	return ret;
}