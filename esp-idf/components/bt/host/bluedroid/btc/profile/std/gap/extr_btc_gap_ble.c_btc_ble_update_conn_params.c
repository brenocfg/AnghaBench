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
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_DmBleUpdateConnectionParams (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  BTC_TRACE_ERROR (char*) ; 
 scalar_t__ BTM_BLE_CONN_INT_MAX ; 
 scalar_t__ BTM_BLE_CONN_INT_MIN ; 

__attribute__((used)) static void btc_ble_update_conn_params(BD_ADDR bd_addr, uint16_t min_int,
                                       uint16_t max_int, uint16_t latency, uint16_t timeout)
{
    if (min_int > max_int) {
        min_int = max_int;
    }

    if (min_int < BTM_BLE_CONN_INT_MIN || max_int > BTM_BLE_CONN_INT_MAX) {
        BTC_TRACE_ERROR("Invalid interval value.\n");
    }

    BTA_DmBleUpdateConnectionParams(bd_addr, min_int, max_int,
                                    latency, timeout);
}