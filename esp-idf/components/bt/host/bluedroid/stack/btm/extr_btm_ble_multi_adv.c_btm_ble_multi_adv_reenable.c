#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ in_use; scalar_t__ adv_evt; int /*<<< orphan*/  p_ref; int /*<<< orphan*/  inst_id; int /*<<< orphan*/  (* p_cback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ tBTM_BLE_MULTI_ADV_INST ;
typedef  int UINT8 ;
struct TYPE_4__ {TYPE_1__* p_adv_inst; } ;

/* Variables and functions */
 scalar_t__ BTM_BLE_CONNECT_DIR_EVT ; 
 int /*<<< orphan*/  BTM_BLE_MULTI_ADV_DISABLE_EVT ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  btm_ble_enable_multi_adv (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ btm_multi_adv_cb ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void btm_ble_multi_adv_reenable(UINT8 inst_id)
{
    tBTM_BLE_MULTI_ADV_INST *p_inst = &btm_multi_adv_cb.p_adv_inst[inst_id - 1];

    if (TRUE == p_inst->in_use) {
        if (p_inst->adv_evt != BTM_BLE_CONNECT_DIR_EVT) {
            btm_ble_enable_multi_adv (TRUE, p_inst->inst_id, 0);
        } else
            /* mark directed adv as disabled if adv has been stopped */
        {
            (p_inst->p_cback)(BTM_BLE_MULTI_ADV_DISABLE_EVT, p_inst->inst_id, p_inst->p_ref, 0);
            p_inst->in_use = FALSE;
        }
    }
}