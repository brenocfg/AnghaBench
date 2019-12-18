#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ link_state; void* link_role; int /*<<< orphan*/  timer_entry; scalar_t__ in_use; } ;
typedef  TYPE_1__ tL2C_LCB ;
struct TYPE_7__ {TYPE_1__* lcb_pool; } ;
typedef  scalar_t__ BOOLEAN ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTU_TTYPE_L2CAP_LINK ; 
 int /*<<< orphan*/  BT_TRANSPORT_BR_EDR ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  HCI_ERR_CONNECTION_EXISTS ; 
 int /*<<< orphan*/  HCI_ERR_HOST_REJECT_DEVICE ; 
 int /*<<< orphan*/  HCI_ERR_HOST_REJECT_RESOURCES ; 
 void* HCI_ROLE_MASTER ; 
 void* HCI_ROLE_SLAVE ; 
 int /*<<< orphan*/  L2CAP_LINK_CONNECT_TOUT ; 
 int /*<<< orphan*/  L2CAP_TRACE_ERROR (char*,...) ; 
 scalar_t__ LST_CONNECTING ; 
 scalar_t__ LST_CONNECT_HOLDING ; 
 scalar_t__ LST_DISCONNECTING ; 
 int MAX_L2CAP_LINKS ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  btm_dev_support_switch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btsnd_hcic_accept_conn (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  btsnd_hcic_reject_conn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btu_start_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__ l2cb ; 
 TYPE_1__* l2cu_allocate_lcb (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__* l2cu_find_lcb_by_bd_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* l2cu_get_conn_role (TYPE_1__*) ; 

BOOLEAN l2c_link_hci_conn_req (BD_ADDR bd_addr)
{
    tL2C_LCB        *p_lcb;
    tL2C_LCB        *p_lcb_cur;
    int             xx;
    BOOLEAN         no_links;

    /* See if we have a link control block for the remote device */
    p_lcb = l2cu_find_lcb_by_bd_addr (bd_addr, BT_TRANSPORT_BR_EDR);

    /* If we don't have one, create one and accept the connection. */
    if (!p_lcb) {
        p_lcb = l2cu_allocate_lcb (bd_addr, FALSE, BT_TRANSPORT_BR_EDR);
        if (!p_lcb) {
            btsnd_hcic_reject_conn (bd_addr, HCI_ERR_HOST_REJECT_RESOURCES);
            L2CAP_TRACE_ERROR ("L2CAP failed to allocate LCB");
            return FALSE;
        }

        no_links = TRUE;

        /* If we already have connection, accept as a master */
        for (xx = 0, p_lcb_cur = &l2cb.lcb_pool[0]; xx < MAX_L2CAP_LINKS; xx++, p_lcb_cur++) {
            if (p_lcb_cur == p_lcb) {
                continue;
            }

            if (p_lcb_cur->in_use) {
                no_links = FALSE;
                p_lcb->link_role = HCI_ROLE_MASTER;
                break;
            }
        }

        if (no_links) {
            if (!btm_dev_support_switch (bd_addr)) {
                p_lcb->link_role = HCI_ROLE_SLAVE;
            } else {
                p_lcb->link_role = l2cu_get_conn_role(p_lcb);
            }
        }

        //counter_add("l2cap.conn.accept", 1);

        /* Tell the other side we accept the connection */
        btsnd_hcic_accept_conn (bd_addr, p_lcb->link_role);

        p_lcb->link_state = LST_CONNECTING;

        /* Start a timer waiting for connect complete */
        btu_start_timer (&p_lcb->timer_entry, BTU_TTYPE_L2CAP_LINK, L2CAP_LINK_CONNECT_TOUT);
        return (TRUE);
    }

    /* We already had a link control block to the guy. Check what state it is in */
    if ((p_lcb->link_state == LST_CONNECTING) || (p_lcb->link_state == LST_CONNECT_HOLDING)) {
        /* Connection collision. Accept the connection anyways. */

        if (!btm_dev_support_switch (bd_addr)) {
            p_lcb->link_role = HCI_ROLE_SLAVE;
        } else {
            p_lcb->link_role = l2cu_get_conn_role(p_lcb);
        }

        //counter_add("l2cap.conn.accept", 1);
        btsnd_hcic_accept_conn (bd_addr, p_lcb->link_role);

        p_lcb->link_state = LST_CONNECTING;
        return (TRUE);
    } else if (p_lcb->link_state == LST_DISCONNECTING) {
        /* In disconnecting state, reject the connection. */
        //counter_add("l2cap.conn.reject.disconn", 1);
        btsnd_hcic_reject_conn (bd_addr, HCI_ERR_HOST_REJECT_DEVICE);
    } else {
        L2CAP_TRACE_ERROR("L2CAP got conn_req while connected (state:%d). Reject it\n",
                          p_lcb->link_state);
        /* Reject the connection with ACL Connection Already exist reason */
        //counter_add("l2cap.conn.reject.exists", 1);
        btsnd_hcic_reject_conn (bd_addr, HCI_ERR_CONNECTION_EXISTS);
    }
    return (FALSE);
}