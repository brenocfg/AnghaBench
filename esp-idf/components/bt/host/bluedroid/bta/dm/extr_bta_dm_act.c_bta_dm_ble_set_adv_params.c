#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  p_dir_bda; int /*<<< orphan*/  adv_int_max; int /*<<< orphan*/  adv_int_min; } ;
struct TYPE_5__ {TYPE_1__ ble_set_adv_params; } ;
typedef  TYPE_2__ tBTA_DM_MSG ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_DM_BLE_ADV_CHNL_MAP ; 
 int /*<<< orphan*/  BTM_BleSetAdvParams (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void bta_dm_ble_set_adv_params (tBTA_DM_MSG *p_data)
{
    BTM_BleSetAdvParams(p_data->ble_set_adv_params.adv_int_min,
                        p_data->ble_set_adv_params.adv_int_max,
                        p_data->ble_set_adv_params.p_dir_bda,
                        BTA_DM_BLE_ADV_CHNL_MAP);
}