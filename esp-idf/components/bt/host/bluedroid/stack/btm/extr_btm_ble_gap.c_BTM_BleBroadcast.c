#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTM_STATUS ;
typedef  int /*<<< orphan*/  tBTM_START_STOP_ADV_CMPL_CBACK ;
struct TYPE_9__ {int /*<<< orphan*/  own_addr_type; } ;
typedef  TYPE_3__ tBTM_LE_RANDOM_CB ;
struct TYPE_8__ {int /*<<< orphan*/  bda; int /*<<< orphan*/  type; } ;
struct TYPE_10__ {scalar_t__ adv_mode; int /*<<< orphan*/ * p_stop_adv_cb; int /*<<< orphan*/  evt_type; int /*<<< orphan*/  afp; int /*<<< orphan*/  adv_chnl_map; TYPE_2__ direct_bda; scalar_t__ adv_interval_max; scalar_t__ adv_interval_min; scalar_t__ scan_rsp; } ;
typedef  TYPE_4__ tBTM_BLE_INQ_CB ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_7__ {TYPE_4__ inq_var; TYPE_3__ addr_mgnt_cb; } ;
struct TYPE_12__ {TYPE_1__ ble_ctr_cb; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* supports_ble ) () ;} ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 scalar_t__ BTM_BLE_ADV_DISABLE ; 
 scalar_t__ BTM_BLE_ADV_ENABLE ; 
 int /*<<< orphan*/  BTM_BLE_CONNECT_EVT ; 
 int /*<<< orphan*/  BTM_BLE_DISCOVER_EVT ; 
 scalar_t__ BTM_BLE_GAP_ADV_INT ; 
 int /*<<< orphan*/  BTM_BLE_NON_CONNECT_EVT ; 
 scalar_t__ BTM_BLE_PC_ADV_TEST_MODE ; 
 int /*<<< orphan*/  BTM_BLE_RL_ADV ; 
 int /*<<< orphan*/  BTM_ILLEGAL_VALUE ; 
 int /*<<< orphan*/  BTM_NO_RESOURCES ; 
 int /*<<< orphan*/  BTM_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  btm_ble_disable_resolving_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btm_ble_start_adv () ; 
 int /*<<< orphan*/  btm_ble_stop_adv () ; 
 TYPE_6__ btm_cb ; 
 int /*<<< orphan*/  btsnd_hcic_ble_write_adv_params (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* controller_get_interface () ; 
 int /*<<< orphan*/  stub1 () ; 

tBTM_STATUS BTM_BleBroadcast(BOOLEAN start, tBTM_START_STOP_ADV_CMPL_CBACK  *p_stop_adv_cback)
{
    tBTM_STATUS status = BTM_NO_RESOURCES;
    tBTM_LE_RANDOM_CB *p_addr_cb = &btm_cb.ble_ctr_cb.addr_mgnt_cb;
    tBTM_BLE_INQ_CB *p_cb = &btm_cb.ble_ctr_cb.inq_var;
    UINT8 evt_type = p_cb->scan_rsp ? BTM_BLE_DISCOVER_EVT : BTM_BLE_NON_CONNECT_EVT;

    if (!controller_get_interface()->supports_ble()) {
        return BTM_ILLEGAL_VALUE;
    }

#ifdef  BTM_BLE_PC_ADV_TEST_MODE
    if (BTM_BLE_PC_ADV_TEST_MODE) {
        evt_type = p_cb->scan_rsp ? BTM_BLE_CONNECT_EVT : BTM_BLE_NON_CONNECT_EVT;
    }
#endif

    if (start && p_cb->adv_mode == BTM_BLE_ADV_DISABLE) {
        /* update adv params */
        if (!btsnd_hcic_ble_write_adv_params ((UINT16)(p_cb->adv_interval_min ? p_cb->adv_interval_min :
                                              BTM_BLE_GAP_ADV_INT),
                                              (UINT16)(p_cb->adv_interval_max ? p_cb->adv_interval_max :
                                                      BTM_BLE_GAP_ADV_INT),
                                              evt_type,
                                              p_addr_cb->own_addr_type,
                                              p_cb->direct_bda.type,
                                              p_cb->direct_bda.bda,
                                              p_cb->adv_chnl_map,
                                              p_cb->afp))

        {
            status = BTM_NO_RESOURCES;
        } else {
            p_cb->evt_type = evt_type;
        }

        status = btm_ble_start_adv ();
    } else if (!start && p_cb->adv_mode == BTM_BLE_ADV_ENABLE) {
        //save the stop adv callback to the BTM env.
        p_cb->p_stop_adv_cb = p_stop_adv_cback;
        status = btm_ble_stop_adv();
#if BLE_PRIVACY_SPT == TRUE
        btm_ble_disable_resolving_list(BTM_BLE_RL_ADV, TRUE);
#endif
    } else {
        /*
            1. start adv when adv has already started (not used)
            2. stop adv shen adv has already stoped
        */
        status = BTM_SUCCESS;
    }
    return status;
}