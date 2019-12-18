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
typedef  scalar_t__ tBTM_STATUS ;
struct TYPE_7__ {scalar_t__ in_use; void* p_ref; int /*<<< orphan*/ * p_cback; int /*<<< orphan*/  inst_id; } ;
typedef  TYPE_2__ tBTM_BLE_MULTI_ADV_INST ;
typedef  int /*<<< orphan*/  tBTM_BLE_MULTI_ADV_CBACK ;
typedef  int /*<<< orphan*/  tBTM_BLE_ADV_PARAMS ;
typedef  int UINT8 ;
struct TYPE_6__ {scalar_t__ adv_inst_max; } ;
struct TYPE_9__ {TYPE_1__ cmn_ble_vsc_cb; } ;
struct TYPE_8__ {TYPE_2__* p_adv_inst; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_BLE_MULTI_ADV_ENB_EVT ; 
 int BTM_BleMaxMultiAdvInstanceCount () ; 
 scalar_t__ BTM_CMD_STARTED ; 
 scalar_t__ BTM_ERR_PROCESSING ; 
 scalar_t__ BTM_NO_RESOURCES ; 
 int /*<<< orphan*/  BTM_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  BTM_TRACE_EVENT (char*,...) ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 scalar_t__ btm_ble_enable_multi_adv (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ btm_ble_multi_adv_set_params (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_4__ btm_cb ; 
 TYPE_3__ btm_multi_adv_cb ; 

tBTM_STATUS BTM_BleEnableAdvInstance (tBTM_BLE_ADV_PARAMS *p_params,
                                      tBTM_BLE_MULTI_ADV_CBACK *p_cback, void *p_ref)
{
    UINT8 i;
    tBTM_STATUS rt = BTM_NO_RESOURCES;
    tBTM_BLE_MULTI_ADV_INST *p_inst = &btm_multi_adv_cb.p_adv_inst[0];

    BTM_TRACE_EVENT("BTM_BleEnableAdvInstance called");

    if (0 == btm_cb.cmn_ble_vsc_cb.adv_inst_max) {
        BTM_TRACE_ERROR("Controller does not support Multi ADV");
        return BTM_ERR_PROCESSING;
    }

    if (NULL == p_inst) {
        BTM_TRACE_ERROR("Invalid instance in BTM_BleEnableAdvInstance");
        return BTM_ERR_PROCESSING;
    }

    for (i = 0; i <  BTM_BleMaxMultiAdvInstanceCount() - 1; i ++, p_inst++) {
        if (FALSE == p_inst->in_use) {
            p_inst->in_use = TRUE;
            /* configure adv parameter */
            if (p_params) {
                rt = btm_ble_multi_adv_set_params(p_inst, p_params, 0);
            } else {
                rt = BTM_CMD_STARTED;
            }

            /* enable adv */
            BTM_TRACE_EVENT("btm_ble_enable_multi_adv being called with inst_id:%d",
                            p_inst->inst_id);

            if (BTM_CMD_STARTED == rt) {
                if ((rt = btm_ble_enable_multi_adv (TRUE, p_inst->inst_id,
                                                    BTM_BLE_MULTI_ADV_ENB_EVT)) == BTM_CMD_STARTED) {
                    p_inst->p_cback = p_cback;
                    p_inst->p_ref   = p_ref;
                }
            }

            if (BTM_CMD_STARTED != rt) {
                p_inst->in_use = FALSE;
                BTM_TRACE_ERROR("BTM_BleEnableAdvInstance failed");
            }
            break;
        }
    }
    return rt;
}