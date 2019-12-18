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
typedef  int /*<<< orphan*/  bt_bdaddr_t ;
typedef  int /*<<< orphan*/  bdstr_t ;
typedef  int /*<<< orphan*/  bdstr ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_STORAGE_LINK_KEY_STR ; 
 int /*<<< orphan*/  BTC_STORAGE_LINK_KEY_TYPE_STR ; 
 int /*<<< orphan*/  BTC_STORAGE_PIN_LENGTH_STR ; 
 int /*<<< orphan*/  BTC_TRACE_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BT_STATUS_FAIL ; 
 int /*<<< orphan*/  BT_STATUS_SUCCESS ; 
 int /*<<< orphan*/  bdaddr_to_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ btc_config_exist (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btc_config_flush () ; 
 int /*<<< orphan*/  btc_config_lock () ; 
 int btc_config_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btc_config_unlock () ; 

bt_status_t btc_storage_remove_bonded_device(bt_bdaddr_t *remote_bd_addr)
{
    bdstr_t bdstr;
    bdaddr_to_string(remote_bd_addr, bdstr, sizeof(bdstr));
    int ret = 1;
    BTC_TRACE_DEBUG("Add to storage: Remote device:%s\n", bdstr);

    btc_config_lock();
    if (btc_config_exist(bdstr, BTC_STORAGE_LINK_KEY_TYPE_STR)) {
        ret &= btc_config_remove(bdstr, BTC_STORAGE_LINK_KEY_TYPE_STR);
    }
    if (btc_config_exist(bdstr, BTC_STORAGE_PIN_LENGTH_STR)) {
        ret &= btc_config_remove(bdstr, BTC_STORAGE_PIN_LENGTH_STR);
    }
    if (btc_config_exist(bdstr, BTC_STORAGE_LINK_KEY_STR)) {
        ret &= btc_config_remove(bdstr, BTC_STORAGE_LINK_KEY_STR);
    }
    /* write bonded info immediately */
    btc_config_flush();
    btc_config_unlock();

    return ret ? BT_STATUS_SUCCESS : BT_STATUS_FAIL;
}