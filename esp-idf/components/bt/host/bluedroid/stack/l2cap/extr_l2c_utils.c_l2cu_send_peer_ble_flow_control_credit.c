#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ id; } ;
typedef  TYPE_1__ tL2C_LCB ;
struct TYPE_8__ {int /*<<< orphan*/  local_cid; TYPE_1__* p_lcb; scalar_t__ local_id; } ;
typedef  TYPE_2__ tL2C_CCB ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;
typedef  int /*<<< orphan*/  BT_HDR ;

/* Variables and functions */
 int HCI_DATA_PREAMBLE_SIZE ; 
 int /*<<< orphan*/  L2CAP_ADJ_ID ; 
 int /*<<< orphan*/  L2CAP_CMD_BLE_FLOW_CTRL_CREDIT ; 
 int /*<<< orphan*/  L2CAP_CMD_BLE_FLOW_CTRL_CREDIT_LEN ; 
 int L2CAP_CMD_OVERHEAD ; 
 int L2CAP_PKT_OVERHEAD ; 
 int L2CAP_SEND_CMD_OFFSET ; 
 int /*<<< orphan*/  L2CAP_TRACE_WARNING (char*) ; 
 int /*<<< orphan*/  UINT16_TO_STREAM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2c_link_check_send_pkts (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2cu_adj_id (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * l2cu_build_header (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

void l2cu_send_peer_ble_flow_control_credit(tL2C_CCB *p_ccb, UINT16 credit_value)
{
    BT_HDR  *p_buf;
    UINT8   *p;
    tL2C_LCB *p_lcb = NULL;

    if (!p_ccb) {
        return;
    }
    p_lcb = p_ccb->p_lcb;

    /* Create an identifier for this packet */
    p_ccb->p_lcb->id++;
    l2cu_adj_id(p_ccb->p_lcb, L2CAP_ADJ_ID);

    p_ccb->local_id = p_ccb->p_lcb->id;

    if ((p_buf = l2cu_build_header (p_lcb, L2CAP_CMD_BLE_FLOW_CTRL_CREDIT_LEN,
                    L2CAP_CMD_BLE_FLOW_CTRL_CREDIT, p_lcb->id)) == NULL )
    {
        L2CAP_TRACE_WARNING ("l2cu_send_peer_ble_credit_based_conn_req - no buffer");
        return;
    }

    p = (UINT8 *)(p_buf + 1) + L2CAP_SEND_CMD_OFFSET + HCI_DATA_PREAMBLE_SIZE +
                               L2CAP_PKT_OVERHEAD + L2CAP_CMD_OVERHEAD;

    UINT16_TO_STREAM (p, p_ccb->local_cid);
    UINT16_TO_STREAM (p, credit_value);

    l2c_link_check_send_pkts (p_lcb, NULL, p_buf);
}