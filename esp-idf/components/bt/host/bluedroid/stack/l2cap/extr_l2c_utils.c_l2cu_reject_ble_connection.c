#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  tL2C_LCB ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;
typedef  int /*<<< orphan*/  BT_HDR ;

/* Variables and functions */
 int HCI_DATA_PREAMBLE_SIZE ; 
 int /*<<< orphan*/  L2CAP_CMD_BLE_CREDIT_BASED_CONN_RES ; 
 int /*<<< orphan*/  L2CAP_CMD_BLE_CREDIT_BASED_CONN_RES_LEN ; 
 int L2CAP_CMD_OVERHEAD ; 
 int L2CAP_PKT_OVERHEAD ; 
 int L2CAP_SEND_CMD_OFFSET ; 
 int /*<<< orphan*/  L2CAP_TRACE_WARNING (char*) ; 
 int /*<<< orphan*/  UINT16_TO_STREAM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2c_link_check_send_pkts (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * l2cu_build_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void l2cu_reject_ble_connection (tL2C_LCB *p_lcb, UINT8 rem_id, UINT16 result)
{
    BT_HDR  *p_buf;
    UINT8   *p;

    if ((p_buf = l2cu_build_header(p_lcb, L2CAP_CMD_BLE_CREDIT_BASED_CONN_RES_LEN,
                    L2CAP_CMD_BLE_CREDIT_BASED_CONN_RES, rem_id)) == NULL )
    {
        L2CAP_TRACE_WARNING ("l2cu_reject_ble_connection - no buffer");
        return;
    }

    p = (UINT8 *)(p_buf + 1) + L2CAP_SEND_CMD_OFFSET + HCI_DATA_PREAMBLE_SIZE +
                               L2CAP_PKT_OVERHEAD + L2CAP_CMD_OVERHEAD;

    UINT16_TO_STREAM (p, 0);                    /* Local CID of 0   */
    UINT16_TO_STREAM (p, 0);                    /* MTU */
    UINT16_TO_STREAM (p, 0);                    /* MPS */
    UINT16_TO_STREAM (p, 0);                    /* initial credit */
    UINT16_TO_STREAM (p, result);

    l2c_link_check_send_pkts (p_lcb, NULL, p_buf);
}