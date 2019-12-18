#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t adv_data_len; size_t scan_rsp_len; } ;
typedef  TYPE_2__ tBTM_INQ_RESULTS ;
struct TYPE_8__ {size_t adv_len; scalar_t__* adv_data_cache; scalar_t__* adv_addr; } ;
typedef  TYPE_3__ tBTM_BLE_INQ_CB ;
typedef  scalar_t__ UINT8 ;
struct TYPE_6__ {TYPE_3__ inq_var; } ;
struct TYPE_9__ {TYPE_1__ ble_ctr_cb; } ;
typedef  scalar_t__* BD_ADDR ;

/* Variables and functions */
 scalar_t__ BD_ADDR_LEN ; 
 scalar_t__ BTM_BLE_CACHE_ADV_DATA_MAX ; 
 scalar_t__ BTM_BLE_SCAN_RSP_EVT ; 
 int /*<<< orphan*/  STREAM_TO_UINT8 (scalar_t__,scalar_t__*) ; 
 TYPE_4__ btm_cb ; 
 scalar_t__ memcmp (scalar_t__*,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,scalar_t__) ; 

void btm_ble_cache_adv_data(BD_ADDR bda, tBTM_INQ_RESULTS *p_cur, UINT8 data_len, UINT8 *p, UINT8 evt_type)
{
    tBTM_BLE_INQ_CB     *p_le_inq_cb = &btm_cb.ble_ctr_cb.inq_var;
    UINT8 *p_cache;
    UINT8 length;

    /* cache adv report/scan response data */
    if (evt_type != BTM_BLE_SCAN_RSP_EVT) {
        p_le_inq_cb->adv_len = 0;
        memset(p_le_inq_cb->adv_data_cache, 0, BTM_BLE_CACHE_ADV_DATA_MAX);
        p_cur->adv_data_len = 0;
        p_cur->scan_rsp_len = 0;
    }

    //Clear the adv cache if the addresses are not equal
    if(memcmp(bda, p_le_inq_cb->adv_addr, BD_ADDR_LEN) != 0) {
        p_le_inq_cb->adv_len = 0;
        memcpy(p_le_inq_cb->adv_addr, bda, BD_ADDR_LEN);
        memset(p_le_inq_cb->adv_data_cache, 0, BTM_BLE_CACHE_ADV_DATA_MAX);
        p_cur->adv_data_len = 0;
        p_cur->scan_rsp_len = 0;
    }

    if (data_len > 0) {
        p_cache = &p_le_inq_cb->adv_data_cache[p_le_inq_cb->adv_len];
        STREAM_TO_UINT8(length, p);
        while ( length && ((p_le_inq_cb->adv_len + length + 1) <= BTM_BLE_CACHE_ADV_DATA_MAX)) {
            /* copy from the length byte & data into cache */
            memcpy(p_cache, p - 1, length + 1);
            /* advance the cache pointer past data */
            p_cache += length + 1;
            /* increment cache length */
            p_le_inq_cb->adv_len += length + 1;
            /* skip the length of data */
            p += length;
            STREAM_TO_UINT8(length, p);
        }
    }

    if (evt_type != BTM_BLE_SCAN_RSP_EVT) {
        p_cur->adv_data_len = p_le_inq_cb->adv_len;
    }
    else {
        p_cur->scan_rsp_len = p_le_inq_cb->adv_len - p_cur->adv_data_len;
    }

    /* parse service UUID from adv packet and save it in inq db eir_uuid */
    /* TODO */
}