#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * p_first_ccb; } ;
struct TYPE_5__ {scalar_t__ link_state; scalar_t__ idle_timeout; int /*<<< orphan*/  timer_entry; int /*<<< orphan*/  handle; TYPE_1__ ccb_queue; int /*<<< orphan*/  is_bonding; } ;
typedef  TYPE_2__ tL2C_LCB ;
typedef  int UINT16 ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  BTU_TTYPE_L2CAP_LINK ; 
 int BT_1SEC_TIMEOUT ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HCI_ERR_PEER_USER ; 
 int L2CAP_BONDING_TIMEOUT ; 
 int L2CAP_LINK_DISCONNECT_TOUT ; 
 scalar_t__ LST_CONNECTED ; 
 scalar_t__ LST_CONNECTING ; 
 scalar_t__ LST_DISCONNECTING ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ btsnd_hcic_disconnect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btu_start_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* l2cu_find_lcb_by_handle (int) ; 

BOOLEAN l2cu_start_post_bond_timer (UINT16 handle)
{
    UINT16    timeout;
    tL2C_LCB *p_lcb = l2cu_find_lcb_by_handle(handle);

    if (!p_lcb) {
        return (TRUE);
    }

    p_lcb->is_bonding = FALSE;

    /* Only start timer if no control blocks allocated */
    if (p_lcb->ccb_queue.p_first_ccb != NULL) {
        return (FALSE);
    }

    /* If no channels on the connection, start idle timeout */
    if ( (p_lcb->link_state == LST_CONNECTED) || (p_lcb->link_state == LST_CONNECTING) || (p_lcb->link_state == LST_DISCONNECTING) ) {
        if (p_lcb->idle_timeout == 0) {
            if (btsnd_hcic_disconnect (p_lcb->handle, HCI_ERR_PEER_USER)) {
                p_lcb->link_state = LST_DISCONNECTING;
                timeout = L2CAP_LINK_DISCONNECT_TOUT;
            } else {
                timeout = BT_1SEC_TIMEOUT;
            }
        } else {
            timeout = L2CAP_BONDING_TIMEOUT;
        }

        if (timeout != 0xFFFF) {
            btu_start_timer (&p_lcb->timer_entry, BTU_TTYPE_L2CAP_LINK, timeout);
        }

        return (TRUE);
    }

    return (FALSE);
}