#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int waiting_update_conn_min_interval; int waiting_update_conn_max_interval; int waiting_update_conn_latency; int waiting_update_conn_timeout; int /*<<< orphan*/  conn_update_mask; int /*<<< orphan*/  upda_con_timer; int /*<<< orphan*/  link_role; } ;
typedef  TYPE_1__ tL2C_LCB ;
typedef  int UINT8 ;
typedef  int /*<<< orphan*/  UINT32 ;
typedef  int UINT16 ;

/* Variables and functions */
 int BTM_BLE_CONN_INT_MAX ; 
 int BTM_BLE_CONN_INT_MIN ; 
 int BTM_BLE_CONN_LATENCY_MAX ; 
 int BTM_BLE_CONN_SUP_TOUT_MAX ; 
 int BTM_BLE_CONN_SUP_TOUT_MIN ; 
 int /*<<< orphan*/  BTU_TTYPE_L2CAP_UPDA_CONN_PARAMS ; 
 int /*<<< orphan*/  CalConnectParamTimeout (TYPE_1__*) ; 
 int HCI_ERR_PARAM_OUT_OF_RANGE ; 
 int /*<<< orphan*/  HCI_ROLE_MASTER ; 
 int HCI_SUCCESS ; 
 int /*<<< orphan*/  L2CAP_CFG_OK ; 
 int /*<<< orphan*/  L2CAP_CFG_UNACCEPTABLE_PARAMS ; 
#define  L2CAP_CMD_BLE_UPDATE_REQ 134 
#define  L2CAP_CMD_BLE_UPDATE_RSP 133 
#define  L2CAP_CMD_ECHO_REQ 132 
#define  L2CAP_CMD_ECHO_RSP 131 
#define  L2CAP_CMD_INFO_REQ 130 
#define  L2CAP_CMD_INFO_RSP 129 
#define  L2CAP_CMD_REJECT 128 
 int /*<<< orphan*/  L2CAP_CMD_REJ_NOT_UNDERSTOOD ; 
 int /*<<< orphan*/  L2CAP_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  L2CAP_TRACE_WARNING (char*,int,...) ; 
 int /*<<< orphan*/  L2C_BLE_NEW_CONN_PARAM ; 
 int /*<<< orphan*/  L2C_BLE_UPDATE_PARAM_FULL ; 
 int /*<<< orphan*/  L2C_BLE_UPDATE_PENDING ; 
 int /*<<< orphan*/  STREAM_TO_UINT16 (int,int*) ; 
 int /*<<< orphan*/  STREAM_TO_UINT8 (int,int*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  btu_start_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btu_stop_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2c_send_update_conn_params_cb (TYPE_1__*,int) ; 
 int /*<<< orphan*/  l2cble_start_conn_update (TYPE_1__*) ; 
 int /*<<< orphan*/  l2cu_send_peer_ble_par_rsp (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  l2cu_send_peer_cmd_reject (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void l2cble_process_sig_cmd (tL2C_LCB *p_lcb, UINT8 *p, UINT16 pkt_len)
{
    UINT8           *p_pkt_end;
    UINT8           cmd_code, id;
    UINT16          cmd_len;
    UINT16          min_interval, max_interval, latency, timeout;

    p_pkt_end = p + pkt_len;

    STREAM_TO_UINT8  (cmd_code, p);
    STREAM_TO_UINT8  (id, p);
    STREAM_TO_UINT16 (cmd_len, p);

    /* Check command length does not exceed packet length */
    if ((p + cmd_len) > p_pkt_end) {
        L2CAP_TRACE_WARNING ("L2CAP - LE - format error, pkt_len: %d  cmd_len: %d  code: %d", pkt_len, cmd_len, cmd_code);
        return;
    }

    switch (cmd_code) {
    case L2CAP_CMD_REJECT:
    case L2CAP_CMD_ECHO_RSP:
    case L2CAP_CMD_INFO_RSP:
        p += 2;
        break;
    case L2CAP_CMD_ECHO_REQ:
    case L2CAP_CMD_INFO_REQ:
        l2cu_send_peer_cmd_reject (p_lcb, L2CAP_CMD_REJ_NOT_UNDERSTOOD, id, 0, 0);
        break;

    case L2CAP_CMD_BLE_UPDATE_REQ:
        STREAM_TO_UINT16 (min_interval, p); /* 0x0006 - 0x0C80 */
        STREAM_TO_UINT16 (max_interval, p); /* 0x0006 - 0x0C80 */
        STREAM_TO_UINT16 (latency, p);  /* 0x0000 - 0x03E8 */
        STREAM_TO_UINT16 (timeout, p);  /* 0x000A - 0x0C80 */
        /* If we are a master, the slave wants to update the parameters */
        if (p_lcb->link_role == HCI_ROLE_MASTER) {
            if (min_interval < BTM_BLE_CONN_INT_MIN || min_interval > BTM_BLE_CONN_INT_MAX ||
                    max_interval < BTM_BLE_CONN_INT_MIN || max_interval > BTM_BLE_CONN_INT_MAX ||
                    latency  > BTM_BLE_CONN_LATENCY_MAX ||
                    timeout < BTM_BLE_CONN_SUP_TOUT_MIN || timeout > BTM_BLE_CONN_SUP_TOUT_MAX ||
                    /* The supervision_timeout parameter defines the link supervision timeout for the connection.
                       The supervision_timeout in milliseconds shall be large than (1 + latency) * max_interval * 2,
                       where max_interval is given in milliseconds. (See [Vol 6] Part B, Section 4.5.2).
                       supervision_timeout (mult of 10ms); conn_interval (mult of 1.25ms)
                       (max_interval * 1.25 * 2) replaced by ((max_interval * 5) >> 1).
                    */
                    ((timeout * 10) < ((1 + latency) *((max_interval * 5) >> 1))) ||
                    max_interval < min_interval) {
                l2cu_send_peer_ble_par_rsp (p_lcb, L2CAP_CFG_UNACCEPTABLE_PARAMS, id);

                L2CAP_TRACE_ERROR("slave connection parameters update failed, the parameters are out of range");

            } else {

                l2cu_send_peer_ble_par_rsp (p_lcb, L2CAP_CFG_OK, id);
                p_lcb->waiting_update_conn_min_interval = min_interval;
                p_lcb->waiting_update_conn_max_interval = max_interval;
                p_lcb->waiting_update_conn_latency = latency;
                p_lcb->waiting_update_conn_timeout = timeout;
                p_lcb->conn_update_mask |= L2C_BLE_NEW_CONN_PARAM;

                if (l2cble_start_conn_update(p_lcb) == TRUE) {
                    UINT32 time = CalConnectParamTimeout(p_lcb);
                    btu_start_timer(&p_lcb->upda_con_timer, BTU_TTYPE_L2CAP_UPDA_CONN_PARAMS, time);
                }
            }
        } else {
            l2cu_send_peer_cmd_reject (p_lcb, L2CAP_CMD_REJ_NOT_UNDERSTOOD, id, 0, 0);
        }
        break;

    case L2CAP_CMD_BLE_UPDATE_RSP: {
        UINT16 result = 0;
        STREAM_TO_UINT16(result, p); //result = 0 connection param accepted, result = 1 connection param rejected.
        UINT8 status = (result == 0) ? HCI_SUCCESS : HCI_ERR_PARAM_OUT_OF_RANGE;
        if (status != HCI_SUCCESS) {
            btu_stop_timer(&p_lcb->upda_con_timer);
            p_lcb->conn_update_mask &= ~L2C_BLE_UPDATE_PENDING;
            p_lcb->conn_update_mask &= ~L2C_BLE_UPDATE_PARAM_FULL;
            l2c_send_update_conn_params_cb(p_lcb, status);
        }
        break;
    }
    default:
        L2CAP_TRACE_WARNING ("L2CAP - LE - unknown cmd code: %d", cmd_code);
        l2cu_send_peer_cmd_reject (p_lcb, L2CAP_CMD_REJ_NOT_UNDERSTOOD, id, 0, 0);
        return;
    }
}