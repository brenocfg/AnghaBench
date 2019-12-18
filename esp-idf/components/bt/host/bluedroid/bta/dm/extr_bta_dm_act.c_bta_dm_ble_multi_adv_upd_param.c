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
struct TYPE_5__ {scalar_t__ inst_id; scalar_t__ p_params; } ;
struct TYPE_6__ {TYPE_1__ ble_multi_adv_param; } ;
typedef  TYPE_2__ tBTA_DM_MSG ;
struct TYPE_7__ {int /*<<< orphan*/  (* p_multi_adv_cback ) (int /*<<< orphan*/ ,scalar_t__,void*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_BLE_MULTI_ADV_PARAM_EVT ; 
 int /*<<< orphan*/  BTA_FAILURE ; 
 scalar_t__ BTM_BleMaxMultiAdvInstanceCount () ; 
 scalar_t__ BTM_BleUpdateAdvInstParam (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ BTM_CMD_STARTED ; 
 TYPE_3__ bta_dm_cb ; 
 void* btm_ble_multi_adv_get_ref (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__,void*,int /*<<< orphan*/ ) ; 

void bta_dm_ble_multi_adv_upd_param(tBTA_DM_MSG *p_data)
{
    tBTM_STATUS btm_status = 0;
    void *p_ref = NULL;

    if (BTM_BleMaxMultiAdvInstanceCount() > 0 && p_data->ble_multi_adv_param.inst_id > 0
            && p_data->ble_multi_adv_param.inst_id < BTM_BleMaxMultiAdvInstanceCount()) {
        btm_status = BTM_BleUpdateAdvInstParam(p_data->ble_multi_adv_param.inst_id,
                                               (tBTM_BLE_ADV_PARAMS *)p_data->ble_multi_adv_param.p_params);
    }

    if (BTM_CMD_STARTED != btm_status) {
        p_ref = btm_ble_multi_adv_get_ref(p_data->ble_multi_adv_param.inst_id);
        bta_dm_cb.p_multi_adv_cback(BTA_BLE_MULTI_ADV_PARAM_EVT,
                                    p_data->ble_multi_adv_param.inst_id, p_ref, BTA_FAILURE);
    }
}