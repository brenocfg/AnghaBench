#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTM_STATUS ;
typedef  scalar_t__ tBTM_BLE_SCAN_COND_OP ;
typedef  int /*<<< orphan*/  tBTM_BLE_PF_FILT_INDEX ;
struct TYPE_3__ {int /*<<< orphan*/  target_addr; } ;
typedef  TYPE_1__ tBTM_BLE_PF_COND_PARAM ;
typedef  int /*<<< orphan*/  tBLE_BD_ADDR ;
typedef  int UINT8 ;

/* Variables and functions */
 scalar_t__ BTM_BLE_INVALID_COUNTER ; 
 int /*<<< orphan*/  BTM_BLE_PF_SRVC_DATA ; 
 scalar_t__ BTM_BLE_SCAN_COND_ADD ; 
 int /*<<< orphan*/  BTM_ILLEGAL_VALUE ; 
 int /*<<< orphan*/  BTM_SUCCESS ; 
 scalar_t__ btm_ble_cs_update_pf_counter (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

tBTM_STATUS btm_ble_update_srvc_data_change(tBTM_BLE_SCAN_COND_OP action,
        tBTM_BLE_PF_FILT_INDEX filt_index,
        tBTM_BLE_PF_COND_PARAM *p_cond)
{
    tBTM_STATUS st = BTM_ILLEGAL_VALUE;
    tBLE_BD_ADDR   *p_bd_addr = p_cond ? &p_cond->target_addr : NULL;
    UINT8           num_avail = (action == BTM_BLE_SCAN_COND_ADD) ? 0 : 1;

    if (btm_ble_cs_update_pf_counter (action, BTM_BLE_PF_SRVC_DATA, p_bd_addr, num_avail)
            != BTM_BLE_INVALID_COUNTER) {
        st = BTM_SUCCESS;
    }

    return st;
}