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
typedef  int bt_status_t ;
typedef  int /*<<< orphan*/  bt_bdaddr_t ;

/* Variables and functions */
 int _btc_storage_get_ble_dev_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btc_config_lock () ; 
 int /*<<< orphan*/  btc_config_unlock () ; 

bool btc_storage_get_ble_dev_type(bt_bdaddr_t *bd_addr)
{
    bt_status_t ret;

    btc_config_lock();
    ret = _btc_storage_get_ble_dev_type(bd_addr);
    btc_config_unlock();

    return ret;
}