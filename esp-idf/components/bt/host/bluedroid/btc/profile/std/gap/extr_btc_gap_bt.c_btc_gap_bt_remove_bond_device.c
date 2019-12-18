#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_5__ {int /*<<< orphan*/  address; } ;
struct TYPE_6__ {TYPE_1__ bda; } ;
struct TYPE_7__ {TYPE_2__ rm_bond_device; } ;
typedef  TYPE_3__ btc_gap_bt_args_t ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 scalar_t__ BTA_DmRemoveDevice (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ BTA_SUCCESS ; 
 int /*<<< orphan*/  BT_TRANSPORT_BR_EDR ; 
 int /*<<< orphan*/  ESP_BT_STATUS_FAIL ; 
 int /*<<< orphan*/  ESP_BT_STATUS_SUCCESS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static esp_err_t btc_gap_bt_remove_bond_device(btc_gap_bt_args_t *arg)
{
    BD_ADDR bd_addr;
    memcpy(bd_addr, arg->rm_bond_device.bda.address, sizeof(BD_ADDR));
    if(BTA_DmRemoveDevice(bd_addr, BT_TRANSPORT_BR_EDR) == BTA_SUCCESS){
        return ESP_BT_STATUS_SUCCESS;
    }
    return ESP_BT_STATUS_FAIL;
}