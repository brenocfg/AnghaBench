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
typedef  int /*<<< orphan*/  tBTM_BLE_REF_VALUE ;
typedef  int /*<<< orphan*/  tBTM_BLE_PF_STATUS_CBACK ;
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_2__ {int /*<<< orphan*/ * p_filt_stat_cback; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_BLE_FILT_ENABLE_DISABLE ; 
 int /*<<< orphan*/  BTM_BLE_META_PF_ENABLE ; 
 int /*<<< orphan*/  BTM_BLE_PCF_ENABLE_LEN ; 
 int /*<<< orphan*/  BTM_CMD_STARTED ; 
 scalar_t__ BTM_SUCCESS ; 
 int /*<<< orphan*/  BTM_VendorSpecificCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTM_WRONG_MODE ; 
 int /*<<< orphan*/  HCI_BLE_ADV_FILTER_OCF ; 
 int /*<<< orphan*/  UINT8_TO_STREAM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ btm_ble_adv_filt_cb ; 
 int /*<<< orphan*/  btm_ble_advfilt_enq_op_q (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ btm_ble_obtain_vsc_details () ; 
 int /*<<< orphan*/  btm_ble_scan_pf_cmpl_cback ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

tBTM_STATUS BTM_BleEnableDisableFilterFeature(UINT8 enable,
        tBTM_BLE_PF_STATUS_CBACK *p_stat_cback,
        tBTM_BLE_REF_VALUE ref_value)
{
    UINT8           param[20], *p;
    tBTM_STATUS     st = BTM_WRONG_MODE;

    if (BTM_SUCCESS  != btm_ble_obtain_vsc_details()) {
        return st;
    }

    p = param;
    memset(param, 0, 20);

    /* enable the content filter in controller */
    p = param;
    UINT8_TO_STREAM(p, BTM_BLE_META_PF_ENABLE);
    /* enable adv data payload filtering */
    UINT8_TO_STREAM(p, enable);

    if ((st = BTM_VendorSpecificCommand (HCI_BLE_ADV_FILTER_OCF,
                                         BTM_BLE_PCF_ENABLE_LEN, param,
                                         btm_ble_scan_pf_cmpl_cback)) == BTM_CMD_STARTED) {
        btm_ble_adv_filt_cb.p_filt_stat_cback = p_stat_cback;
        btm_ble_advfilt_enq_op_q(enable, BTM_BLE_META_PF_ENABLE, BTM_BLE_FILT_ENABLE_DISABLE,
                                 ref_value, NULL, NULL);
    }
    return st;
}