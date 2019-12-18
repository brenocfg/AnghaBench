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
 int /*<<< orphan*/  BTC_BLE_STORAGE_ADDR_TYPE_STR ; 
 int /*<<< orphan*/  BT_STATUS_FAIL ; 
 int /*<<< orphan*/  BT_STATUS_SUCCESS ; 
 int /*<<< orphan*/  bdaddr_to_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int btc_config_get_int (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static bt_status_t _btc_storage_get_remote_addr_type(bt_bdaddr_t *remote_bd_addr,
                                             int*addr_type)
{
    bdstr_t bdstr;
    bdaddr_to_string(remote_bd_addr, bdstr, sizeof(bdstr));
    int ret = btc_config_get_int(bdstr, BTC_BLE_STORAGE_ADDR_TYPE_STR, addr_type);
    return ret ? BT_STATUS_SUCCESS : BT_STATUS_FAIL;
}