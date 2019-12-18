#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  timer_entry; int /*<<< orphan*/  remote_bd_addr; int /*<<< orphan*/  link_state; int /*<<< orphan*/  ble_addr_type; } ;
typedef  TYPE_4__ tL2C_LCB ;
struct TYPE_16__ {scalar_t__ min_conn_int; scalar_t__ max_conn_int; scalar_t__ slave_latency; scalar_t__ supervision_tout; } ;
struct TYPE_15__ {int /*<<< orphan*/  current_addr; int /*<<< orphan*/  current_addr_type; scalar_t__ current_addr_valid; } ;
struct TYPE_18__ {TYPE_3__ conn_params; TYPE_2__ ble; } ;
typedef  TYPE_5__ tBTM_SEC_DEV_REC ;
struct TYPE_14__ {int /*<<< orphan*/  own_addr_type; } ;
struct TYPE_19__ {scalar_t__ scan_int; scalar_t__ scan_win; TYPE_1__ addr_mgnt_cb; } ;
typedef  TYPE_6__ tBTM_BLE_CB ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_20__ {int /*<<< orphan*/  ble_connecting_bda; int /*<<< orphan*/  is_ble_connecting; } ;
struct TYPE_13__ {TYPE_6__ ble_ctr_cb; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int BD_ADDR_LEN ; 
 int /*<<< orphan*/  BLE_ADDR_PUBLIC ; 
 int /*<<< orphan*/  BLE_DIR_CONN ; 
 scalar_t__ BTM_BLE_CONN_INT_MAX_DEF ; 
 scalar_t__ BTM_BLE_CONN_INT_MIN_DEF ; 
 scalar_t__ BTM_BLE_CONN_PARAM_UNDEF ; 
 scalar_t__ BTM_BLE_CONN_SLAVE_LATENCY_DEF ; 
 scalar_t__ BTM_BLE_CONN_TIMEOUT_DEF ; 
 scalar_t__ BTM_BLE_SCAN_FAST_INT ; 
 scalar_t__ BTM_BLE_SCAN_FAST_WIN ; 
 scalar_t__ BTM_BLE_SCAN_PARAM_UNDEF ; 
 int /*<<< orphan*/  BTM_BLE_STATE_INIT ; 
 int /*<<< orphan*/  BTU_TTYPE_L2CAP_LINK ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  L2CAP_BLE_LINK_CONNECT_TOUT ; 
 int /*<<< orphan*/  L2CAP_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  L2CAP_TRACE_WARNING (char*) ; 
 int /*<<< orphan*/  LST_CONNECTING ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  btm_ble_set_conn_st (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btm_ble_topology_check (int /*<<< orphan*/ ) ; 
 TYPE_12__ btm_cb ; 
 TYPE_5__* btm_find_dev (int /*<<< orphan*/ ) ; 
 TYPE_5__* btm_find_or_alloc_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btsnd_hcic_ble_create_ll_conn (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btu_start_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_9__ l2cb ; 
 int /*<<< orphan*/  l2cu_release_lcb (TYPE_4__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

BOOLEAN l2cble_init_direct_conn (tL2C_LCB *p_lcb)
{
#if ( (defined BLE_PRIVACY_SPT) && (BLE_PRIVACY_SPT == TRUE))
    //check for security device information in the cache
    bool dev_rec_exist = true;
    tBTM_SEC_DEV_REC *find_dev_rec = btm_find_dev (p_lcb->remote_bd_addr);
    if(find_dev_rec == NULL) {
        dev_rec_exist = false;
    }

#endif
    tBTM_SEC_DEV_REC *p_dev_rec = btm_find_or_alloc_dev (p_lcb->remote_bd_addr);
    tBTM_BLE_CB *p_cb = &btm_cb.ble_ctr_cb;
    UINT16 scan_int;
    UINT16 scan_win;
    BD_ADDR peer_addr;
    UINT8 peer_addr_type = BLE_ADDR_PUBLIC;
    UINT8 own_addr_type = BLE_ADDR_PUBLIC;

    /* There can be only one BLE connection request outstanding at a time */
    if (p_dev_rec == NULL) {
        L2CAP_TRACE_WARNING ("unknown device, can not initate connection");
        return (FALSE);
    }

    scan_int = (p_cb->scan_int == BTM_BLE_SCAN_PARAM_UNDEF) ? BTM_BLE_SCAN_FAST_INT : p_cb->scan_int;
    scan_win = (p_cb->scan_win == BTM_BLE_SCAN_PARAM_UNDEF) ? BTM_BLE_SCAN_FAST_WIN : p_cb->scan_win;

    peer_addr_type = p_lcb->ble_addr_type;
    memcpy(peer_addr, p_lcb->remote_bd_addr, BD_ADDR_LEN);

#if ( (defined BLE_PRIVACY_SPT) && (BLE_PRIVACY_SPT == TRUE))
    own_addr_type = btm_cb.ble_ctr_cb.addr_mgnt_cb.own_addr_type;
    if(dev_rec_exist) {
        // if the current address information is valid, get the real address information
        if(p_dev_rec->ble.current_addr_valid) {
            peer_addr_type = p_dev_rec->ble.current_addr_type;
            memcpy(peer_addr, p_dev_rec->ble.current_addr, 6);
        } else {
            /* find security device information but not find the real address information
             * This state may be directly open without scanning. In this case, you must
             * use the current adv address of the device to open*/
        }
    } else {
        //not find security device information, We think this is a new device, connect directly
    }

    /* It will cause that scanner doesn't send scan request to advertiser
    * which has sent IRK to us and we have stored the IRK in controller.
    * It is a hardware limitation. The preliminary solution is not to
    * send key to the controller, but to resolve the random address in host.
    * so we need send the real address information to controller. */
    /*
    if (p_dev_rec->ble.in_controller_list & BTM_RESOLVING_LIST_BIT) {
        if (btm_cb.ble_ctr_cb.privacy_mode >=  BTM_PRIVACY_1_2) {
            own_addr_type |= BLE_ADDR_TYPE_ID_BIT;
        }

        btm_ble_enable_resolving_list(BTM_BLE_RL_INIT);
        btm_random_pseudo_to_identity_addr(peer_addr, &peer_addr_type);
    } else {
        btm_ble_disable_resolving_list(BTM_BLE_RL_INIT, TRUE);
    }
    */
#endif

    if (!btm_ble_topology_check(BTM_BLE_STATE_INIT)) {
        l2cu_release_lcb (p_lcb);
        L2CAP_TRACE_ERROR("initate direct connection fail, topology limitation");
        return FALSE;
    }

    if (!btsnd_hcic_ble_create_ll_conn (scan_int,/* UINT16 scan_int      */
                                        scan_win, /* UINT16 scan_win      */
                                        FALSE,                   /* UINT8 white_list     */
                                        peer_addr_type,          /* UINT8 addr_type_peer */
                                        peer_addr,               /* BD_ADDR bda_peer     */
                                        own_addr_type,         /* UINT8 addr_type_own  */
                                        (UINT16) ((p_dev_rec->conn_params.min_conn_int != BTM_BLE_CONN_PARAM_UNDEF) ?
                                                p_dev_rec->conn_params.min_conn_int : BTM_BLE_CONN_INT_MIN_DEF),  /* UINT16 conn_int_min  */
                                        (UINT16) ((p_dev_rec->conn_params.max_conn_int != BTM_BLE_CONN_PARAM_UNDEF) ?
                                                p_dev_rec->conn_params.max_conn_int : BTM_BLE_CONN_INT_MAX_DEF),  /* UINT16 conn_int_max  */
                                        (UINT16) ((p_dev_rec->conn_params.slave_latency != BTM_BLE_CONN_PARAM_UNDEF) ?
                                                p_dev_rec->conn_params.slave_latency : BTM_BLE_CONN_SLAVE_LATENCY_DEF), /* UINT16 conn_latency  */
                                        (UINT16) ((p_dev_rec->conn_params.supervision_tout != BTM_BLE_CONN_PARAM_UNDEF) ?
                                                p_dev_rec->conn_params.supervision_tout : BTM_BLE_CONN_TIMEOUT_DEF), /* conn_timeout */
                                        0,                       /* UINT16 min_len       */
                                        0)) {                    /* UINT16 max_len       */
        l2cu_release_lcb (p_lcb);
        L2CAP_TRACE_ERROR("initate direct connection fail, no resources");
        return (FALSE);
    } else {
        p_lcb->link_state = LST_CONNECTING;
        l2cb.is_ble_connecting = TRUE;
        memcpy (l2cb.ble_connecting_bda, p_lcb->remote_bd_addr, BD_ADDR_LEN);
        btu_start_timer (&p_lcb->timer_entry, BTU_TTYPE_L2CAP_LINK, L2CAP_BLE_LINK_CONNECT_TOUT);
        btm_ble_set_conn_st (BLE_DIR_CONN);

        return (TRUE);
    }
}