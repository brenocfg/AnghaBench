#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ transport; int conn_update_mask; int /*<<< orphan*/  upda_con_timer; void* waiting_update_conn_timeout; void* waiting_update_conn_latency; void* waiting_update_conn_max_interval; void* waiting_update_conn_min_interval; int /*<<< orphan*/  remote_bd_addr; int /*<<< orphan*/  current_used_conn_timeout; int /*<<< orphan*/  current_used_conn_latency; int /*<<< orphan*/  current_used_conn_interval; } ;
typedef  TYPE_1__ tL2C_LCB ;
struct TYPE_9__ {int /*<<< orphan*/  supervision_tout; int /*<<< orphan*/  slave_latency; int /*<<< orphan*/  conn_int; void* min_conn_int; void* max_conn_int; } ;
typedef  TYPE_2__ tBTM_LE_UPDATE_CONN_PRAMS ;
typedef  int /*<<< orphan*/  tACL_CONN ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT32 ;
typedef  void* UINT16 ;
struct TYPE_10__ {int /*<<< orphan*/  (* update_conn_param_cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ;} ;
typedef  scalar_t__ BOOLEAN ;
typedef  int* BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTU_TTYPE_L2CAP_UPDA_CONN_PARAMS ; 
 scalar_t__ BT_TRANSPORT_LE ; 
 int /*<<< orphan*/  CalConnectParamTimeout (TYPE_1__*) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  HCI_ERR_ILLEGAL_COMMAND ; 
 int /*<<< orphan*/  L2CAP_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  L2CAP_TRACE_WARNING (char*,int,int) ; 
 int L2C_BLE_NEW_CONN_PARAM ; 
 int L2C_BLE_UPDATE_PARAM_FULL ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/ * btm_bda_to_acl (int*,scalar_t__) ; 
 int /*<<< orphan*/  btu_start_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__ conn_param_update_cb ; 
 scalar_t__ l2cble_start_conn_update (TYPE_1__*) ; 
 TYPE_1__* l2cu_find_lcb_by_bd_addr (int*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 

BOOLEAN L2CA_UpdateBleConnParams (BD_ADDR rem_bda, UINT16 min_int, UINT16 max_int,
                                  UINT16 latency, UINT16 timeout)
{
    tL2C_LCB            *p_lcb;
    tACL_CONN           *p_acl_cb = btm_bda_to_acl(rem_bda, BT_TRANSPORT_LE);

    /* See if we have a link control block for the remote device */
    p_lcb = l2cu_find_lcb_by_bd_addr (rem_bda, BT_TRANSPORT_LE);

    /* If we don't have one, create one and accept the connection. */
    if (!p_lcb || !p_acl_cb) {
        L2CAP_TRACE_WARNING ("L2CA_UpdateBleConnParams - unknown BD_ADDR %08x%04x",
                             (rem_bda[0] << 24) + (rem_bda[1] << 16) + (rem_bda[2] << 8) + rem_bda[3],
                             (rem_bda[4] << 8) + rem_bda[5]);
        return (FALSE);
    }

    if (p_lcb->transport != BT_TRANSPORT_LE) {
        L2CAP_TRACE_WARNING ("L2CA_UpdateBleConnParams - BD_ADDR %08x%04x not LE",
                             (rem_bda[0] << 24) + (rem_bda[1] << 16) + (rem_bda[2] << 8) + rem_bda[3],
                             (rem_bda[4] << 8) + rem_bda[5]);
        return (FALSE);
    }

    if (p_lcb->conn_update_mask & L2C_BLE_UPDATE_PARAM_FULL){
        UINT8 status = HCI_ERR_ILLEGAL_COMMAND;
        L2CAP_TRACE_ERROR("There are two connection parameter requests that are being updated, please try later ");
        if (conn_param_update_cb.update_conn_param_cb != NULL) {
            tBTM_LE_UPDATE_CONN_PRAMS update_param;
            update_param.max_conn_int = max_int;
            update_param.min_conn_int = min_int;
            update_param.conn_int = p_lcb->current_used_conn_interval;
            update_param.slave_latency = p_lcb->current_used_conn_latency;
            update_param.supervision_tout = p_lcb->current_used_conn_timeout;
            (conn_param_update_cb.update_conn_param_cb)(status, p_lcb->remote_bd_addr, &update_param);
        }
        return (FALSE);
    }

    p_lcb->waiting_update_conn_min_interval = min_int;
    p_lcb->waiting_update_conn_max_interval = max_int;
    p_lcb->waiting_update_conn_latency = latency;
    p_lcb->waiting_update_conn_timeout = timeout;
    p_lcb->conn_update_mask |= L2C_BLE_NEW_CONN_PARAM;

    if(l2cble_start_conn_update(p_lcb) == TRUE) {
        UINT32 time = CalConnectParamTimeout(p_lcb);
        btu_start_timer(&p_lcb->upda_con_timer, BTU_TTYPE_L2CAP_UPDA_CONN_PARAMS, time);
    }

    return (TRUE);
}