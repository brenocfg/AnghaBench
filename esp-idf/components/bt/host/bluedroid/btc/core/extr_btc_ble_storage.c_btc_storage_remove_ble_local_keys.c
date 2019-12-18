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
 int /*<<< orphan*/  _btc_storage_remove_ble_local_keys () ; 
 int /*<<< orphan*/  btc_config_lock () ; 
 int /*<<< orphan*/  btc_config_unlock () ; 

bt_status_t btc_storage_remove_ble_local_keys(void)
{
    bt_status_t ret;

    btc_config_lock();
    ret = _btc_storage_remove_ble_local_keys();
    btc_config_unlock();

    return ret;
}