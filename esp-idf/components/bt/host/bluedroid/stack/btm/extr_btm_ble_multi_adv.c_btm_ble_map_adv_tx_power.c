#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int BTM_BLE_ADV_TX_POWER_MAX ; 
 scalar_t__* btm_ble_tx_power ; 

char btm_ble_map_adv_tx_power(int tx_power_index)
{
    if (0 <= tx_power_index && tx_power_index <= BTM_BLE_ADV_TX_POWER_MAX) {
        return (char)btm_ble_tx_power[tx_power_index];
    }
    return 0;
}