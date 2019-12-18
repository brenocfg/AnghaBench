#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ ble_addr_type; int flag; int /*<<< orphan*/  device_type; scalar_t__* dev_class; scalar_t__ ble_evt_type; scalar_t__ rssi; int /*<<< orphan*/  inq_result_type; } ;
struct TYPE_10__ {TYPE_4__ results; } ;
struct TYPE_12__ {scalar_t__ inq_count; void* scan_rsp; TYPE_1__ inq_info; } ;
typedef  TYPE_3__ tINQ_DB_ENT ;
typedef  TYPE_4__ tBTM_INQ_RESULTS ;
struct TYPE_14__ {scalar_t__ inq_counter; } ;
typedef  TYPE_5__ tBTM_INQUIRY_VAR_ST ;
struct TYPE_15__ {scalar_t__ scan_type; scalar_t__ adv_len; int /*<<< orphan*/  adv_data_cache; } ;
typedef  TYPE_6__ tBTM_BLE_INQ_CB ;
typedef  scalar_t__ UINT8 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_11__ {TYPE_6__ inq_var; } ;
struct TYPE_16__ {TYPE_2__ ble_ctr_cb; TYPE_5__ btm_inq_vars; } ;
typedef  void* BOOLEAN ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 scalar_t__ BLE_ADDR_RANDOM ; 
 scalar_t__ BTM_BLE_ADV_DATA_LEN_MAX ; 
 int /*<<< orphan*/  BTM_BLE_AD_TYPE_16SRV_CMPL ; 
 int /*<<< orphan*/  BTM_BLE_AD_TYPE_APPEARANCE ; 
 int /*<<< orphan*/  BTM_BLE_AD_TYPE_FLAG ; 
 int BTM_BLE_BREDR_NOT_SPT ; 
 scalar_t__ BTM_BLE_CONNECT_DIR_EVT ; 
 scalar_t__ BTM_BLE_CONNECT_EVT ; 
 scalar_t__ BTM_BLE_DISCOVER_EVT ; 
 scalar_t__ BTM_BLE_SCAN_MODE_ACTI ; 
 scalar_t__ BTM_BLE_SCAN_RSP_EVT ; 
 scalar_t__ BTM_COD_MAJOR_PERIPHERAL ; 
 scalar_t__* BTM_CheckAdvData (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  BTM_INQ_RESULT_BLE ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*,...) ; 
 int /*<<< orphan*/  BTM_TRACE_WARNING (char*,scalar_t__) ; 
 int /*<<< orphan*/  BT_DEVICE_TYPE_BLE ; 
 int /*<<< orphan*/  BT_DEVICE_TYPE_DUMO ; 
 void* FALSE ; 
 int /*<<< orphan*/  STREAM_TO_UINT8 (scalar_t__,scalar_t__*) ; 
 void* TRUE ; 
 scalar_t__ UUID_SERVCLASS_LE_HID ; 
 int /*<<< orphan*/  btm_ble_appearance_to_cod (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  btm_ble_cache_adv_data (int /*<<< orphan*/ ,TYPE_4__*,scalar_t__,scalar_t__*,scalar_t__) ; 
 TYPE_7__ btm_cb ; 

BOOLEAN btm_ble_update_inq_result(BD_ADDR bda, tINQ_DB_ENT *p_i, UINT8 addr_type, UINT8 evt_type, UINT8 *p)
{
    BOOLEAN             to_report = TRUE;
    tBTM_INQ_RESULTS     *p_cur = &p_i->inq_info.results;
    UINT8               len;
    UINT8               *p_flag;
    tBTM_INQUIRY_VAR_ST  *p_inq = &btm_cb.btm_inq_vars;
    UINT8                data_len, rssi;
    tBTM_BLE_INQ_CB     *p_le_inq_cb = &btm_cb.ble_ctr_cb.inq_var;
    UINT8 *p1;
    UINT8               *p_uuid16;

    STREAM_TO_UINT8    (data_len, p);

    if (data_len > BTM_BLE_ADV_DATA_LEN_MAX) {
        BTM_TRACE_WARNING("EIR data too long %d. discard", data_len);
        return FALSE;
    }
    btm_ble_cache_adv_data(bda, p_cur, data_len, p, evt_type);

    p1 = (p + data_len);
    STREAM_TO_UINT8 (rssi, p1);

    /* Save the info */
    p_cur->inq_result_type = BTM_INQ_RESULT_BLE;
    p_cur->ble_addr_type    = addr_type;
    p_cur->rssi = rssi;

    /* active scan, always wait until get scan_rsp to report the result */
    if ((btm_cb.ble_ctr_cb.inq_var.scan_type == BTM_BLE_SCAN_MODE_ACTI &&
            (evt_type == BTM_BLE_CONNECT_EVT || evt_type == BTM_BLE_DISCOVER_EVT))) {
        BTM_TRACE_DEBUG("btm_ble_update_inq_result scan_rsp=false, to_report=false,\
                              scan_type_active=%d", btm_cb.ble_ctr_cb.inq_var.scan_type);
        p_i->scan_rsp = FALSE;
#if BTM_BLE_ACTIVE_SCAN_REPORT_ADV_SCAN_RSP_INDIVIDUALLY == FALSE
        to_report = FALSE;
#endif
    } else {
        p_i->scan_rsp = TRUE;
    }

    if (p_i->inq_count != p_inq->inq_counter) {
        p_cur->device_type = BT_DEVICE_TYPE_BLE;
    } else {
        p_cur->device_type |= BT_DEVICE_TYPE_BLE;
    }

    if (evt_type != BTM_BLE_SCAN_RSP_EVT) {
        p_cur->ble_evt_type     = evt_type;
    }

    p_i->inq_count = p_inq->inq_counter;   /* Mark entry for current inquiry */

    if (p_le_inq_cb->adv_len != 0) {
        if ((p_flag = BTM_CheckAdvData(p_le_inq_cb->adv_data_cache, BTM_BLE_AD_TYPE_FLAG, &len)) != NULL) {
            p_cur->flag = * p_flag;
        }
    }

    if (p_le_inq_cb->adv_len != 0) {
        /* Check to see the BLE device has the Appearance UUID in the advertising data.  If it does
         * then try to convert the appearance value to a class of device value Bluedroid can use.
         * Otherwise fall back to trying to infer if it is a HID device based on the service class.
         */
        p_uuid16 = BTM_CheckAdvData(p_le_inq_cb->adv_data_cache, BTM_BLE_AD_TYPE_APPEARANCE, &len);
        if (p_uuid16 && len == 2) {
            btm_ble_appearance_to_cod((UINT16)p_uuid16[0] | (p_uuid16[1] << 8), p_cur->dev_class);
        } else {
            if ((p_uuid16 = BTM_CheckAdvData(p_le_inq_cb->adv_data_cache,
                                             BTM_BLE_AD_TYPE_16SRV_CMPL, &len)) != NULL) {
                UINT8 i;
                for (i = 0; i + 2 <= len; i = i + 2) {
#if BTA_HH_LE_INCLUDED == TRUE
					/* if this BLE device support HID over LE, set HID Major in class of device */
                    if ((p_uuid16[i] | (p_uuid16[i + 1] << 8)) == UUID_SERVCLASS_LE_HID) {
                        p_cur->dev_class[0] = 0;
                        p_cur->dev_class[1] = BTM_COD_MAJOR_PERIPHERAL;
                        p_cur->dev_class[2] = 0;
                        break;
                    }
#endif /* BTA_HH_LE_INCLUDED */
                }
            }
        }
    }

    /* if BR/EDR not supported is not set, assume is a DUMO device */
    if ((p_cur->flag & BTM_BLE_BREDR_NOT_SPT) == 0 &&
            evt_type != BTM_BLE_CONNECT_DIR_EVT) {
        if (p_cur->ble_addr_type != BLE_ADDR_RANDOM) {
            BTM_TRACE_DEBUG("BR/EDR NOT support bit not set, treat as DUMO");
            p_cur->device_type |= BT_DEVICE_TYPE_DUMO;
        } else {
            BTM_TRACE_DEBUG("Random address, treating device as LE only");
        }
    } else {
        BTM_TRACE_DEBUG("BR/EDR NOT SUPPORT bit set, LE only device");
    }

    return to_report;

}