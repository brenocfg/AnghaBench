#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tBTM_STATUS ;
struct TYPE_5__ {scalar_t__ evt_type; scalar_t__ afp; void* adv_mode; int /*<<< orphan*/  state; } ;
typedef  TYPE_2__ tBTM_BLE_INQ_CB ;
typedef  int /*<<< orphan*/  tBTM_BLE_GAP_STATE ;
typedef  void* UINT8 ;
struct TYPE_4__ {int /*<<< orphan*/  wl_state; TYPE_2__ inq_var; } ;
struct TYPE_6__ {TYPE_1__ ble_ctr_cb; } ;

/* Variables and functions */
 scalar_t__ AP_SCAN_CONN_ALL ; 
 int /*<<< orphan*/  BTM_BLE_ADVERTISING ; 
 void* BTM_BLE_ADV_DISABLE ; 
 void* BTM_BLE_ADV_ENABLE ; 
 scalar_t__ BTM_BLE_CONNECT_DIR_EVT ; 
 scalar_t__ BTM_BLE_CONNECT_LO_DUTY_DIR_EVT ; 
 int /*<<< orphan*/  BTM_BLE_RL_ADV ; 
 int /*<<< orphan*/  BTM_BLE_WL_ADV ; 
 scalar_t__ BTM_NO_RESOURCES ; 
 int /*<<< orphan*/  BTM_TRACE_EVENT (char*) ; 
 scalar_t__ BTM_WRONG_MODE ; 
 scalar_t__ HCI_SUCCESS ; 
 int /*<<< orphan*/  OSI_MUTEX_MAX_TIMEOUT ; 
 int /*<<< orphan*/  OSI_SEM_MAX_TIMEOUT ; 
 int /*<<< orphan*/  adv_enable_lock ; 
 int /*<<< orphan*/  adv_enable_sem ; 
 scalar_t__ adv_enable_status ; 
 int /*<<< orphan*/  btm_ble_adv_states_operation (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  btm_ble_clear_topology_mask ; 
 int /*<<< orphan*/  btm_ble_enable_resolving_list_for_platform (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btm_ble_set_topology_mask ; 
 int /*<<< orphan*/  btm_ble_topology_check ; 
 TYPE_3__ btm_cb ; 
 int /*<<< orphan*/  btm_execute_wl_dev_operation () ; 
 scalar_t__ btsnd_hcic_ble_set_adv_enable (void*) ; 
 int /*<<< orphan*/  osi_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osi_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osi_sem_take (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

tBTM_STATUS btm_ble_start_adv(void)
{
    tBTM_BLE_INQ_CB *p_cb = &btm_cb.ble_ctr_cb.inq_var;
    tBTM_STATUS     rt = BTM_NO_RESOURCES;
    BTM_TRACE_EVENT ("btm_ble_start_adv\n");


    if (!btm_ble_adv_states_operation (btm_ble_topology_check, p_cb->evt_type)) {
        return BTM_WRONG_MODE;
    }

    osi_mutex_lock(&adv_enable_lock, OSI_MUTEX_MAX_TIMEOUT);

#if (defined BLE_PRIVACY_SPT && BLE_PRIVACY_SPT == TRUE)
    /* To relax resolving list,  always have resolving list enabled, unless directed adv */
    if (p_cb->evt_type != BTM_BLE_CONNECT_LO_DUTY_DIR_EVT &&
            p_cb->evt_type != BTM_BLE_CONNECT_DIR_EVT)
        /* enable resolving list is desired */
    {
        btm_ble_enable_resolving_list_for_platform(BTM_BLE_RL_ADV);
    }
#endif
    if (p_cb->afp != AP_SCAN_CONN_ALL) {
        //find the device in the btm dev buffer and write it to the controller white list
        btm_execute_wl_dev_operation();
        btm_cb.ble_ctr_cb.wl_state |= BTM_BLE_WL_ADV;
    }
    /* The complete event comes up immediately after the 'btsnd_hcic_ble_set_adv_enable' being called in dual core,
    this causes the 'adv_mode' and 'state' not be set yet, so we set the state first */
    tBTM_BLE_GAP_STATE temp_state = p_cb->state;
    UINT8 adv_mode = p_cb->adv_mode;
    p_cb->adv_mode = BTM_BLE_ADV_ENABLE;
    p_cb->state = BTM_BLE_ADVERTISING;
    btm_ble_adv_states_operation(btm_ble_set_topology_mask, p_cb->evt_type);
    if (btsnd_hcic_ble_set_adv_enable (BTM_BLE_ADV_ENABLE)) {
        osi_sem_take(&adv_enable_sem, OSI_SEM_MAX_TIMEOUT);
        rt = adv_enable_status;
        BTM_TRACE_EVENT ("BTM_SUCCESS\n");
    } else {
        p_cb->adv_mode = BTM_BLE_ADV_DISABLE;
        p_cb->state = temp_state;
        p_cb->adv_mode = adv_mode;
        btm_ble_adv_states_operation(btm_ble_clear_topology_mask, p_cb->evt_type);
        btm_cb.ble_ctr_cb.wl_state &= ~BTM_BLE_WL_ADV;
    }

    if(adv_enable_status != HCI_SUCCESS) {
        p_cb->adv_mode = adv_mode;
    }
    osi_mutex_unlock(&adv_enable_lock);
    return rt;
}