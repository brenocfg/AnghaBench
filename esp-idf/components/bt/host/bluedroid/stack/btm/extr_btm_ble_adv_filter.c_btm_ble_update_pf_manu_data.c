#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTM_STATUS ;
typedef  int /*<<< orphan*/  tBTM_BLE_SCAN_COND_OP ;
typedef  int /*<<< orphan*/  tBTM_BLE_REF_VALUE ;
struct TYPE_6__ {int data_len; int /*<<< orphan*/ * p_pattern_mask; int /*<<< orphan*/ * p_pattern; } ;
typedef  TYPE_1__ tBTM_BLE_PF_SRVC_PATTERN_COND ;
struct TYPE_7__ {int data_len; scalar_t__ company_id; scalar_t__ company_id_mask; int /*<<< orphan*/ * p_pattern_mask; int /*<<< orphan*/ * p_pattern; } ;
typedef  TYPE_2__ tBTM_BLE_PF_MANU_COND ;
typedef  int /*<<< orphan*/  tBTM_BLE_PF_FILT_INDEX ;
typedef  scalar_t__ tBTM_BLE_PF_COND_TYPE ;
struct TYPE_8__ {TYPE_1__ srvc_data; TYPE_2__ manu_data; } ;
typedef  TYPE_3__ tBTM_BLE_PF_COND_PARAM ;
typedef  int /*<<< orphan*/  tBTM_BLE_FILT_CB_EVT ;
typedef  int /*<<< orphan*/  tBLE_BD_ADDR ;
typedef  int UINT8 ;
struct TYPE_9__ {int cur_filter_target; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_TO_STREAM (int*,int /*<<< orphan*/ *,int) ; 
 int BTM_BLE_ADV_FILT_META_HDR_LENGTH ; 
 int /*<<< orphan*/  BTM_BLE_META_PF_MANU_DATA ; 
 int /*<<< orphan*/  BTM_BLE_META_PF_SRVC_DATA ; 
 scalar_t__ BTM_BLE_PF_SRVC_DATA_PATTERN ; 
 int BTM_BLE_PF_STR_LEN_MAX ; 
 int /*<<< orphan*/  BTM_BLE_SCAN_COND_ADD ; 
 int /*<<< orphan*/  BTM_BLE_SCAN_COND_DELETE ; 
 int /*<<< orphan*/  BTM_ILLEGAL_VALUE ; 
 int /*<<< orphan*/  BTM_NO_RESOURCES ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*,int) ; 
 int /*<<< orphan*/  BTM_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  BTM_TRACE_EVENT (char*,int) ; 
 int /*<<< orphan*/  BTM_VendorSpecificCommand (int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_BLE_ADV_FILTER_OCF ; 
 int /*<<< orphan*/  UINT16_TO_STREAM (int*,scalar_t__) ; 
 int /*<<< orphan*/  UINT8_TO_STREAM (int*,int /*<<< orphan*/ ) ; 
 TYPE_5__ btm_ble_adv_filt_cb ; 
 int /*<<< orphan*/  btm_ble_scan_pf_cmpl_cback ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 

tBTM_STATUS btm_ble_update_pf_manu_data(tBTM_BLE_SCAN_COND_OP action,
                                        tBTM_BLE_PF_FILT_INDEX filt_index,
                                        tBTM_BLE_PF_COND_PARAM *p_data,
                                        tBTM_BLE_PF_COND_TYPE cond_type,
                                        tBTM_BLE_FILT_CB_EVT cb_evt,
                                        tBTM_BLE_REF_VALUE ref_value)
{
    tBTM_BLE_PF_MANU_COND *p_manu_data = (p_data == NULL) ? NULL : &p_data->manu_data;
    tBTM_BLE_PF_SRVC_PATTERN_COND *p_srvc_data = (p_data == NULL) ? NULL : &p_data->srvc_data;

    UINT8 param[BTM_BLE_PF_STR_LEN_MAX + BTM_BLE_PF_STR_LEN_MAX + BTM_BLE_ADV_FILT_META_HDR_LENGTH],
          *p = param,
           len = BTM_BLE_ADV_FILT_META_HDR_LENGTH;
    tBTM_STATUS st = BTM_ILLEGAL_VALUE;

    if (NULL == p_data) {
        return st;
    }

    memset(param, 0, BTM_BLE_PF_STR_LEN_MAX + BTM_BLE_PF_STR_LEN_MAX
           + BTM_BLE_ADV_FILT_META_HDR_LENGTH);

    if (BTM_BLE_PF_SRVC_DATA_PATTERN == cond_type) {
        UINT8_TO_STREAM(p, BTM_BLE_META_PF_SRVC_DATA);
    } else {
        UINT8_TO_STREAM(p, BTM_BLE_META_PF_MANU_DATA);
    }

    UINT8_TO_STREAM(p, action);

    /* Filter index */
    UINT8_TO_STREAM(p, filt_index);

    if (BTM_BLE_SCAN_COND_ADD == action || BTM_BLE_SCAN_COND_DELETE == action) {
        if (BTM_BLE_PF_SRVC_DATA_PATTERN == cond_type) {
            if (NULL == p_srvc_data) {
                return st;
            }
            if (p_srvc_data->data_len > (BTM_BLE_PF_STR_LEN_MAX - 2)) {
                p_srvc_data->data_len = (BTM_BLE_PF_STR_LEN_MAX - 2);
            }

            if (p_srvc_data->data_len > 0) {
                ARRAY_TO_STREAM(p, p_srvc_data->p_pattern, p_srvc_data->data_len);
                len += (p_srvc_data->data_len);
                ARRAY_TO_STREAM(p, p_srvc_data->p_pattern_mask, p_srvc_data->data_len);
            }

            len += (p_srvc_data->data_len);
            BTM_TRACE_DEBUG("Service data length: %d", len);
        } else {
            if (NULL == p_manu_data) {
                BTM_TRACE_ERROR("btm_ble_update_pf_manu_data - No manuf data");
                return st;
            }
            BTM_TRACE_EVENT("btm_ble_update_pf_manu_data length: %d",
                            p_manu_data->data_len);
            if (p_manu_data->data_len > (BTM_BLE_PF_STR_LEN_MAX - 2)) {
                p_manu_data->data_len = (BTM_BLE_PF_STR_LEN_MAX - 2);
            }

            UINT16_TO_STREAM(p, p_manu_data->company_id);
            if (p_manu_data->data_len > 0 && p_manu_data->p_pattern_mask != NULL) {
                ARRAY_TO_STREAM(p, p_manu_data->p_pattern, p_manu_data->data_len);
                len += (p_manu_data->data_len + 2);
            } else {
                len += 2;
            }

            if (p_manu_data->company_id_mask != 0) {
                UINT16_TO_STREAM (p, p_manu_data->company_id_mask);
            } else {
                memset(p, 0xff, 2);
                p += 2;
            }
            len += 2;

            if (p_manu_data->data_len > 0 && p_manu_data->p_pattern_mask != NULL) {
                ARRAY_TO_STREAM(p, p_manu_data->p_pattern_mask, p_manu_data->data_len);
                len += (p_manu_data->data_len);
            }

            BTM_TRACE_DEBUG("Manuf data length: %d", len);
        }
    }

    /* send manufacturer*/
    if ((st = BTM_VendorSpecificCommand (HCI_BLE_ADV_FILTER_OCF,
                                         len,
                                         param,
                                         btm_ble_scan_pf_cmpl_cback)) != BTM_NO_RESOURCES) {
        memset(&btm_ble_adv_filt_cb.cur_filter_target, 0, sizeof(tBLE_BD_ADDR));
    } else {
        BTM_TRACE_ERROR("manufacturer data PF filter update failed");
    }

    return st;
}