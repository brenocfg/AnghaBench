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
typedef  int /*<<< orphan*/  tBTA_SET_PKT_DATA_LENGTH_CBACK ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_DmBleSetDataLength (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ BTM_BLE_DATA_SIZE_MAX ; 
 scalar_t__ BTM_BLE_DATA_SIZE_MIN ; 

__attribute__((used)) static void btc_ble_set_pkt_data_len(BD_ADDR remote_device, uint16_t tx_data_length, tBTA_SET_PKT_DATA_LENGTH_CBACK *p_set_pkt_data_cback)
{
    if (tx_data_length > BTM_BLE_DATA_SIZE_MAX) {
        tx_data_length =  BTM_BLE_DATA_SIZE_MAX;
    } else if (tx_data_length < BTM_BLE_DATA_SIZE_MIN) {
        tx_data_length =  BTM_BLE_DATA_SIZE_MIN;
    }

    BTA_DmBleSetDataLength(remote_device, tx_data_length, p_set_pkt_data_cback);
}