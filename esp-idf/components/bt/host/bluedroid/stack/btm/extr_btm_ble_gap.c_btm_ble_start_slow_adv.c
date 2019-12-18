#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  own_addr_type; } ;
typedef  TYPE_2__ tBTM_LE_RANDOM_CB ;
struct TYPE_11__ {scalar_t__ adv_mode; int /*<<< orphan*/  afp; int /*<<< orphan*/  adv_chnl_map; int /*<<< orphan*/  evt_type; } ;
typedef  TYPE_3__ tBTM_BLE_INQ_CB ;
typedef  int /*<<< orphan*/  tBLE_ADDR_TYPE ;
struct TYPE_9__ {TYPE_2__ addr_mgnt_cb; TYPE_3__ inq_var; } ;
struct TYPE_13__ {TYPE_1__ ble_ctr_cb; } ;
struct TYPE_12__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_4__ BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BLE_ADDR_PUBLIC ; 
 scalar_t__ BTM_BLE_ADV_ENABLE ; 
 int /*<<< orphan*/  BTM_BLE_GAP_ADV_SLOW_INT ; 
 int /*<<< orphan*/  btm_ble_start_adv () ; 
 int /*<<< orphan*/  btm_ble_stop_adv () ; 
 TYPE_8__ btm_cb ; 
 int /*<<< orphan*/  btm_set_conn_mode_adv_init_addr (TYPE_3__*,TYPE_4__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btsnd_hcic_ble_write_adv_params (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btm_ble_start_slow_adv (void)
{
    tBTM_BLE_INQ_CB *p_cb = &btm_cb.ble_ctr_cb.inq_var;

    if (p_cb->adv_mode == BTM_BLE_ADV_ENABLE) {
        tBTM_LE_RANDOM_CB *p_addr_cb = &btm_cb.ble_ctr_cb.addr_mgnt_cb;
        BD_ADDR p_addr_ptr = {0};
        tBLE_ADDR_TYPE init_addr_type = BLE_ADDR_PUBLIC;
        tBLE_ADDR_TYPE own_addr_type = p_addr_cb->own_addr_type;

        btm_ble_stop_adv();

        p_cb->evt_type = btm_set_conn_mode_adv_init_addr(p_cb, p_addr_ptr, &init_addr_type,
                         &own_addr_type);

        /* slow adv mode never goes into directed adv */
        btsnd_hcic_ble_write_adv_params (BTM_BLE_GAP_ADV_SLOW_INT, BTM_BLE_GAP_ADV_SLOW_INT,
                                         p_cb->evt_type, own_addr_type,
                                         init_addr_type, p_addr_ptr,
                                         p_cb->adv_chnl_map, p_cb->afp);

        btm_ble_start_adv();
    }
}