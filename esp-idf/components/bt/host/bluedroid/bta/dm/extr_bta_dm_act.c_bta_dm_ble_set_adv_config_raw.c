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
typedef  int /*<<< orphan*/  tBTA_STATUS ;
struct TYPE_4__ {int /*<<< orphan*/  (* p_adv_data_cback ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  raw_adv_len; int /*<<< orphan*/  p_raw_adv; } ;
struct TYPE_5__ {TYPE_1__ ble_set_adv_data_raw; } ;
typedef  TYPE_2__ tBTA_DM_MSG ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_FAILURE ; 
 int /*<<< orphan*/  BTA_SUCCESS ; 
 scalar_t__ BTM_BleWriteAdvDataRaw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ BTM_SUCCESS ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void bta_dm_ble_set_adv_config_raw (tBTA_DM_MSG *p_data)
{
    tBTA_STATUS status = BTA_FAILURE;

    if (BTM_BleWriteAdvDataRaw(p_data->ble_set_adv_data_raw.p_raw_adv,
                               p_data->ble_set_adv_data_raw.raw_adv_len) == BTM_SUCCESS) {
        status = BTA_SUCCESS;
    }

    if (p_data->ble_set_adv_data_raw.p_adv_data_cback) {
        (*p_data->ble_set_adv_data_raw.p_adv_data_cback)(status);
    }
}