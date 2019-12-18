#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTM_STATUS ;
struct TYPE_7__ {scalar_t__ in_use; } ;
typedef  TYPE_2__ tBTM_BLE_MULTI_ADV_INST ;
typedef  int /*<<< orphan*/  tBTM_BLE_ADV_PARAMS ;
typedef  int UINT8 ;
struct TYPE_6__ {scalar_t__ adv_inst_max; } ;
struct TYPE_9__ {TYPE_1__ cmn_ble_vsc_cb; } ;
struct TYPE_8__ {TYPE_2__* p_adv_inst; } ;

/* Variables and functions */
 int BTM_BLE_MULTI_ADV_DEFAULT_STD ; 
 int /*<<< orphan*/  BTM_BLE_MULTI_ADV_PARAM_EVT ; 
 int BTM_BleMaxMultiAdvInstanceCount () ; 
 scalar_t__ BTM_CMD_STARTED ; 
 int /*<<< orphan*/  BTM_ERR_PROCESSING ; 
 int /*<<< orphan*/  BTM_ILLEGAL_VALUE ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*,int) ; 
 int /*<<< orphan*/  BTM_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  BTM_TRACE_EVENT (char*,int) ; 
 int /*<<< orphan*/  BTM_WRONG_MODE ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  btm_ble_enable_multi_adv (scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ btm_ble_multi_adv_set_params (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_4__ btm_cb ; 
 TYPE_3__ btm_multi_adv_cb ; 

tBTM_STATUS BTM_BleUpdateAdvInstParam (UINT8 inst_id, tBTM_BLE_ADV_PARAMS *p_params)
{
    tBTM_STATUS rt = BTM_ILLEGAL_VALUE;
    tBTM_BLE_MULTI_ADV_INST *p_inst = &btm_multi_adv_cb.p_adv_inst[inst_id - 1];

    BTM_TRACE_EVENT("BTM_BleUpdateAdvInstParam called with inst_id:%d", inst_id);

    if (0 == btm_cb.cmn_ble_vsc_cb.adv_inst_max) {
        BTM_TRACE_ERROR("Controller does not support Multi ADV");
        return BTM_ERR_PROCESSING;
    }

    if (inst_id <  BTM_BleMaxMultiAdvInstanceCount() &&
            inst_id != BTM_BLE_MULTI_ADV_DEFAULT_STD &&
            p_params != NULL) {
        if (FALSE == p_inst->in_use) {
            BTM_TRACE_DEBUG("adv instance %d is not active", inst_id);
            return BTM_WRONG_MODE;
        } else {
            btm_ble_enable_multi_adv(FALSE, inst_id, 0);
        }

        if (BTM_CMD_STARTED == btm_ble_multi_adv_set_params(p_inst, p_params, 0)) {
            rt = btm_ble_enable_multi_adv(TRUE, inst_id, BTM_BLE_MULTI_ADV_PARAM_EVT);
        }
    }
    return rt;
}