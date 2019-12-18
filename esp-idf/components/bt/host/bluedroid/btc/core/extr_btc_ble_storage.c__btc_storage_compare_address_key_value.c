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
 int /*<<< orphan*/  bdaddr_to_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int btc_compare_address_key_value (int /*<<< orphan*/ ,char const*,void*,int) ; 

bool _btc_storage_compare_address_key_value(bt_bdaddr_t *remote_bd_addr,
                                                   uint8_t key_type, void *key_value, int key_length)
{
    bdstr_t bdstr;
    bdaddr_to_string(remote_bd_addr, bdstr, sizeof(bdstr));
    const char *key_type_str;
    switch (key_type) {
    case BTM_LE_KEY_PENC:
        key_type_str = BTC_BLE_STORAGE_LE_KEY_PENC_STR;
        break;
    case BTM_LE_KEY_PID:
        key_type_str = BTC_BLE_STORAGE_LE_KEY_PID_STR;
        break;
    case BTM_LE_KEY_PCSRK:
        key_type_str = BTC_BLE_STORAGE_LE_KEY_PCSRK_STR;
        break;
    case BTM_LE_KEY_LENC:
        key_type_str = BTC_BLE_STORAGE_LE_KEY_LENC_STR;
        break;
    case BTM_LE_KEY_LCSRK:
        key_type_str = BTC_BLE_STORAGE_LE_KEY_LCSRK_STR;
        break;
    case BTM_LE_KEY_LID:
        key_type_str =  BTC_BLE_STORAGE_LE_KEY_LID_STR;
    default:
        return false;
    }

    return btc_compare_address_key_value(bdstr, key_type_str, key_value, key_length);
}