#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ link_state; int /*<<< orphan*/  timer_entry; int /*<<< orphan*/ * p_echo_rsp_cb; } ;
typedef  TYPE_1__ tL2C_LCB ;
typedef  int /*<<< orphan*/  tL2CA_ECHO_RSP_CB ;
typedef  scalar_t__ BOOLEAN ;
typedef  int /*<<< orphan*/ * BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_IsDeviceUp () ; 
 int /*<<< orphan*/  BTU_TTYPE_L2CAP_LINK ; 
 int /*<<< orphan*/  BT_TRANSPORT_BR_EDR ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  L2CAP_ADJ_BRCM_ID ; 
 int /*<<< orphan*/  L2CAP_ECHO_RSP_TOUT ; 
 int /*<<< orphan*/  L2CAP_TRACE_API (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L2CAP_TRACE_WARNING (char*) ; 
 scalar_t__ LST_CONNECTED ; 
 scalar_t__ LST_DISCONNECTING ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  btu_start_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cu_adj_id (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* l2cu_allocate_lcb (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ l2cu_create_conn (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* l2cu_find_lcb_by_bd_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cu_send_peer_echo_req (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

BOOLEAN  L2CA_Ping (BD_ADDR p_bd_addr, tL2CA_ECHO_RSP_CB *p_callback)
{
    tL2C_LCB        *p_lcb;

    L2CAP_TRACE_API ("L2CA_Ping()  BDA: %02x-%02x-%02x-%02x-%02x-%02x",
                     p_bd_addr[0], p_bd_addr[1], p_bd_addr[2], p_bd_addr[3], p_bd_addr[4], p_bd_addr[5]);

    /* Fail if we have not established communications with the controller */
    if (!BTM_IsDeviceUp()) {
        return (FALSE);
    }

    /* First, see if we already have a link to the remote */
    if ((p_lcb = l2cu_find_lcb_by_bd_addr (p_bd_addr, BT_TRANSPORT_BR_EDR)) == NULL) {
        /* No link. Get an LCB and start link establishment */
        if ((p_lcb = l2cu_allocate_lcb (p_bd_addr, FALSE, BT_TRANSPORT_BR_EDR)) == NULL) {
            L2CAP_TRACE_WARNING ("L2CAP - no LCB for L2CA_ping");
            return (FALSE);
        }
        if (l2cu_create_conn(p_lcb, BT_TRANSPORT_BR_EDR) == FALSE) {
            return (FALSE);
        }

        p_lcb->p_echo_rsp_cb = p_callback;

        return (TRUE);
    }

    /* We only allow 1 ping outstanding at a time */
    if (p_lcb->p_echo_rsp_cb != NULL) {
        L2CAP_TRACE_WARNING ("L2CAP - rejected second L2CA_ping");
        return (FALSE);
    }

    /* Have a link control block. If link is disconnecting, tell user to retry later */
    if (p_lcb->link_state == LST_DISCONNECTING) {
        L2CAP_TRACE_WARNING ("L2CAP - L2CA_ping rejected - link disconnecting");
        return (FALSE);
    }

    /* Save address of callback */
    p_lcb->p_echo_rsp_cb = p_callback;

    if (p_lcb->link_state == LST_CONNECTED) {
        l2cu_adj_id(p_lcb, L2CAP_ADJ_BRCM_ID);  /* Make sure not using Broadcom ID */
        l2cu_send_peer_echo_req (p_lcb, NULL, 0);
        btu_start_timer (&p_lcb->timer_entry, BTU_TTYPE_L2CAP_LINK, L2CAP_ECHO_RSP_TOUT);
    }

    return (TRUE);
}