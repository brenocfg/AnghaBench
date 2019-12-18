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
typedef  int tBTM_BLE_BATCH_SCAN_EVT ;
typedef  int /*<<< orphan*/  tBTA_BLE_BATCH_SCAN_EVT ;
struct TYPE_2__ {int /*<<< orphan*/  (* p_setup_cback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTA_BLE_BATCH_SCAN_CFG_STRG_EVT ; 
 int /*<<< orphan*/  BTA_BLE_BATCH_SCAN_DIS_EVT ; 
 int /*<<< orphan*/  BTA_BLE_BATCH_SCAN_ENB_EVT ; 
 int /*<<< orphan*/  BTA_BLE_BATCH_SCAN_PARAM_EVT ; 
#define  BTM_BLE_BATCH_SCAN_CFG_STRG_EVT 131 
#define  BTM_BLE_BATCH_SCAN_DISABLE_EVT 130 
#define  BTM_BLE_BATCH_SCAN_ENABLE_EVT 129 
#define  BTM_BLE_BATCH_SCAN_PARAM_EVT 128 
 TYPE_1__ bta_dm_cb ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void bta_ble_scan_setup_cb(tBTM_BLE_BATCH_SCAN_EVT evt, tBTM_BLE_REF_VALUE ref_value,
                           tBTM_STATUS status)
{
    tBTA_BLE_BATCH_SCAN_EVT bta_evt = 0;

    APPL_TRACE_DEBUG("bta_ble_scan_setup_cb : evt: %d, ref_value: %d, status:%d", evt,
                     ref_value, status);

    switch (evt) {
    case BTM_BLE_BATCH_SCAN_ENABLE_EVT:
        bta_evt = BTA_BLE_BATCH_SCAN_ENB_EVT;
        break;
    case BTM_BLE_BATCH_SCAN_CFG_STRG_EVT:
        bta_evt = BTA_BLE_BATCH_SCAN_CFG_STRG_EVT;
        break;
    case BTM_BLE_BATCH_SCAN_DISABLE_EVT:
        bta_evt = BTA_BLE_BATCH_SCAN_DIS_EVT;
        break;
    case BTM_BLE_BATCH_SCAN_PARAM_EVT:
        bta_evt = BTA_BLE_BATCH_SCAN_PARAM_EVT;
        break;
    default:
        break;
    }

    if (NULL != bta_dm_cb.p_setup_cback) {
        bta_dm_cb.p_setup_cback(bta_evt, ref_value, status);
    }
}