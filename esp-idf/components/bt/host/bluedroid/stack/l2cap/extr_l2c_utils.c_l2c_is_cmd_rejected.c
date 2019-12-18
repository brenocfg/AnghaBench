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
typedef  int UINT8 ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
#define  L2CAP_CMD_AMP_CONN_REQ 135 
#define  L2CAP_CMD_AMP_MOVE_REQ 134 
#define  L2CAP_CMD_BLE_UPDATE_REQ 133 
#define  L2CAP_CMD_CONFIG_REQ 132 
#define  L2CAP_CMD_CONN_REQ 131 
#define  L2CAP_CMD_DISC_REQ 130 
#define  L2CAP_CMD_ECHO_REQ 129 
#define  L2CAP_CMD_INFO_REQ 128 
 int /*<<< orphan*/  L2CAP_CMD_REJ_MTU_EXCEEDED ; 
 int /*<<< orphan*/  L2CAP_DEFAULT_MTU ; 
 int /*<<< orphan*/  L2CAP_TRACE_WARNING (char*,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  l2cu_send_peer_cmd_reject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BOOLEAN l2c_is_cmd_rejected (UINT8 cmd_code, UINT8 id, tL2C_LCB *p_lcb)
{
    switch (cmd_code) {
    case L2CAP_CMD_CONN_REQ:
    case L2CAP_CMD_CONFIG_REQ:
    case L2CAP_CMD_DISC_REQ:
    case L2CAP_CMD_ECHO_REQ:
    case L2CAP_CMD_INFO_REQ:
    case L2CAP_CMD_AMP_CONN_REQ:
    case L2CAP_CMD_AMP_MOVE_REQ:
    case L2CAP_CMD_BLE_UPDATE_REQ:
        l2cu_send_peer_cmd_reject (p_lcb, L2CAP_CMD_REJ_MTU_EXCEEDED, id, L2CAP_DEFAULT_MTU, 0);
        L2CAP_TRACE_WARNING ("Dumping first Command (%d)", cmd_code);
        return TRUE;

    default:    /* Otherwise a response */
        return FALSE;
    }
}