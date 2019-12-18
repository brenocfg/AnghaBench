#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int in_controller_list; } ;
struct TYPE_8__ {TYPE_1__ ble; } ;
typedef  TYPE_3__ tBTM_SEC_DEV_REC ;
typedef  scalar_t__ UINT8 ;
struct TYPE_7__ {scalar_t__ wl_state; scalar_t__ resolving_list_avail_size; } ;
struct TYPE_10__ {TYPE_3__* sec_dev_rec; TYPE_2__ ble_ctr_cb; } ;
struct TYPE_9__ {scalar_t__ (* get_ble_resolving_list_max_size ) () ;} ;

/* Variables and functions */
 scalar_t__ BTM_BLE_WL_IDLE ; 
 int BTM_RESOLVING_LIST_BIT ; 
 scalar_t__ BTM_SEC_MAX_DEVICE_RECORDS ; 
 int BTM_WHITE_LIST_BIT ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  btm_ble_disable_resolving_list (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btm_ble_enable_resolving_list (scalar_t__) ; 
 TYPE_5__ btm_cb ; 
 TYPE_4__* controller_get_interface () ; 
 scalar_t__ stub1 () ; 
 scalar_t__ stub2 () ; 

void btm_ble_enable_resolving_list_for_platform (UINT8 rl_mask)
{
    /* if controller does not support, skip */
    if (controller_get_interface()->get_ble_resolving_list_max_size() == 0) {
        return;
    }

    if (btm_cb.ble_ctr_cb.wl_state == BTM_BLE_WL_IDLE) {
        if (controller_get_interface()->get_ble_resolving_list_max_size() >
                btm_cb.ble_ctr_cb.resolving_list_avail_size) {
            btm_ble_enable_resolving_list(rl_mask);
        } else {
            btm_ble_disable_resolving_list(rl_mask, TRUE);
        }
        return;
    }

    tBTM_SEC_DEV_REC *p_dev = &btm_cb.sec_dev_rec[0];
    for (UINT8 i = 0; i < BTM_SEC_MAX_DEVICE_RECORDS; i ++, p_dev ++) {
        if ((p_dev->ble.in_controller_list & BTM_RESOLVING_LIST_BIT) &&
                (p_dev->ble.in_controller_list & BTM_WHITE_LIST_BIT)) {
            btm_ble_enable_resolving_list(rl_mask);
            return;
        }
    }
    btm_ble_disable_resolving_list(rl_mask, TRUE);
}