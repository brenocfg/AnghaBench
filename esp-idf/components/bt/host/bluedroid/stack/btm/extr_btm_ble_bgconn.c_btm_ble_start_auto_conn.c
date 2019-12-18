#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  own_addr_type; } ;
struct TYPE_8__ {scalar_t__ conn_state; scalar_t__ scan_int; scalar_t__ scan_win; scalar_t__ rl_state; int /*<<< orphan*/  wl_state; TYPE_1__ addr_mgnt_cb; } ;
typedef  TYPE_2__ tBTM_BLE_CB ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_11__ {TYPE_2__ ble_ctr_cb; } ;
struct TYPE_10__ {scalar_t__ (* supports_ble_privacy ) () ;} ;
struct TYPE_9__ {int /*<<< orphan*/  member_0; } ;
typedef  scalar_t__ BOOLEAN ;
typedef  TYPE_3__ BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BLE_ADDR_PUBLIC ; 
 int /*<<< orphan*/  BLE_ADDR_TYPE_ID_BIT ; 
 scalar_t__ BLE_BG_CONN ; 
 scalar_t__ BLE_CONN_CANCEL ; 
 scalar_t__ BLE_CONN_IDLE ; 
 int /*<<< orphan*/  BTM_BLE_CONN_INT_MAX_DEF ; 
 int /*<<< orphan*/  BTM_BLE_CONN_INT_MIN_DEF ; 
 int /*<<< orphan*/  BTM_BLE_CONN_SLAVE_LATENCY_DEF ; 
 int /*<<< orphan*/  BTM_BLE_CONN_TIMEOUT_DEF ; 
 scalar_t__ BTM_BLE_RL_IDLE ; 
 int /*<<< orphan*/  BTM_BLE_RL_INIT ; 
 scalar_t__ BTM_BLE_SCAN_PARAM_UNDEF ; 
 scalar_t__ BTM_BLE_SCAN_SLOW_INT_1 ; 
 scalar_t__ BTM_BLE_SCAN_SLOW_WIN_1 ; 
 int /*<<< orphan*/  BTM_BLE_STATE_INIT ; 
 int /*<<< orphan*/  BTM_BLE_WL_INIT ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*,scalar_t__) ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 scalar_t__ background_connections_pending () ; 
 int /*<<< orphan*/  btm_ble_enable_resolving_list_for_platform (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btm_ble_set_conn_st (scalar_t__) ; 
 scalar_t__ btm_ble_topology_check (int /*<<< orphan*/ ) ; 
 TYPE_6__ btm_cb ; 
 int /*<<< orphan*/  btm_execute_wl_dev_operation () ; 
 int /*<<< orphan*/  btsnd_hcic_ble_create_conn_cancel () ; 
 int /*<<< orphan*/  btsnd_hcic_ble_create_ll_conn (scalar_t__,scalar_t__,int,int /*<<< orphan*/ ,TYPE_3__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* controller_get_interface () ; 
 scalar_t__ stub1 () ; 

BOOLEAN btm_ble_start_auto_conn(BOOLEAN start)
{
    tBTM_BLE_CB *p_cb = &btm_cb.ble_ctr_cb;
    BD_ADDR dummy_bda = {0};
    BOOLEAN exec = TRUE;
    UINT16 scan_int;
    UINT16 scan_win;
    UINT8 own_addr_type = p_cb->addr_mgnt_cb.own_addr_type;
    UINT8 peer_addr_type = BLE_ADDR_PUBLIC;

    if (start) {
        if (p_cb->conn_state == BLE_CONN_IDLE && background_connections_pending()
                && btm_ble_topology_check(BTM_BLE_STATE_INIT)) {
            p_cb->wl_state  |= BTM_BLE_WL_INIT;

            btm_execute_wl_dev_operation();

#if BLE_PRIVACY_SPT == TRUE
            btm_ble_enable_resolving_list_for_platform(BTM_BLE_RL_INIT);
#endif
            scan_int = (p_cb->scan_int == BTM_BLE_SCAN_PARAM_UNDEF) ?
                       BTM_BLE_SCAN_SLOW_INT_1 : p_cb->scan_int;
            scan_win = (p_cb->scan_win == BTM_BLE_SCAN_PARAM_UNDEF) ?
                       BTM_BLE_SCAN_SLOW_WIN_1 : p_cb->scan_win;

#if BLE_PRIVACY_SPT == TRUE
            if (btm_cb.ble_ctr_cb.rl_state != BTM_BLE_RL_IDLE
                    && controller_get_interface()->supports_ble_privacy()) {
                own_addr_type |= BLE_ADDR_TYPE_ID_BIT;
                peer_addr_type |= BLE_ADDR_TYPE_ID_BIT;
            }
#endif

            if (!btsnd_hcic_ble_create_ll_conn (scan_int,  /* UINT16 scan_int      */
                                                scan_win,    /* UINT16 scan_win      */
                                                0x01,                   /* UINT8 white_list     */
                                                peer_addr_type,        /* UINT8 addr_type_peer */
                                                dummy_bda,              /* BD_ADDR bda_peer     */
                                                own_addr_type,          /* UINT8 addr_type_own */
                                                BTM_BLE_CONN_INT_MIN_DEF,   /* UINT16 conn_int_min  */
                                                BTM_BLE_CONN_INT_MAX_DEF,   /* UINT16 conn_int_max  */
                                                BTM_BLE_CONN_SLAVE_LATENCY_DEF,  /* UINT16 conn_latency  */
                                                BTM_BLE_CONN_TIMEOUT_DEF,        /* UINT16 conn_timeout  */
                                                0,                       /* UINT16 min_len       */
                                                0)) {                    /* UINT16 max_len       */
                /* start auto connection failed */
                exec =  FALSE;
                p_cb->wl_state &= ~BTM_BLE_WL_INIT;
            } else {
                btm_ble_set_conn_st (BLE_BG_CONN);
            }
        } else {
            exec = FALSE;
        }
    } else {
        if (p_cb->conn_state == BLE_BG_CONN) {
            btsnd_hcic_ble_create_conn_cancel();
            btm_ble_set_conn_st (BLE_CONN_CANCEL);
            p_cb->wl_state &= ~BTM_BLE_WL_INIT;
        } else {
            BTM_TRACE_DEBUG("conn_st = %d, not in auto conn state, cannot stop", p_cb->conn_state);
            exec = FALSE;
        }
    }
    return exec;
}