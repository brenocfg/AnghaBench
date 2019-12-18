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
typedef  int /*<<< orphan*/  btc_config_section_iter_t ;
typedef  int /*<<< orphan*/  bt_status_t ;
typedef  int /*<<< orphan*/  bt_bdaddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_STORAGE_LINK_KEY_STR ; 
 int /*<<< orphan*/  BTC_STORAGE_LINK_KEY_TYPE_STR ; 
 int /*<<< orphan*/  BTC_STORAGE_PIN_LENGTH_STR ; 
 int /*<<< orphan*/  BT_STATUS_SUCCESS ; 
 scalar_t__ btc_config_exist (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btc_config_lock () ; 
 int /*<<< orphan*/ * btc_config_section_begin () ; 
 int /*<<< orphan*/  const* btc_config_section_end () ; 
 char* btc_config_section_name (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * btc_config_section_next (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  btc_config_unlock () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ string_is_bdaddr (char const*) ; 
 int /*<<< orphan*/  string_to_bdaddr (char const*,int /*<<< orphan*/ *) ; 

bt_status_t btc_storage_get_bonded_bt_devices_list(bt_bdaddr_t *bond_dev, int dev_num)
{
    bt_bdaddr_t bd_addr;

    btc_config_lock();
    for (const btc_config_section_iter_t *iter = btc_config_section_begin(); iter != btc_config_section_end();
            iter = btc_config_section_next(iter)) {

        if (dev_num-- <= 0) {
            break;
        }

        const char *name = btc_config_section_name(iter);

        if (string_is_bdaddr(name) &&
            btc_config_exist(name, BTC_STORAGE_LINK_KEY_TYPE_STR) &&
            btc_config_exist(name, BTC_STORAGE_PIN_LENGTH_STR) &&
            btc_config_exist(name, BTC_STORAGE_LINK_KEY_STR)) {
            string_to_bdaddr(name, &bd_addr);
            memcpy(bond_dev, &bd_addr, sizeof(bt_bdaddr_t));
            bond_dev++;
        }
    }
    btc_config_unlock();

    return BT_STATUS_SUCCESS;
}