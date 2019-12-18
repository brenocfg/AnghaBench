#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  direct_bda; int /*<<< orphan*/  adv_chnl_map; int /*<<< orphan*/  adv_interval_max; int /*<<< orphan*/  adv_interval_min; } ;
typedef  TYPE_2__ tBTM_BLE_INQ_CB ;
typedef  int /*<<< orphan*/  tBTM_BLE_ADV_CHNL_MAP ;
typedef  int /*<<< orphan*/  tBLE_BD_ADDR ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_5__ {TYPE_2__ inq_var; } ;
struct TYPE_8__ {TYPE_1__ ble_ctr_cb; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* supports_ble ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_TRACE_EVENT (char*) ; 
 TYPE_4__ btm_cb ; 
 TYPE_3__* controller_get_interface () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 () ; 

void BTM_BleReadAdvParams (UINT16 *adv_int_min, UINT16 *adv_int_max,
                           tBLE_BD_ADDR *p_dir_bda, tBTM_BLE_ADV_CHNL_MAP *p_chnl_map)
{
    tBTM_BLE_INQ_CB *p_cb = &btm_cb.ble_ctr_cb.inq_var;

    BTM_TRACE_EVENT ("BTM_BleReadAdvParams ");
    if (!controller_get_interface()->supports_ble()) {
        return ;
    }

    *adv_int_min = p_cb->adv_interval_min;
    *adv_int_max = p_cb->adv_interval_max;
    *p_chnl_map = p_cb->adv_chnl_map;

    if (p_dir_bda != NULL) {
        memcpy(p_dir_bda, &p_cb->direct_bda, sizeof(tBLE_BD_ADDR));
    }
}