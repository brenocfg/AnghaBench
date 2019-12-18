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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  bt_bdaddr_t ;

/* Variables and functions */
 int _btc_storage_compare_address_key_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  btc_config_lock () ; 
 int /*<<< orphan*/  btc_config_unlock () ; 

bool btc_storage_compare_address_key_value(bt_bdaddr_t *remote_bd_addr,
                                                   uint8_t key_type, void *key_value, int key_length)
{
    bool ret;

    btc_config_lock();
    ret = _btc_storage_compare_address_key_value(remote_bd_addr, key_type, key_value, key_length);
    btc_config_unlock();

    return ret;
}