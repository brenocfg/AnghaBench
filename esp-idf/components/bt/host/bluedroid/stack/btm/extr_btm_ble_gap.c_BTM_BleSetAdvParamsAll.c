#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTM_STATUS ;
typedef  int /*<<< orphan*/  (* tBTM_START_ADV_CMPL_CBACK ) (int /*<<< orphan*/ ) ;
struct TYPE_11__ {int exist_addr_bit; scalar_t__ own_addr_type; TYPE_4__* static_rand_addr; int /*<<< orphan*/ * private_addr; TYPE_4__* resolvale_addr; } ;
typedef  TYPE_2__ tBTM_LE_RANDOM_CB ;
struct TYPE_12__ {int /*<<< orphan*/  afp; int /*<<< orphan*/  direct_bda; int /*<<< orphan*/  (* p_adv_cb ) (int /*<<< orphan*/ ) ;scalar_t__ evt_type; int /*<<< orphan*/  adv_chnl_map; void* adv_interval_max; void* adv_interval_min; } ;
typedef  TYPE_3__ tBTM_BLE_INQ_CB ;
typedef  int /*<<< orphan*/  tBTM_BLE_AFP ;
typedef  int /*<<< orphan*/  tBTM_BLE_ADV_CHNL_MAP ;
struct TYPE_13__ {int /*<<< orphan*/  bda; int /*<<< orphan*/  type; } ;
typedef  TYPE_4__ tBLE_BD_ADDR ;
typedef  scalar_t__ tBLE_ADDR_TYPE ;
typedef  scalar_t__ UINT8 ;
typedef  void* UINT16 ;
struct TYPE_10__ {scalar_t__ privacy_mode; TYPE_2__ addr_mgnt_cb; TYPE_3__ inq_var; } ;
struct TYPE_15__ {TYPE_1__ ble_ctr_cb; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* supports_ble ) () ;} ;

/* Variables and functions */
 int BD_ADDR_LEN ; 
 scalar_t__ BLE_ADDR_PUBLIC ; 
 scalar_t__ BLE_ADDR_PUBLIC_ID ; 
 scalar_t__ BLE_ADDR_RANDOM ; 
 scalar_t__ BLE_ADDR_RANDOM_ID ; 
 int /*<<< orphan*/  BTM_BLE_ADV_INT_MAX ; 
 int /*<<< orphan*/  BTM_BLE_ADV_INT_MIN ; 
 scalar_t__ BTM_BLE_CONNECT_DIR_EVT ; 
 scalar_t__ BTM_BLE_CONNECT_LO_DUTY_DIR_EVT ; 
 int BTM_BLE_GAP_ADDR_BIT_RANDOM ; 
 int BTM_BLE_GAP_ADDR_BIT_RESOLVABLE ; 
 int /*<<< orphan*/  BTM_BLE_ISVALID_PARAM (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ BTM_BLE_NON_CONNECT_EVT ; 
 int /*<<< orphan*/  BTM_BLE_STATE_HI_DUTY_DIR_ADV_BIT ; 
 int /*<<< orphan*/  BTM_BLE_STATE_LO_DUTY_DIR_ADV_BIT ; 
 int /*<<< orphan*/  BTM_BLE_STATE_NON_CONN_ADV_BIT ; 
 int /*<<< orphan*/  BTM_BleConfigPrivacy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BTM_ILLEGAL_VALUE ; 
 int /*<<< orphan*/  BTM_NO_RESOURCES ; 
 scalar_t__ BTM_PRIVACY_NONE ; 
 int /*<<< orphan*/  BTM_SUCCESS ; 
 int /*<<< orphan*/  BTM_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  BTM_TRACE_EVENT (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HCI_ERR_ESP_VENDOR_FAIL ; 
 int /*<<< orphan*/  OSI_MUTEX_MAX_TIMEOUT ; 
 int /*<<< orphan*/  OSI_SEM_MAX_TIMEOUT ; 
 int /*<<< orphan*/  adv_param_lock ; 
 int /*<<< orphan*/  adv_param_sem ; 
 int /*<<< orphan*/  adv_param_status ; 
 int /*<<< orphan*/  btm_ble_set_topology_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btm_ble_stop_adv () ; 
 TYPE_8__ btm_cb ; 
 int /*<<< orphan*/  btsnd_hcic_ble_set_random_addr (TYPE_4__*) ; 
 scalar_t__ btsnd_hcic_ble_write_adv_params (void*,void*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__* controller_get_interface () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 int /*<<< orphan*/  osi_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osi_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osi_sem_take (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ) ; 

tBTM_STATUS BTM_BleSetAdvParamsAll(UINT16 adv_int_min, UINT16 adv_int_max, UINT8 adv_type,
                                        tBLE_ADDR_TYPE own_bda_type, tBLE_BD_ADDR *p_dir_bda,
                                        tBTM_BLE_ADV_CHNL_MAP chnl_map, tBTM_BLE_AFP afp, tBTM_START_ADV_CMPL_CBACK *adv_cb)
{
    tBTM_LE_RANDOM_CB *p_addr_cb = &btm_cb.ble_ctr_cb.addr_mgnt_cb;
    tBTM_BLE_INQ_CB *p_cb = &btm_cb.ble_ctr_cb.inq_var;

    BTM_TRACE_EVENT ("BTM_BleSetAdvParamsAll\n");

    if (!controller_get_interface()->supports_ble()) {
        return BTM_ILLEGAL_VALUE;
    }

    if(own_bda_type == BLE_ADDR_RANDOM) {
        if((btm_cb.ble_ctr_cb.addr_mgnt_cb.exist_addr_bit & BTM_BLE_GAP_ADDR_BIT_RANDOM) == BTM_BLE_GAP_ADDR_BIT_RANDOM) {
            //close privacy
            #if BLE_PRIVACY_SPT == TRUE
            if (btm_cb.ble_ctr_cb.privacy_mode != BTM_PRIVACY_NONE) {
                BTM_BleConfigPrivacy(FALSE, NULL);
            }
            #endif
            btm_cb.ble_ctr_cb.addr_mgnt_cb.own_addr_type = BLE_ADDR_RANDOM;
            memcpy(btm_cb.ble_ctr_cb.addr_mgnt_cb.private_addr, btm_cb.ble_ctr_cb.addr_mgnt_cb.static_rand_addr, BD_ADDR_LEN);
            // set address to controller
            btsnd_hcic_ble_set_random_addr(btm_cb.ble_ctr_cb.addr_mgnt_cb.static_rand_addr);

        } else if((btm_cb.ble_ctr_cb.addr_mgnt_cb.exist_addr_bit & BTM_BLE_GAP_ADDR_BIT_RESOLVABLE) == BTM_BLE_GAP_ADDR_BIT_RESOLVABLE) {
            btm_cb.ble_ctr_cb.addr_mgnt_cb.own_addr_type = BLE_ADDR_RANDOM;
            memcpy(btm_cb.ble_ctr_cb.addr_mgnt_cb.private_addr, btm_cb.ble_ctr_cb.addr_mgnt_cb.resolvale_addr, BD_ADDR_LEN);
            btsnd_hcic_ble_set_random_addr(btm_cb.ble_ctr_cb.addr_mgnt_cb.resolvale_addr);
        }else {
            BTM_TRACE_ERROR ("No random address yet, please set random address and try\n");
            if(adv_cb) {
                (* adv_cb)(HCI_ERR_ESP_VENDOR_FAIL);
            }
            return BTM_ILLEGAL_VALUE;
        }
    } else if(own_bda_type == BLE_ADDR_PUBLIC_ID || own_bda_type == BLE_ADDR_RANDOM_ID) {
        if((btm_cb.ble_ctr_cb.addr_mgnt_cb.exist_addr_bit & BTM_BLE_GAP_ADDR_BIT_RESOLVABLE) == BTM_BLE_GAP_ADDR_BIT_RESOLVABLE) {
            own_bda_type = BLE_ADDR_RANDOM;
            btm_cb.ble_ctr_cb.addr_mgnt_cb.own_addr_type = BLE_ADDR_RANDOM;
            memcpy(btm_cb.ble_ctr_cb.addr_mgnt_cb.private_addr, btm_cb.ble_ctr_cb.addr_mgnt_cb.resolvale_addr, BD_ADDR_LEN);
            btsnd_hcic_ble_set_random_addr(btm_cb.ble_ctr_cb.addr_mgnt_cb.resolvale_addr);
        } else {
            #if BLE_PRIVACY_SPT == TRUE
            if(btm_cb.ble_ctr_cb.privacy_mode != BTM_PRIVACY_NONE) {
                BTM_TRACE_ERROR ("Error state\n");
                if(adv_cb) {
                    (* adv_cb)(HCI_ERR_ESP_VENDOR_FAIL);
                }
                return BTM_ILLEGAL_VALUE;
            }
            #endif
            if(own_bda_type == BLE_ADDR_PUBLIC_ID) {
                own_bda_type = BLE_ADDR_PUBLIC;
                btm_cb.ble_ctr_cb.addr_mgnt_cb.own_addr_type = BLE_ADDR_PUBLIC;
            } else { //own_bda_type == BLE_ADDR_RANDOM_ID
                if((btm_cb.ble_ctr_cb.addr_mgnt_cb.exist_addr_bit & BTM_BLE_GAP_ADDR_BIT_RANDOM) == BTM_BLE_GAP_ADDR_BIT_RANDOM) {
                    own_bda_type = BLE_ADDR_RANDOM;
                    btm_cb.ble_ctr_cb.addr_mgnt_cb.own_addr_type = BLE_ADDR_RANDOM;
                    memcpy(btm_cb.ble_ctr_cb.addr_mgnt_cb.private_addr, btm_cb.ble_ctr_cb.addr_mgnt_cb.static_rand_addr, BD_ADDR_LEN);
                    btsnd_hcic_ble_set_random_addr(btm_cb.ble_ctr_cb.addr_mgnt_cb.static_rand_addr);
                } else {
                    BTM_TRACE_ERROR ("No RPA and no random address yet, please set RPA or random address and try\n");
                    if(adv_cb) {
                        (* adv_cb)(HCI_ERR_ESP_VENDOR_FAIL);
                    }
                    return BTM_ILLEGAL_VALUE;
                }
            }
        }
    } else {
        btm_cb.ble_ctr_cb.addr_mgnt_cb.own_addr_type = BLE_ADDR_PUBLIC;
    }

    if (!BTM_BLE_ISVALID_PARAM(adv_int_min, BTM_BLE_ADV_INT_MIN, BTM_BLE_ADV_INT_MAX) ||
            !BTM_BLE_ISVALID_PARAM(adv_int_max, BTM_BLE_ADV_INT_MIN, BTM_BLE_ADV_INT_MAX)) {
         BTM_TRACE_ERROR ("adv_int_min or adv_int_max is invalid\n");
        if(adv_cb) {
            (* adv_cb)(HCI_ERR_ESP_VENDOR_FAIL);
        }
        return BTM_ILLEGAL_VALUE;
    }

    btm_ble_stop_adv();

    osi_mutex_lock(&adv_param_lock, OSI_MUTEX_MAX_TIMEOUT);
    if(adv_type == BTM_BLE_CONNECT_DIR_EVT){
        btm_ble_set_topology_mask(BTM_BLE_STATE_HI_DUTY_DIR_ADV_BIT);
    }else if(adv_type == BTM_BLE_CONNECT_LO_DUTY_DIR_EVT){
        btm_ble_set_topology_mask(BTM_BLE_STATE_LO_DUTY_DIR_ADV_BIT);
    }else if(adv_type == BTM_BLE_NON_CONNECT_EVT){
        btm_ble_set_topology_mask(BTM_BLE_STATE_NON_CONN_ADV_BIT);
    }

    p_cb->adv_interval_min = adv_int_min;
    p_cb->adv_interval_max = adv_int_max;
    p_cb->adv_chnl_map = chnl_map;
    p_addr_cb->own_addr_type = own_bda_type;
    p_cb->evt_type = adv_type;
    p_cb->afp = afp;
    p_cb->p_adv_cb = adv_cb;

    if (p_dir_bda) {
        memcpy(&p_cb->direct_bda, p_dir_bda, sizeof(tBLE_BD_ADDR));
    }

    BTM_TRACE_EVENT ("update params for an active adv\n");

    tBTM_STATUS status = BTM_SUCCESS;
    /* update adv params */
    if (btsnd_hcic_ble_write_adv_params (adv_int_min,
                                        adv_int_max,
                                        adv_type,
                                        own_bda_type,
                                        p_dir_bda->type,
                                        p_dir_bda->bda,
                                        chnl_map,
                                        p_cb->afp)) {
        osi_sem_take(&adv_param_sem, OSI_SEM_MAX_TIMEOUT);
        status = adv_param_status;
    } else {
        status = BTM_NO_RESOURCES;
    }
    osi_mutex_unlock(&adv_param_lock);
    return status;
}