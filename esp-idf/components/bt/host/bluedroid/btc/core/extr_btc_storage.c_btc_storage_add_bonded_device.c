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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  bt_status_t ;
typedef  int /*<<< orphan*/  bt_bdaddr_t ;
typedef  int bdstr_t ;
typedef  int /*<<< orphan*/  bdstr ;
typedef  int /*<<< orphan*/  LINK_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_STORAGE_LINK_KEY_STR ; 
 int /*<<< orphan*/  BTC_STORAGE_LINK_KEY_TYPE_STR ; 
 int /*<<< orphan*/  BTC_STORAGE_PIN_LENGTH_STR ; 
 int /*<<< orphan*/  BTC_TRACE_DEBUG (char*,int) ; 
 int /*<<< orphan*/  BT_STATUS_FAIL ; 
 int /*<<< orphan*/  BT_STATUS_SUCCESS ; 
 int /*<<< orphan*/  bdaddr_to_string (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  btc_config_flush () ; 
 int /*<<< orphan*/  btc_config_lock () ; 
 int btc_config_set_bin (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int btc_config_set_int (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  btc_config_unlock () ; 

bt_status_t btc_storage_add_bonded_device(bt_bdaddr_t *remote_bd_addr,
        LINK_KEY link_key,
        uint8_t key_type,
        uint8_t pin_length)
{
    bdstr_t bdstr;

    bdaddr_to_string(remote_bd_addr, bdstr, sizeof(bdstr));
    BTC_TRACE_DEBUG("add to storage: Remote device:%s\n", bdstr);

    btc_config_lock();
    int ret = btc_config_set_int(bdstr, BTC_STORAGE_LINK_KEY_TYPE_STR, (int)key_type);
    ret &= btc_config_set_int(bdstr, BTC_STORAGE_PIN_LENGTH_STR, (int)pin_length);
    ret &= btc_config_set_bin(bdstr, BTC_STORAGE_LINK_KEY_STR, link_key, sizeof(LINK_KEY));
    /* write bonded info immediately */
    btc_config_flush();
    btc_config_unlock();

    BTC_TRACE_DEBUG("Storage add rslt %d\n", ret);
    return ret ? BT_STATUS_SUCCESS : BT_STATUS_FAIL;
}