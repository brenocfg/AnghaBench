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
struct TYPE_3__ {void* p_ref; } ;
typedef  TYPE_1__ tBTM_BLE_MULTI_ADV_INST ;
typedef  int UINT8 ;
struct TYPE_4__ {TYPE_1__* p_adv_inst; } ;

/* Variables and functions */
 int BTM_BleMaxMultiAdvInstanceCount () ; 
 TYPE_2__ btm_multi_adv_cb ; 

void *btm_ble_multi_adv_get_ref(UINT8 inst_id)
{
    tBTM_BLE_MULTI_ADV_INST *p_inst = NULL;

    if (inst_id < BTM_BleMaxMultiAdvInstanceCount()) {
        p_inst = &btm_multi_adv_cb.p_adv_inst[inst_id - 1];
        if (NULL != p_inst) {
            return p_inst->p_ref;
        }
    }

    return NULL;
}