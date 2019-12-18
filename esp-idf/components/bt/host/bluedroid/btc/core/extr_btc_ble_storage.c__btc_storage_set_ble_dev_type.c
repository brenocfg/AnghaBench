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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  bt_status_t ;
typedef  int /*<<< orphan*/  bt_bdaddr_t ;
typedef  int /*<<< orphan*/  bdstr_t ;
typedef  int /*<<< orphan*/  bdstr ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_BLE_STORAGE_DEV_TYPE_STR ; 
 int BT_DEVICE_TYPE_BLE ; 
 int /*<<< orphan*/  BT_STATUS_FAIL ; 
 int /*<<< orphan*/  BT_STATUS_SUCCESS ; 
 int /*<<< orphan*/  _btc_storage_save () ; 
 int /*<<< orphan*/  bdaddr_to_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  btc_config_get_int (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int btc_config_set_int (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bt_status_t _btc_storage_set_ble_dev_type(bt_bdaddr_t *bd_addr, bool flush)
{
    bool ret = 1;
    bdstr_t bdstr;
    uint32_t dev_type = 0;

    bdaddr_to_string(bd_addr, bdstr, sizeof(bdstr));

    btc_config_get_int(bdstr, BTC_BLE_STORAGE_DEV_TYPE_STR, (int *)&dev_type);
    ret = btc_config_set_int(bdstr, BTC_BLE_STORAGE_DEV_TYPE_STR, BT_DEVICE_TYPE_BLE|dev_type);
    if (ret == false) {
        return BT_STATUS_FAIL;
    }

    if (flush) {
        _btc_storage_save();
    }

    return BT_STATUS_SUCCESS;
}