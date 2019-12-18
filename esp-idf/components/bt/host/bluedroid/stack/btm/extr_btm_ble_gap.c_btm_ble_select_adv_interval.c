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
struct TYPE_3__ {scalar_t__ adv_interval_max; scalar_t__ adv_interval_min; } ;
typedef  TYPE_1__ tBTM_BLE_INQ_CB ;
typedef  int UINT8 ;
typedef  scalar_t__ UINT16 ;

/* Variables and functions */
#define  BTM_BLE_CONNECT_DIR_EVT 132 
#define  BTM_BLE_CONNECT_EVT 131 
#define  BTM_BLE_CONNECT_LO_DUTY_DIR_EVT 130 
#define  BTM_BLE_DISCOVER_EVT 129 
 scalar_t__ BTM_BLE_GAP_ADV_DIR_MAX_INT ; 
 scalar_t__ BTM_BLE_GAP_ADV_DIR_MIN_INT ; 
 scalar_t__ BTM_BLE_GAP_ADV_FAST_INT_1 ; 
 scalar_t__ BTM_BLE_GAP_ADV_FAST_INT_2 ; 
 scalar_t__ BTM_BLE_GAP_ADV_SLOW_INT ; 
#define  BTM_BLE_NON_CONNECT_EVT 128 

void btm_ble_select_adv_interval(tBTM_BLE_INQ_CB *p_cb, UINT8 evt_type, UINT16 *p_adv_int_min, UINT16 *p_adv_int_max)
{
    if (p_cb->adv_interval_min && p_cb->adv_interval_max) {
        *p_adv_int_min = p_cb->adv_interval_min;
        *p_adv_int_max = p_cb->adv_interval_max;
    } else {
        switch (evt_type) {
        case BTM_BLE_CONNECT_EVT:
        case BTM_BLE_CONNECT_LO_DUTY_DIR_EVT:
            *p_adv_int_min = *p_adv_int_max = BTM_BLE_GAP_ADV_FAST_INT_1;
            break;

        case BTM_BLE_NON_CONNECT_EVT:
        case BTM_BLE_DISCOVER_EVT:
            *p_adv_int_min = *p_adv_int_max = BTM_BLE_GAP_ADV_FAST_INT_2;
            break;

        /* connectable directed event */
        case BTM_BLE_CONNECT_DIR_EVT:
            *p_adv_int_min = BTM_BLE_GAP_ADV_DIR_MIN_INT;
            *p_adv_int_max = BTM_BLE_GAP_ADV_DIR_MAX_INT;
            break;

        default:
            *p_adv_int_min = *p_adv_int_max = BTM_BLE_GAP_ADV_SLOW_INT;
            break;
        }
    }
    return;
}