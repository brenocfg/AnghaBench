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
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  btc_config_section_iter_t ;
struct TYPE_3__ {int /*<<< orphan*/  address; } ;
typedef  TYPE_1__ bt_bdaddr_t ;

/* Variables and functions */
 scalar_t__ BONED_DEVICES_MAX_COUNT ; 
 int /*<<< orphan*/  BTC_BLE_STORAGE_ADDR_TYPE_STR ; 
 int /*<<< orphan*/  BTC_BLE_STORAGE_DEV_TYPE_STR ; 
 int /*<<< orphan*/  BTC_BLE_STORAGE_LE_KEY_LCSRK_STR ; 
 int /*<<< orphan*/  BTC_BLE_STORAGE_LE_KEY_LENC_STR ; 
 int /*<<< orphan*/  BTC_BLE_STORAGE_LE_KEY_PCSRK_STR ; 
 int /*<<< orphan*/  BTC_BLE_STORAGE_LE_KEY_PENC_STR ; 
 int /*<<< orphan*/  BTC_BLE_STORAGE_LE_KEY_PID_STR ; 
 int /*<<< orphan*/  BTC_BLE_STORAGE_LINK_KEY_STR ; 
 int /*<<< orphan*/  BTIF_TRACE_WARNING (char*,char const*) ; 
 int /*<<< orphan*/  BTM_SecDeleteDevice (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int BT_DEVICE_TYPE_BLE ; 
 int /*<<< orphan*/  BT_TRANSPORT_LE ; 
 int /*<<< orphan*/  btc_config_exist (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btc_config_flush () ; 
 int /*<<< orphan*/  btc_config_get_int (char const*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ btc_config_remove_section (char const*) ; 
 int /*<<< orphan*/ * btc_config_section_begin () ; 
 int /*<<< orphan*/  const* btc_config_section_end () ; 
 char* btc_config_section_name (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * btc_config_section_next (int /*<<< orphan*/  const*) ; 
 scalar_t__ string_is_bdaddr (char const*) ; 
 int /*<<< orphan*/  string_to_bdaddr (char const*,TYPE_1__*) ; 

__attribute__((used)) static void _btc_storage_save(void)
{
    uint16_t addr_section_count = 0;
    bt_bdaddr_t bd_addr;
    uint32_t device_type = 0;
    const btc_config_section_iter_t *need_remove_iter = NULL;
    const btc_config_section_iter_t *iter = btc_config_section_begin();

    while (iter != btc_config_section_end()) {
        //store the next iter, if remove section, then will not loss the point

        const char *section = btc_config_section_name(iter);

        if (string_is_bdaddr(section) &&
                !btc_config_exist(section, BTC_BLE_STORAGE_DEV_TYPE_STR) &&
                !btc_config_exist(section, BTC_BLE_STORAGE_ADDR_TYPE_STR) &&
                !btc_config_exist(section, BTC_BLE_STORAGE_LINK_KEY_STR) &&
                !btc_config_exist(section, BTC_BLE_STORAGE_LE_KEY_PENC_STR) &&
                !btc_config_exist(section, BTC_BLE_STORAGE_LE_KEY_PID_STR) &&
                !btc_config_exist(section, BTC_BLE_STORAGE_LE_KEY_PCSRK_STR) &&
                !btc_config_exist(section, BTC_BLE_STORAGE_LE_KEY_LENC_STR) &&
                !btc_config_exist(section, BTC_BLE_STORAGE_LE_KEY_LCSRK_STR)) {
            iter = btc_config_section_next(iter);
            btc_config_remove_section(section);
            continue;
        }

        if (!string_is_bdaddr(section) ||
            !btc_config_get_int(section, BTC_BLE_STORAGE_DEV_TYPE_STR, (int *)&device_type) ||
            ((device_type & BT_DEVICE_TYPE_BLE) != BT_DEVICE_TYPE_BLE)) {
            iter = btc_config_section_next(iter);
            continue;
        }

        if(addr_section_count == BONED_DEVICES_MAX_COUNT) {
            need_remove_iter = iter;
        }
        addr_section_count ++;
        iter = btc_config_section_next(iter);
    }
    /*exceeded the maximum nubmer of bonded devices, delete them */
    if (need_remove_iter) {
        while(need_remove_iter != btc_config_section_end()) {
            const char *need_remove_section = btc_config_section_name(need_remove_iter);
            if (!string_is_bdaddr(need_remove_section) ||
                !btc_config_get_int(need_remove_section, BTC_BLE_STORAGE_DEV_TYPE_STR, (int *)&device_type) ||
                ((device_type & BT_DEVICE_TYPE_BLE) != BT_DEVICE_TYPE_BLE)) {
                need_remove_iter = btc_config_section_next(need_remove_iter);
                continue;
            }
            need_remove_iter = btc_config_section_next(need_remove_iter);
            //delete device info
            string_to_bdaddr(need_remove_section, &bd_addr);
            BTM_SecDeleteDevice(bd_addr.address, BT_TRANSPORT_LE);
            //delet config info
            if(btc_config_remove_section(need_remove_section)) {
                BTIF_TRACE_WARNING("exceeded the maximum nubmer of bonded devices, delete the last device info : %s", need_remove_section);
            }
        }
    }
    btc_config_flush();
}