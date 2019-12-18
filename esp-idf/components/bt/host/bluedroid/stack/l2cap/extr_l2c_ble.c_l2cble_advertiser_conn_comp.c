#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_14__ {int updating_param_flag; int* peer_chnl_mask; int /*<<< orphan*/  link_state; int /*<<< orphan*/  link_role; int /*<<< orphan*/  conn_update_mask; void* current_used_conn_latency; void* waiting_update_conn_latency; void* current_used_conn_timeout; void* waiting_update_conn_timeout; void* current_used_conn_interval; void* waiting_update_conn_max_interval; void* waiting_update_conn_min_interval; int /*<<< orphan*/  transport; void* handle; } ;
typedef  TYPE_2__ tL2C_LCB ;
struct TYPE_15__ {int /*<<< orphan*/  sec_bd_name; } ;
typedef  TYPE_3__ tBTM_SEC_DEV_REC ;
typedef  void* tBLE_ADDR_TYPE ;
typedef  void* UINT16 ;
struct TYPE_17__ {int /*<<< orphan*/  ble_connecting_bda; scalar_t__ is_ble_connecting; TYPE_1__* fixed_reg; } ;
struct TYPE_16__ {int /*<<< orphan*/  as_array; } ;
struct TYPE_13__ {int /*<<< orphan*/  fixed_chnl_opts; } ;
struct TYPE_12__ {TYPE_4__* (* get_features_ble ) () ;} ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 int /*<<< orphan*/  BTM_BLE_RL_ADV ; 
 int /*<<< orphan*/  BT_TRANSPORT_LE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HCI_ERR_NO_CONNECTION ; 
 int /*<<< orphan*/  HCI_LE_SLAVE_INIT_FEAT_EXC_SUPPORTED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_ROLE_SLAVE ; 
 size_t L2CAP_ATT_CID ; 
 size_t L2CAP_FIRST_FIXED_CHNL ; 
 int L2CAP_FIXED_CHNL_ATT_BIT ; 
 int L2CAP_FIXED_CHNL_BLE_SIG_BIT ; 
 int L2CAP_FIXED_CHNL_SMP_BIT ; 
 int /*<<< orphan*/  L2CAP_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  L2CAP_TRACE_WARNING (char*) ; 
 int /*<<< orphan*/  L2CA_CancelBleConnectReq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L2C_BLE_NOT_DEFAULT_PARAM ; 
 int /*<<< orphan*/  LST_CONNECTED ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UNUSED (void*) ; 
 int /*<<< orphan*/  btm_acl_created (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btm_ble_disable_resolving_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* btm_find_or_alloc_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btm_sec_disconnect (void*,int /*<<< orphan*/ ) ; 
 TYPE_10__* controller_get_interface () ; 
 TYPE_9__ l2cb ; 
 TYPE_2__* l2cu_allocate_lcb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* l2cu_find_lcb_by_bd_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cu_initialize_fixed_ccb (TYPE_2__*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2cu_process_fixed_chnl_resp (TYPE_2__*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* stub1 () ; 

void l2cble_advertiser_conn_comp (UINT16 handle, BD_ADDR bda, tBLE_ADDR_TYPE type,
                                  UINT16 conn_interval, UINT16 conn_latency, UINT16 conn_timeout)
{
    tL2C_LCB            *p_lcb;
    tBTM_SEC_DEV_REC    *p_dev_rec;
    UNUSED(type);
    UNUSED(conn_interval);
    UNUSED(conn_latency);
    UNUSED(conn_timeout);

    /* See if we have a link control block for the remote device */
    p_lcb = l2cu_find_lcb_by_bd_addr (bda, BT_TRANSPORT_LE);

    /* If we don't have one, create one and accept the connection. */
    if (!p_lcb) {
        p_lcb = l2cu_allocate_lcb (bda, FALSE, BT_TRANSPORT_LE);
        if (!p_lcb) {
#if (SMP_INCLUDED == TRUE)
            btm_sec_disconnect (handle, HCI_ERR_NO_CONNECTION);
#endif  ///SMP_INCLUDED == TRUE
            L2CAP_TRACE_ERROR ("l2cble_advertiser_conn_comp - failed to allocate LCB");
            return;
        } else {
            if (!l2cu_initialize_fixed_ccb (p_lcb, L2CAP_ATT_CID, &l2cb.fixed_reg[L2CAP_ATT_CID - L2CAP_FIRST_FIXED_CHNL].fixed_chnl_opts)) {
#if (SMP_INCLUDED == TRUE)
                btm_sec_disconnect (handle, HCI_ERR_NO_CONNECTION);
#endif  ///SMP_INCLUDED == TRUE
                L2CAP_TRACE_WARNING ("l2cble_scanner_conn_comp - LCB but no CCB");
                return ;
            }
        }
    }

    /* Save the handle */
    p_lcb->handle = handle;

    /* Connected OK. Change state to connected, we were advertising, so we are slave */
    p_lcb->link_role  = HCI_ROLE_SLAVE;
    p_lcb->transport  = BT_TRANSPORT_LE;

    /* update link parameter, set slave link as non-spec default upon link up */
    p_lcb->waiting_update_conn_min_interval = p_lcb->waiting_update_conn_max_interval = p_lcb->current_used_conn_interval = conn_interval;
    p_lcb->waiting_update_conn_timeout      =  p_lcb->current_used_conn_timeout = conn_timeout;
    p_lcb->waiting_update_conn_latency      =  p_lcb->current_used_conn_latency = conn_latency;
    p_lcb->conn_update_mask = L2C_BLE_NOT_DEFAULT_PARAM;
    p_lcb->updating_param_flag = false;

    /* Tell BTM Acl management about the link */
    p_dev_rec = btm_find_or_alloc_dev (bda);

    btm_acl_created (bda, NULL, p_dev_rec->sec_bd_name, handle, p_lcb->link_role, BT_TRANSPORT_LE);

#if BLE_PRIVACY_SPT == TRUE
    btm_ble_disable_resolving_list(BTM_BLE_RL_ADV, TRUE);
#endif

    p_lcb->peer_chnl_mask[0] = L2CAP_FIXED_CHNL_ATT_BIT | L2CAP_FIXED_CHNL_BLE_SIG_BIT | L2CAP_FIXED_CHNL_SMP_BIT;

    if (!HCI_LE_SLAVE_INIT_FEAT_EXC_SUPPORTED(controller_get_interface()->get_features_ble()->as_array)) {
        p_lcb->link_state = LST_CONNECTED;
        l2cu_process_fixed_chnl_resp (p_lcb);
    }

    /* when adv and initiating are both active, cancel the direct connection */
    if (l2cb.is_ble_connecting && memcmp(bda, l2cb.ble_connecting_bda, BD_ADDR_LEN) == 0) {
        L2CA_CancelBleConnectReq(bda);
    }
}