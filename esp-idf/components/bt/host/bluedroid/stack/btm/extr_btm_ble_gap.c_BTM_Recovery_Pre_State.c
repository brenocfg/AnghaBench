#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ state; } ;
typedef  TYPE_2__ tBTM_BLE_INQ_CB ;
struct TYPE_4__ {TYPE_2__ inq_var; } ;
struct TYPE_6__ {TYPE_1__ ble_ctr_cb; } ;

/* Variables and functions */
 scalar_t__ BTM_BLE_ADVERTISING ; 
 scalar_t__ BTM_BLE_SCANNING ; 
 int /*<<< orphan*/  btm_ble_start_adv () ; 
 int /*<<< orphan*/  btm_ble_start_scan () ; 
 int /*<<< orphan*/  btm_ble_stop_adv () ; 
 TYPE_3__ btm_cb ; 

void BTM_Recovery_Pre_State(void)
{
    tBTM_BLE_INQ_CB *ble_inq_cb = &btm_cb.ble_ctr_cb.inq_var;

    if (ble_inq_cb->state == BTM_BLE_ADVERTISING) {
        btm_ble_stop_adv();
        btm_ble_start_adv();
    } else if (ble_inq_cb->state == BTM_BLE_SCANNING) {
        btm_ble_start_scan();
    }

    return;
}