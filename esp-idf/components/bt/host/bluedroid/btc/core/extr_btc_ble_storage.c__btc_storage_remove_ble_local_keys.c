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
typedef  int /*<<< orphan*/  bt_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_BLE_STORAGE_LE_LOCAL_KEY_DHK_STR ; 
 int /*<<< orphan*/  BTC_BLE_STORAGE_LE_LOCAL_KEY_ER_STR ; 
 int /*<<< orphan*/  BTC_BLE_STORAGE_LE_LOCAL_KEY_IRK_STR ; 
 int /*<<< orphan*/  BTC_BLE_STORAGE_LE_LOCAL_KEY_IR_STR ; 
 int /*<<< orphan*/  BTC_BLE_STORAGE_LOCAL_ADAPTER_STR ; 
 int /*<<< orphan*/  BT_STATUS_FAIL ; 
 int /*<<< orphan*/  BT_STATUS_SUCCESS ; 
 int /*<<< orphan*/  _btc_storage_save () ; 
 scalar_t__ btc_config_exist (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int btc_config_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bt_status_t _btc_storage_remove_ble_local_keys(void)
{
    int ret = 1;

    if (btc_config_exist(BTC_BLE_STORAGE_LOCAL_ADAPTER_STR, BTC_BLE_STORAGE_LE_LOCAL_KEY_IR_STR)) {
        ret &= btc_config_remove(BTC_BLE_STORAGE_LOCAL_ADAPTER_STR, BTC_BLE_STORAGE_LE_LOCAL_KEY_IR_STR);
    }
    if (btc_config_exist(BTC_BLE_STORAGE_LOCAL_ADAPTER_STR, BTC_BLE_STORAGE_LE_LOCAL_KEY_IRK_STR)) {
        ret &= btc_config_remove(BTC_BLE_STORAGE_LOCAL_ADAPTER_STR, BTC_BLE_STORAGE_LE_LOCAL_KEY_IRK_STR);
    }
    if (btc_config_exist(BTC_BLE_STORAGE_LOCAL_ADAPTER_STR, BTC_BLE_STORAGE_LE_LOCAL_KEY_DHK_STR)) {
        ret &= btc_config_remove(BTC_BLE_STORAGE_LOCAL_ADAPTER_STR, BTC_BLE_STORAGE_LE_LOCAL_KEY_DHK_STR);
    }
    if (btc_config_exist(BTC_BLE_STORAGE_LOCAL_ADAPTER_STR, BTC_BLE_STORAGE_LE_LOCAL_KEY_ER_STR)) {
        ret &= btc_config_remove(BTC_BLE_STORAGE_LOCAL_ADAPTER_STR, BTC_BLE_STORAGE_LE_LOCAL_KEY_ER_STR);
    }
    _btc_storage_save();

    return ret ? BT_STATUS_SUCCESS : BT_STATUS_FAIL;
}