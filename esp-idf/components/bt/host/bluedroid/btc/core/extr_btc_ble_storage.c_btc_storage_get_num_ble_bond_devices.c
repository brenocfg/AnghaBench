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
typedef  int /*<<< orphan*/  btc_config_section_iter_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_BLE_STORAGE_DEV_TYPE_STR ; 
 int BT_DEVICE_TYPE_BLE ; 
 int /*<<< orphan*/  btc_config_get_int (char const*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  btc_config_lock () ; 
 int /*<<< orphan*/ * btc_config_section_begin () ; 
 int /*<<< orphan*/  const* btc_config_section_end () ; 
 char* btc_config_section_name (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * btc_config_section_next (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  btc_config_unlock () ; 
 int /*<<< orphan*/  string_is_bdaddr (char const*) ; 

int btc_storage_get_num_ble_bond_devices(void)
{
    int num_dev = 0;
    uint32_t device_type = 0;

    btc_config_lock();
    for (const btc_config_section_iter_t *iter = btc_config_section_begin(); iter != btc_config_section_end();
            iter = btc_config_section_next(iter)) {
        const char *name = btc_config_section_name(iter);
        if (!string_is_bdaddr(name) ||
                !btc_config_get_int(name, BTC_BLE_STORAGE_DEV_TYPE_STR, (int *)&device_type) ||
                !(device_type & BT_DEVICE_TYPE_BLE)) {
            continue;
        }

        num_dev++;
    }
    btc_config_unlock();

    return num_dev;
}