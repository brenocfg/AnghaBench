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
typedef  int UINT16 ;
typedef  int /*<<< orphan*/  BT_HDR ;

/* Variables and functions */
 int HCI_DATA_PREAMBLE_SIZE ; 
 int L2CAP_CMD_OVERHEAD ; 
 int /*<<< orphan*/  L2CAP_CMD_REJECT ; 
 scalar_t__ L2CAP_CMD_REJECT_LEN ; 
 int L2CAP_CMD_REJ_INVALID_CID ; 
 int L2CAP_CMD_REJ_MTU_EXCEEDED ; 
 int L2CAP_PKT_OVERHEAD ; 
 int L2CAP_SEND_CMD_OFFSET ; 
 int /*<<< orphan*/  L2CAP_TRACE_WARNING (char*) ; 
 int /*<<< orphan*/  UINT16_TO_STREAM (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  l2c_link_check_send_pkts (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * l2cu_build_header (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void l2cu_send_peer_cmd_reject (tL2C_LCB *p_lcb, UINT16 reason, UINT8 rem_id,
                                UINT16 p1, UINT16 p2)
{
    UINT16  param_len;
    BT_HDR  *p_buf;
    UINT8   *p;

    /* Put in L2CAP packet header */
    if (reason == L2CAP_CMD_REJ_MTU_EXCEEDED) {
        param_len = 2;
    } else if (reason == L2CAP_CMD_REJ_INVALID_CID) {
        param_len = 4;
    } else {
        param_len = 0;
    }

    if ((p_buf = l2cu_build_header (p_lcb, (UINT16) (L2CAP_CMD_REJECT_LEN + param_len), L2CAP_CMD_REJECT, rem_id)) == NULL ) {
        L2CAP_TRACE_WARNING ("L2CAP - no buffer cmd_rej");
        return;
    }

    p = (UINT8 *)(p_buf + 1) + L2CAP_SEND_CMD_OFFSET + HCI_DATA_PREAMBLE_SIZE +
        L2CAP_PKT_OVERHEAD + L2CAP_CMD_OVERHEAD;

    UINT16_TO_STREAM (p, reason);

    if (param_len >= 2) {
        UINT16_TO_STREAM (p, p1);
    }

    if (param_len >= 4) {
        UINT16_TO_STREAM (p, p2);
    }

    l2c_link_check_send_pkts (p_lcb, NULL, p_buf);
}