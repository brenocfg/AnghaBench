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
typedef  int UINT8 ;
typedef  int UINT16 ;
struct TYPE_2__ {scalar_t__ (* supports_simultaneous_le_bredr ) () ;} ;

/* Variables and functions */
 int BTM_BLE_BREDR_NOT_SPT ; 
 int BTM_BLE_DMT_CONTROLLER_SPT ; 
 int BTM_BLE_DMT_HOST_SPT ; 
 int const BTM_CONNECTABLE_MASK ; 
 int const BTM_DISCOVERABLE_MASK ; 
 TYPE_1__* controller_get_interface () ; 
 scalar_t__ stub1 () ; 

void btm_ble_update_dmt_flag_bits(UINT8 *adv_flag_value, const UINT16 connect_mode,
                                  const UINT16 disc_mode)
{
    /* BR/EDR non-discoverable , non-connectable */
    if ((disc_mode & BTM_DISCOVERABLE_MASK) == 0 &&
            (connect_mode & BTM_CONNECTABLE_MASK) == 0) {
        *adv_flag_value |= BTM_BLE_BREDR_NOT_SPT;
    } else {
        *adv_flag_value &= ~BTM_BLE_BREDR_NOT_SPT;
    }

    /* if local controller support, mark both controller and host support in flag */
    if (controller_get_interface()->supports_simultaneous_le_bredr()) {
        *adv_flag_value |= (BTM_BLE_DMT_CONTROLLER_SPT | BTM_BLE_DMT_HOST_SPT);
    } else {
        *adv_flag_value &= ~(BTM_BLE_DMT_CONTROLLER_SPT | BTM_BLE_DMT_HOST_SPT);
    }
}