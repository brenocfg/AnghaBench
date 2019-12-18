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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  bt_status_t ;
typedef  int /*<<< orphan*/  bt_bdaddr_t ;
typedef  int /*<<< orphan*/  bdstr_t ;
typedef  int /*<<< orphan*/  bdstr ;

/* Variables and functions */
 char* BTC_BLE_STORAGE_LE_KEY_LCSRK_STR ; 
 char* BTC_BLE_STORAGE_LE_KEY_LENC_STR ; 
 char* BTC_BLE_STORAGE_LE_KEY_LID_STR ; 
 char* BTC_BLE_STORAGE_LE_KEY_PCSRK_STR ; 
 char* BTC_BLE_STORAGE_LE_KEY_PENC_STR ; 
 char* BTC_BLE_STORAGE_LE_KEY_PID_STR ; 
#define  BTM_LE_KEY_LCSRK 133 
#define  BTM_LE_KEY_LENC 132 
#define  BTM_LE_KEY_LID 131 
#define  BTM_LE_KEY_PCSRK 130 
#define  BTM_LE_KEY_PENC 129 
#define  BTM_LE_KEY_PID 128 
 int /*<<< orphan*/  BT_STATUS_FAIL ; 
 int /*<<< orphan*/  BT_STATUS_SUCCESS ; 
 int /*<<< orphan*/  bdaddr_to_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int btc_config_get_bin (int /*<<< orphan*/ ,char const*,int*,size_t*) ; 

__attribute__((used)) static bt_status_t _btc_storage_get_ble_bonding_key(bt_bdaddr_t *remote_bd_addr,
                                            uint8_t key_type,
                                            char *key_value,
                                            int key_length)
{
    bdstr_t bdstr;
    bdaddr_to_string(remote_bd_addr, bdstr, sizeof(bdstr));
    const char* name;
    switch (key_type) {
    case BTM_LE_KEY_PENC:
        name = BTC_BLE_STORAGE_LE_KEY_PENC_STR;
        break;
    case BTM_LE_KEY_PID:
        name = BTC_BLE_STORAGE_LE_KEY_PID_STR;
        break;
    case BTM_LE_KEY_PCSRK:
        name = BTC_BLE_STORAGE_LE_KEY_PCSRK_STR;
        break;
    case BTM_LE_KEY_LENC:
        name = BTC_BLE_STORAGE_LE_KEY_LENC_STR;
        break;
    case BTM_LE_KEY_LCSRK:
        name = BTC_BLE_STORAGE_LE_KEY_LCSRK_STR;
        break;
    case BTM_LE_KEY_LID:
        name =  BTC_BLE_STORAGE_LE_KEY_LID_STR;
    default:
        return BT_STATUS_FAIL;
    }
    size_t length = key_length;
    int ret = btc_config_get_bin(bdstr, name, (uint8_t *)key_value, &length);
    return ret ? BT_STATUS_SUCCESS : BT_STATUS_FAIL;

}