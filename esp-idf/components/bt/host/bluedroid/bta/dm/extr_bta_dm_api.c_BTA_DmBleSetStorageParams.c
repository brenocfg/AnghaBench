#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTA_DM_BLE_REF_VALUE ;
struct TYPE_5__ {int /*<<< orphan*/  event; } ;
struct TYPE_6__ {void* batch_scan_notify_threshold; void* batch_scan_trunc_max; void* batch_scan_full_max; int /*<<< orphan*/  ref_value; int /*<<< orphan*/ * p_read_rep_cback; int /*<<< orphan*/ * p_thres_cback; int /*<<< orphan*/  p_setup_cback; TYPE_1__ hdr; } ;
typedef  TYPE_2__ tBTA_DM_API_SET_STORAGE_CONFIG ;
typedef  int /*<<< orphan*/  tBTA_BLE_SCAN_THRESHOLD_CBACK ;
typedef  int /*<<< orphan*/  tBTA_BLE_SCAN_SETUP_CBACK ;
typedef  int /*<<< orphan*/  tBTA_BLE_SCAN_REP_CBACK ;
typedef  void* UINT8 ;
struct TYPE_7__ {int /*<<< orphan*/ * p_setup_cback; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_DM_API_BLE_SETUP_STORAGE_EVT ; 
 int /*<<< orphan*/  bta_ble_scan_setup_cb ; 
 TYPE_4__ bta_dm_cb ; 
 int /*<<< orphan*/  bta_sys_sendmsg (TYPE_2__*) ; 
 scalar_t__ osi_malloc (int) ; 

extern void BTA_DmBleSetStorageParams(UINT8 batch_scan_full_max,
                                      UINT8 batch_scan_trunc_max,
                                      UINT8 batch_scan_notify_threshold,
                                      tBTA_BLE_SCAN_SETUP_CBACK *p_setup_cback,
                                      tBTA_BLE_SCAN_THRESHOLD_CBACK *p_thres_cback,
                                      tBTA_BLE_SCAN_REP_CBACK *p_rep_cback,
                                      tBTA_DM_BLE_REF_VALUE ref_value)
{
    tBTA_DM_API_SET_STORAGE_CONFIG  *p_msg;
    bta_dm_cb.p_setup_cback = p_setup_cback;
    if ((p_msg = (tBTA_DM_API_SET_STORAGE_CONFIG *)
                 osi_malloc(sizeof(tBTA_DM_API_SET_STORAGE_CONFIG))) != NULL) {
        p_msg->hdr.event = BTA_DM_API_BLE_SETUP_STORAGE_EVT;
        p_msg->p_setup_cback = bta_ble_scan_setup_cb;
        p_msg->p_thres_cback = p_thres_cback;
        p_msg->p_read_rep_cback = p_rep_cback;
        p_msg->ref_value = ref_value;
        p_msg->batch_scan_full_max = batch_scan_full_max;
        p_msg->batch_scan_trunc_max = batch_scan_trunc_max;
        p_msg->batch_scan_notify_threshold = batch_scan_notify_threshold;
        bta_sys_sendmsg(p_msg);
    }
}