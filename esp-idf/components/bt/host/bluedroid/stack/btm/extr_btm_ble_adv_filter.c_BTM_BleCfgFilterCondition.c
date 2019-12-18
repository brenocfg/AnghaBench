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
typedef  scalar_t__ tBTM_STATUS ;
typedef  int /*<<< orphan*/  tBTM_BLE_SCAN_COND_OP ;
typedef  int /*<<< orphan*/  tBTM_BLE_REF_VALUE ;
typedef  int /*<<< orphan*/  tBTM_BLE_PF_FILT_INDEX ;
typedef  int tBTM_BLE_PF_COND_TYPE ;
typedef  int /*<<< orphan*/  tBTM_BLE_PF_COND_PARAM ;
typedef  int /*<<< orphan*/  tBTM_BLE_PF_CFG_CBACK ;
typedef  int /*<<< orphan*/  UINT8 ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_BLE_FILT_CFG ; 
 int /*<<< orphan*/  BTM_BLE_META_PF_FEAT_SEL ; 
#define  BTM_BLE_PF_ADDR_FILTER 135 
#define  BTM_BLE_PF_LOCAL_NAME 134 
#define  BTM_BLE_PF_MANU_DATA 133 
#define  BTM_BLE_PF_SRVC_DATA 132 
#define  BTM_BLE_PF_SRVC_DATA_PATTERN 131 
#define  BTM_BLE_PF_SRVC_SOL_UUID 130 
#define  BTM_BLE_PF_SRVC_UUID 129 
#define  BTM_BLE_PF_TYPE_ALL 128 
 scalar_t__ BTM_CMD_STARTED ; 
 scalar_t__ BTM_ILLEGAL_VALUE ; 
 scalar_t__ BTM_SUCCESS ; 
 int /*<<< orphan*/  BTM_TRACE_EVENT (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTM_TRACE_WARNING (char*,int) ; 
 int /*<<< orphan*/  btm_ble_advfilt_enq_op_q (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ btm_ble_clear_scan_pf_filter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btm_ble_condtype_to_ocf (int) ; 
 scalar_t__ btm_ble_obtain_vsc_details () ; 
 scalar_t__ btm_ble_update_addr_filter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ btm_ble_update_pf_local_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ btm_ble_update_pf_manu_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ btm_ble_update_srvc_data_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ btm_ble_update_uuid_filter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

tBTM_STATUS BTM_BleCfgFilterCondition(tBTM_BLE_SCAN_COND_OP action,
                                      tBTM_BLE_PF_COND_TYPE cond_type,
                                      tBTM_BLE_PF_FILT_INDEX filt_index,
                                      tBTM_BLE_PF_COND_PARAM *p_cond,
                                      tBTM_BLE_PF_CFG_CBACK *p_cmpl_cback,
                                      tBTM_BLE_REF_VALUE ref_value)
{
    tBTM_STATUS     st = BTM_ILLEGAL_VALUE;
    UINT8 ocf = 0;
    BTM_TRACE_EVENT (" BTM_BleCfgFilterCondition action:%d, cond_type:%d, index:%d", action,
                     cond_type, filt_index);

    if (BTM_SUCCESS  != btm_ble_obtain_vsc_details()) {
        return st;
    }

    switch (cond_type) {
    /* write service data filter */
    case BTM_BLE_PF_SRVC_DATA_PATTERN:
    /* write manufacturer data filter */
    case BTM_BLE_PF_MANU_DATA:
        st = btm_ble_update_pf_manu_data(action, filt_index, p_cond, cond_type, 0, ref_value);
        break;

    /* write local name filter */
    case BTM_BLE_PF_LOCAL_NAME:
        st = btm_ble_update_pf_local_name(action, filt_index, p_cond);
        break;

    /* filter on advertiser address */
    case BTM_BLE_PF_ADDR_FILTER:
        st = btm_ble_update_addr_filter(action, filt_index, p_cond);
        break;

    /* filter on service/solicitated UUID */
    case BTM_BLE_PF_SRVC_UUID:
    case BTM_BLE_PF_SRVC_SOL_UUID:
        st = btm_ble_update_uuid_filter(action, filt_index, cond_type, p_cond, 0, ref_value);
        break;

    case BTM_BLE_PF_SRVC_DATA:
        st = btm_ble_update_srvc_data_change(action, filt_index, p_cond);
        break;

    case BTM_BLE_PF_TYPE_ALL: /* only used to clear filter */
        st = btm_ble_clear_scan_pf_filter(action, filt_index, p_cond, p_cmpl_cback,
                                          0, ref_value);
        break;

    default:
        BTM_TRACE_WARNING("condition type [%d] not supported currently.", cond_type);
        break;
    }

    if (BTM_CMD_STARTED == st && cond_type != BTM_BLE_PF_TYPE_ALL) {
        ocf = btm_ble_condtype_to_ocf(cond_type);
        btm_ble_advfilt_enq_op_q(action, ocf, BTM_BLE_FILT_CFG, ref_value, p_cmpl_cback, NULL);
    } else if (BTM_CMD_STARTED == st && BTM_BLE_PF_TYPE_ALL == cond_type) {
        btm_ble_advfilt_enq_op_q(action, BTM_BLE_META_PF_FEAT_SEL, BTM_BLE_FILT_CFG,
                                 ref_value, p_cmpl_cback, NULL);
    }
    return st;
}