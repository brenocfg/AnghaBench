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
typedef  int /*<<< orphan*/  tBTM_STATUS ;
typedef  int UINT8 ;
struct TYPE_2__ {int /*<<< orphan*/  cur_state; int /*<<< orphan*/  discard_rule; int /*<<< orphan*/  addr_type; int /*<<< orphan*/  scan_window; int /*<<< orphan*/  scan_interval; } ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int BTM_BLE_BATCH_SCAN_ENB_DISAB_CUST_FEATURE ; 
 int BTM_BLE_BATCH_SCAN_ENB_DISB_LEN ; 
 int /*<<< orphan*/  BTM_BLE_BATCH_SCAN_MODE_DISABLE ; 
 int /*<<< orphan*/  BTM_BLE_SCAN_DISABLE_CALLED ; 
 int /*<<< orphan*/  BTM_BLE_SCAN_ENABLE_CALLED ; 
 int /*<<< orphan*/  BTM_CMD_STARTED ; 
 int /*<<< orphan*/  BTM_ILLEGAL_VALUE ; 
 int /*<<< orphan*/  BTM_MODE_UNSUPPORTED ; 
 int /*<<< orphan*/  BTM_NO_RESOURCES ; 
 int /*<<< orphan*/  BTM_TRACE_ERROR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTM_VendorSpecificCommand (int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_BLE_BATCH_SCAN_OCF ; 
 int /*<<< orphan*/  UINT8_TO_STREAM (int*,int) ; 
 TYPE_1__ ble_batchscan_cb ; 
 int /*<<< orphan*/  btm_ble_batchscan_vsc_cmpl_cback ; 
 int /*<<< orphan*/  btm_ble_set_batchscan_param (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

tBTM_STATUS btm_ble_enable_disable_batchscan(BOOLEAN should_enable)
{
    tBTM_STATUS     status = BTM_NO_RESOURCES;
    UINT8 shld_enable = 0x01;
    UINT8 enable_param[BTM_BLE_BATCH_SCAN_ENB_DISB_LEN], *pp_enable;

    if (!should_enable) {
        shld_enable = 0x00;
    }

    if (should_enable) {
        pp_enable = enable_param;
        memset(enable_param, 0, BTM_BLE_BATCH_SCAN_ENB_DISB_LEN);

        UINT8_TO_STREAM (pp_enable, BTM_BLE_BATCH_SCAN_ENB_DISAB_CUST_FEATURE);
        UINT8_TO_STREAM (pp_enable, shld_enable);

        if ((status = BTM_VendorSpecificCommand(HCI_BLE_BATCH_SCAN_OCF,
                                                BTM_BLE_BATCH_SCAN_ENB_DISB_LEN, enable_param,
                                                btm_ble_batchscan_vsc_cmpl_cback)) != BTM_CMD_STARTED) {
            status = BTM_MODE_UNSUPPORTED;
            BTM_TRACE_ERROR("btm_ble_enable_disable_batchscan %d", status);
            return BTM_ILLEGAL_VALUE;
        }
    } else if ((status = btm_ble_set_batchscan_param(BTM_BLE_BATCH_SCAN_MODE_DISABLE,
                         ble_batchscan_cb.scan_interval, ble_batchscan_cb.scan_window,
                         ble_batchscan_cb.addr_type, ble_batchscan_cb.discard_rule)) != BTM_CMD_STARTED) {
        status = BTM_MODE_UNSUPPORTED;
        BTM_TRACE_ERROR("btm_ble_enable_disable_batchscan %d", status);
        return BTM_ILLEGAL_VALUE;
    }

    if (should_enable) {
        ble_batchscan_cb.cur_state = BTM_BLE_SCAN_ENABLE_CALLED;
    } else {
        ble_batchscan_cb.cur_state = BTM_BLE_SCAN_DISABLE_CALLED;
    }
    return status;
}