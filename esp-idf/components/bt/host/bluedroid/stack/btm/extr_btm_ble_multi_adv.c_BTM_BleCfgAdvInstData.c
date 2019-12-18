#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTM_STATUS ;
struct TYPE_9__ {scalar_t__ adv_inst_max; } ;
typedef  TYPE_2__ tBTM_BLE_VSC_CB ;
typedef  int /*<<< orphan*/  tBTM_BLE_AD_MASK ;
struct TYPE_10__ {int /*<<< orphan*/  flag; } ;
typedef  TYPE_3__ tBTM_BLE_ADV_DATA ;
typedef  scalar_t__ UINT8 ;
struct TYPE_8__ {int /*<<< orphan*/  discoverable_mode; int /*<<< orphan*/  connectable_mode; } ;
struct TYPE_11__ {TYPE_1__ btm_inq_vars; } ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_BLE_MULTI_ADV_DATA_EVT ; 
 scalar_t__ BTM_BLE_MULTI_ADV_DEFAULT_STD ; 
 scalar_t__ BTM_BLE_MULTI_ADV_MAX ; 
 scalar_t__ BTM_BLE_MULTI_ADV_WRITE_ADV_DATA ; 
 int BTM_BLE_MULTI_ADV_WRITE_DATA_LEN ; 
 scalar_t__ BTM_BLE_MULTI_ADV_WRITE_SCAN_RSP_DATA ; 
 int /*<<< orphan*/  BTM_BleGetVendorCapabilities (TYPE_2__*) ; 
 int /*<<< orphan*/  BTM_CMD_STARTED ; 
 int /*<<< orphan*/  BTM_ERR_PROCESSING ; 
 int /*<<< orphan*/  BTM_ILLEGAL_VALUE ; 
 int /*<<< orphan*/  BTM_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  BTM_TRACE_EVENT (char*,scalar_t__) ; 
 int /*<<< orphan*/  BTM_VendorSpecificCommand (int /*<<< orphan*/ ,scalar_t__,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_BLE_MULTI_ADV_OCF ; 
 int /*<<< orphan*/  UINT8_TO_STREAM (scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  btm_ble_build_adv_data (int /*<<< orphan*/ *,scalar_t__**,TYPE_3__*) ; 
 int /*<<< orphan*/  btm_ble_multi_adv_enq_op_q (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btm_ble_multi_adv_vsc_cmpl_cback ; 
 int /*<<< orphan*/  btm_ble_update_dmt_flag_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__ btm_cb ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 

tBTM_STATUS BTM_BleCfgAdvInstData (UINT8 inst_id, BOOLEAN is_scan_rsp,
                                   tBTM_BLE_AD_MASK data_mask,
                                   tBTM_BLE_ADV_DATA *p_data)
{
    UINT8       param[BTM_BLE_MULTI_ADV_WRITE_DATA_LEN], *pp = param;
    UINT8       sub_code = (is_scan_rsp) ?
                           BTM_BLE_MULTI_ADV_WRITE_SCAN_RSP_DATA : BTM_BLE_MULTI_ADV_WRITE_ADV_DATA;
    UINT8       *p_len;
    tBTM_STATUS rt;
    UINT8 *pp_temp = (UINT8 *)(param + BTM_BLE_MULTI_ADV_WRITE_DATA_LEN - 1);
    tBTM_BLE_VSC_CB cmn_ble_vsc_cb;

    BTM_BleGetVendorCapabilities(&cmn_ble_vsc_cb);
    if (0 == cmn_ble_vsc_cb.adv_inst_max) {
        BTM_TRACE_ERROR("Controller does not support Multi ADV");
        return BTM_ERR_PROCESSING;
    }

    btm_ble_update_dmt_flag_bits(&p_data->flag, btm_cb.btm_inq_vars.connectable_mode,
                                 btm_cb.btm_inq_vars.discoverable_mode);

    BTM_TRACE_EVENT("BTM_BleCfgAdvInstData called with inst_id:%d", inst_id);
    if (inst_id > BTM_BLE_MULTI_ADV_MAX || inst_id == BTM_BLE_MULTI_ADV_DEFAULT_STD) {
        return BTM_ILLEGAL_VALUE;
    }

    memset(param, 0, BTM_BLE_MULTI_ADV_WRITE_DATA_LEN);

    UINT8_TO_STREAM(pp, sub_code);
    p_len = pp ++;
    btm_ble_build_adv_data(&data_mask, &pp, p_data);
    *p_len = (UINT8)(pp - param - 2);
    UINT8_TO_STREAM(pp_temp, inst_id);

    if ((rt = BTM_VendorSpecificCommand (HCI_BLE_MULTI_ADV_OCF,
                                         (UINT8)BTM_BLE_MULTI_ADV_WRITE_DATA_LEN,
                                         param,
                                         btm_ble_multi_adv_vsc_cmpl_cback))
            == BTM_CMD_STARTED) {
        btm_ble_multi_adv_enq_op_q(sub_code, inst_id, BTM_BLE_MULTI_ADV_DATA_EVT);
    }
    return rt;
}