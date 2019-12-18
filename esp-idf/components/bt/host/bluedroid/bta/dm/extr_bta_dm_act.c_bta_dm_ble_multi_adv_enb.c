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
typedef  scalar_t__ tBTM_STATUS ;
typedef  int /*<<< orphan*/  tBTM_BLE_ADV_PARAMS ;
struct TYPE_5__ {int /*<<< orphan*/ * p_ref; int /*<<< orphan*/  (* p_cback ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;scalar_t__ p_params; } ;
struct TYPE_6__ {TYPE_1__ ble_multi_adv_enb; } ;
typedef  TYPE_2__ tBTA_DM_MSG ;
struct TYPE_7__ {int /*<<< orphan*/  (* p_multi_adv_cback ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_BLE_MULTI_ADV_ENB_EVT ; 
 int /*<<< orphan*/  BTA_FAILURE ; 
 scalar_t__ BTM_BleEnableAdvInstance (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ),int /*<<< orphan*/ *) ; 
 scalar_t__ BTM_BleMaxMultiAdvInstanceCount () ; 
 scalar_t__ BTM_CMD_STARTED ; 
 TYPE_3__ bta_dm_cb ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void bta_dm_ble_multi_adv_enb(tBTA_DM_MSG *p_data)
{
    tBTM_STATUS btm_status = 0;

    bta_dm_cb.p_multi_adv_cback = p_data->ble_multi_adv_enb.p_cback;
    if (BTM_BleMaxMultiAdvInstanceCount() > 0 && NULL != p_data->ble_multi_adv_enb.p_ref) {
        btm_status = BTM_BleEnableAdvInstance((tBTM_BLE_ADV_PARAMS *)
                                              p_data->ble_multi_adv_enb.p_params,
                                              p_data->ble_multi_adv_enb.p_cback,
                                              p_data->ble_multi_adv_enb.p_ref);
    }

    if (BTM_CMD_STARTED != btm_status) {
        bta_dm_cb.p_multi_adv_cback(BTA_BLE_MULTI_ADV_ENB_EVT, 0xFF,
                                    p_data->ble_multi_adv_enb.p_ref, BTA_FAILURE);
    }
}