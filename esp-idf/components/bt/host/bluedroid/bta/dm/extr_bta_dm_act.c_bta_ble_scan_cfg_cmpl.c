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
typedef  scalar_t__ tBTM_STATUS ;
typedef  int /*<<< orphan*/  tBTM_BLE_SCAN_COND_OP ;
typedef  int /*<<< orphan*/  tBTM_BLE_REF_VALUE ;
typedef  int /*<<< orphan*/  tBTM_BLE_PF_AVBL_SPACE ;
typedef  int /*<<< orphan*/  tBTM_BLE_PF_ACTION ;
typedef  int /*<<< orphan*/  tBTA_STATUS ;
struct TYPE_2__ {int /*<<< orphan*/  (* p_scan_filt_cfg_cback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  BTA_FAILURE ; 
 int /*<<< orphan*/  BTA_SUCCESS ; 
 scalar_t__ BTM_SUCCESS ; 
 TYPE_1__ bta_dm_cb ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bta_ble_scan_cfg_cmpl(tBTM_BLE_PF_ACTION action, tBTM_BLE_SCAN_COND_OP cfg_op,
                                  tBTM_BLE_PF_AVBL_SPACE avbl_space, tBTM_STATUS status,
                                  tBTM_BLE_REF_VALUE ref_value)
{
    tBTA_STATUS st = (status == BTM_SUCCESS) ? BTA_SUCCESS : BTA_FAILURE;

    APPL_TRACE_DEBUG("bta_ble_scan_cfg_cmpl: %d, %d, %d, %d", action, cfg_op, avbl_space, status);

    if (bta_dm_cb.p_scan_filt_cfg_cback) {
        bta_dm_cb.p_scan_filt_cfg_cback(action, cfg_op, avbl_space, st, ref_value);
    }
}