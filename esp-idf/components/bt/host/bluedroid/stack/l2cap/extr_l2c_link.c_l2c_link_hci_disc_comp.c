#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_12__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_4__* p_first_ccb; } ;
struct TYPE_17__ {scalar_t__ disc_reason; scalar_t__ transport; TYPE_4__* p_pending_ccb; TYPE_4__** p_fixed_ccbs; int /*<<< orphan*/  remote_bd_addr; int /*<<< orphan*/  link_xmit_data_q; TYPE_1__ ccb_queue; int /*<<< orphan*/  link_role; int /*<<< orphan*/  link_state; } ;
typedef  TYPE_3__ tL2C_LCB ;
struct TYPE_18__ {struct TYPE_18__* p_next_ccb; } ;
typedef  TYPE_4__ tL2C_CCB ;
typedef  scalar_t__ tBT_TRANSPORT ;
typedef  scalar_t__ UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_16__ {int /*<<< orphan*/  (* pL2CA_FixedConn_Cb ) (scalar_t__,int /*<<< orphan*/ ,void*,scalar_t__,scalar_t__) ;} ;
struct TYPE_14__ {scalar_t__ acl_disc_reason; } ;
struct TYPE_13__ {TYPE_2__* fixed_reg; void* is_ble_connecting; } ;
typedef  int /*<<< orphan*/  BT_HDR ;
typedef  void* BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_Recovery_Pre_State () ; 
 scalar_t__ BT_TRANSPORT_BR_EDR ; 
 scalar_t__ BT_TRANSPORT_LE ; 
 void* FALSE ; 
 scalar_t__ HCI_ERR_HOST_REJECT_SECURITY ; 
 scalar_t__ L2CAP_FIRST_FIXED_CHNL ; 
 int L2CAP_NUM_FIXED_CHNLS ; 
 int /*<<< orphan*/  L2CAP_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  L2CEVT_LP_DISCONNECT_IND ; 
 int /*<<< orphan*/  LST_CONNECT_HOLDING ; 
 int /*<<< orphan*/  LST_DISCONNECTING ; 
 void* TRUE ; 
 int /*<<< orphan*/  btm_acl_removed (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  btm_ble_update_link_topology_mask (int /*<<< orphan*/ ,void*) ; 
 TYPE_12__ btm_cb ; 
 int /*<<< orphan*/  btm_sco_acl_removed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2c_csm_execute (TYPE_4__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 TYPE_10__ l2cb ; 
 scalar_t__ l2cu_create_conn (TYPE_3__*,scalar_t__) ; 
 TYPE_3__* l2cu_find_lcb_by_handle (int /*<<< orphan*/ ) ; 
 TYPE_3__* l2cu_find_lcb_by_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cu_release_ccb (TYPE_4__*) ; 
 int /*<<< orphan*/  l2cu_release_lcb (TYPE_3__*) ; 
 int /*<<< orphan*/ * list_front (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_is_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osi_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int /*<<< orphan*/ ,void*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (scalar_t__,int /*<<< orphan*/ ,void*,scalar_t__,scalar_t__) ; 

BOOLEAN l2c_link_hci_disc_comp (UINT16 handle, UINT8 reason)
{
    tL2C_LCB    *p_lcb;
#if (CLASSIC_BT_INCLUDED == TRUE)
    tL2C_CCB    *p_ccb;
#endif  ///CLASSIC_BT_INCLUDED == TRUE
    BOOLEAN     status = TRUE;
    BOOLEAN     lcb_is_free = TRUE;
    tBT_TRANSPORT   transport = BT_TRANSPORT_BR_EDR;

    /* See if we have a link control block for the connection */
    p_lcb = l2cu_find_lcb_by_handle (handle);
    /* If we don't have one, maybe an SCO link. Send to MM */
    if (!p_lcb) {
#if (BLE_INCLUDED == TRUE)
        BTM_Recovery_Pre_State();
#endif  ///BLE_INCLUDED == TRUE
        status = FALSE;
    } else {
        /* There can be a case when we rejected PIN code authentication */
        /* otherwise save a new reason */
        if (btm_cb.acl_disc_reason != HCI_ERR_HOST_REJECT_SECURITY) {
            btm_cb.acl_disc_reason = reason;
        }

        p_lcb->disc_reason = btm_cb.acl_disc_reason;

        /* Just in case app decides to try again in the callback context */
        p_lcb->link_state = LST_DISCONNECTING;

#if (BLE_INCLUDED == TRUE)
        /* Check for BLE and handle that differently */
        if (p_lcb->transport == BT_TRANSPORT_LE) {
            btm_ble_update_link_topology_mask(p_lcb->link_role, FALSE);
        }
#endif
#if (CLASSIC_BT_INCLUDED == TRUE)
        /* Link is disconnected. For all channels, send the event through */
        /* their FSMs. The CCBs should remove themselves from the LCB     */
        for (p_ccb = p_lcb->ccb_queue.p_first_ccb; p_ccb; ) {
            tL2C_CCB *pn = p_ccb->p_next_ccb;

            /* Keep connect pending control block (if exists)
             * Possible Race condition when a reconnect occurs
             * on the channel during a disconnect of link. This
             * ccb will be automatically retried after link disconnect
             * arrives
             */
            if (p_ccb != p_lcb->p_pending_ccb) {
                l2c_csm_execute (p_ccb, L2CEVT_LP_DISCONNECT_IND, &reason);
            }
            p_ccb = pn;
        }
#endif  ///CLASSIC_BT_INCLUDED == TRUE
#if (BTM_SCO_INCLUDED == TRUE)
#if (BLE_INCLUDED == TRUE)
        if (p_lcb->transport == BT_TRANSPORT_BR_EDR)
#endif
        {
            /* Tell SCO management to drop any SCOs on this ACL */
            btm_sco_acl_removed (p_lcb->remote_bd_addr);
        }
#endif

        /* If waiting for disconnect and reconnect is pending start the reconnect now
           race condition where layer above issued connect request on link that was
           disconnecting
         */
        if (p_lcb->ccb_queue.p_first_ccb != NULL || p_lcb->p_pending_ccb) {
            L2CAP_TRACE_DEBUG("l2c_link_hci_disc_comp: Restarting pending ACL request");
            transport = p_lcb->transport;
#if BLE_INCLUDED == TRUE
            /* for LE link, always drop and re-open to ensure to get LE remote feature */
            if (p_lcb->transport == BT_TRANSPORT_LE) {
                l2cb.is_ble_connecting = FALSE;
                btm_acl_removed (p_lcb->remote_bd_addr, p_lcb->transport);
                /* Release any held buffers */
                BT_HDR *p_buf;
                while (!list_is_empty(p_lcb->link_xmit_data_q)) {
                    p_buf = list_front(p_lcb->link_xmit_data_q);
                    list_remove(p_lcb->link_xmit_data_q, p_buf);
                    osi_free(p_buf);
                }
            } else
#endif
            {
#if (L2CAP_NUM_FIXED_CHNLS > 0)
                /* If we are going to re-use the LCB without dropping it, release all fixed channels
                here */
                int xx;
                for (xx = 0; xx < L2CAP_NUM_FIXED_CHNLS; xx++) {
                    if (p_lcb->p_fixed_ccbs[xx] && p_lcb->p_fixed_ccbs[xx] != p_lcb->p_pending_ccb) {
#if BLE_INCLUDED == TRUE
                        (*l2cb.fixed_reg[xx].pL2CA_FixedConn_Cb)(xx + L2CAP_FIRST_FIXED_CHNL,
                                p_lcb->remote_bd_addr, FALSE, p_lcb->disc_reason, p_lcb->transport);
#else
                        (*l2cb.fixed_reg[xx].pL2CA_FixedConn_Cb)(xx + L2CAP_FIRST_FIXED_CHNL,
                                p_lcb->remote_bd_addr, FALSE, p_lcb->disc_reason, BT_TRANSPORT_BR_EDR);
#endif
                        l2cu_release_ccb (p_lcb->p_fixed_ccbs[xx]);

                        p_lcb->p_fixed_ccbs[xx] = NULL;
                    }
                }
#endif
            }
            if (l2cu_create_conn(p_lcb, transport)) {
                lcb_is_free = FALSE;    /* still using this lcb */
            }
        }

        p_lcb->p_pending_ccb = NULL;

        /* Release the LCB */
        if (lcb_is_free) {
            l2cu_release_lcb (p_lcb);
        }
    }

    /* Now that we have a free acl connection, see if any lcbs are pending */
    if (lcb_is_free && ((p_lcb = l2cu_find_lcb_by_state(LST_CONNECT_HOLDING)) != NULL)) {
        /* we found one-- create a connection */
        l2cu_create_conn(p_lcb, BT_TRANSPORT_BR_EDR);
    }

    return status;
}