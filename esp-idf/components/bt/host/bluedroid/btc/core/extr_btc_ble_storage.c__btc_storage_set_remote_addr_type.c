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
typedef  int /*<<< orphan*/  bdstr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_BLE_STORAGE_ADDR_TYPE_STR ; 
 int /*<<< orphan*/  BT_STATUS_FAIL ; 
 int /*<<< orphan*/  BT_STATUS_SUCCESS ; 
 int /*<<< orphan*/  _btc_storage_save () ; 
 int /*<<< orphan*/  bdaddr_to_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int btc_config_set_int (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bt_status_t _btc_storage_set_remote_addr_type(bt_bdaddr_t *remote_bd_addr, uint8_t addr_type, bool flush)
{
    int ret;
    bdstr_t bdstr;

    bdaddr_to_string(remote_bd_addr, bdstr, sizeof(bdstr_t));
    ret = btc_config_set_int(bdstr, BTC_BLE_STORAGE_ADDR_TYPE_STR, (int)addr_type);
    if (ret == false) {
        return BT_STATUS_FAIL;
    }

    if (flush) {
        _btc_storage_save();
    }

    return BT_STATUS_SUCCESS;
}