#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_3__* p_first_ccb; } ;
struct TYPE_12__ {scalar_t__ link_state; int /*<<< orphan*/  timer_entry; int /*<<< orphan*/  handle; scalar_t__ is_bonding; TYPE_1__ ccb_queue; int /*<<< orphan*/  (* p_echo_rsp_cb ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/ * p_pending_ccb; } ;
typedef  TYPE_2__ tL2C_LCB ;
struct TYPE_13__ {struct TYPE_13__* p_next_ccb; } ;
typedef  TYPE_3__ tL2C_CCB ;
typedef  int /*<<< orphan*/  (* tL2CA_ECHO_RSP_CB ) (int /*<<< orphan*/ ) ;
typedef  scalar_t__ tBTM_STATUS ;
typedef  int UINT16 ;
struct TYPE_14__ {scalar_t__ is_ble_connecting; int /*<<< orphan*/  ble_connecting_bda; } ;

/* Variables and functions */
 scalar_t__ BTM_BUSY ; 
 scalar_t__ BTM_CMD_STARTED ; 
 scalar_t__ BTM_CMD_STORED ; 
 scalar_t__ BTM_SUCCESS ; 
 int /*<<< orphan*/  BTU_TTYPE_L2CAP_LINK ; 
 int BT_1SEC_TIMEOUT ; 
 int /*<<< orphan*/  HCI_ERR_PEER_USER ; 
 int L2CAP_LINK_DISCONNECT_TOUT ; 
 int /*<<< orphan*/  L2CAP_PING_RESULT_NO_RESP ; 
 int /*<<< orphan*/  L2CAP_TRACE_EVENT (char*,scalar_t__,TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  L2CAP_TRACE_WARNING (char*) ; 
 int /*<<< orphan*/  L2CA_CancelBleConnectReq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L2CEVT_LP_DISCONNECT_IND ; 
 scalar_t__ LST_CONNECTED ; 
 scalar_t__ LST_CONNECTING ; 
 scalar_t__ LST_CONNECTING_WAIT_SWITCH ; 
 scalar_t__ LST_CONNECT_HOLDING ; 
 scalar_t__ LST_DISCONNECTING ; 
 scalar_t__ TRUE ; 
 scalar_t__ btm_sec_disconnect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ btsnd_hcic_disconnect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btu_start_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  l2c_csm_execute (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2c_link_check_send_pkts (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_6__ l2cb ; 
 int /*<<< orphan*/  l2cu_process_fixed_disc_cback (TYPE_2__*) ; 
 int /*<<< orphan*/  l2cu_release_lcb (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void l2c_link_timeout (tL2C_LCB *p_lcb)
{
#if (CLASSIC_BT_INCLUDED == TRUE)
    tL2C_CCB   *p_ccb;
#endif  ///CLASSIC_BT_INCLUDED == TRUE
#if (SMP_INCLUDED == TRUE)
    UINT16      timeout;
    tBTM_STATUS rc;
#endif  ///SMP_INCLUDED == TRUE
    L2CAP_TRACE_EVENT ("L2CAP - l2c_link_timeout() link state %d first CCB %p is_bonding:%d",
                       p_lcb->link_state, p_lcb->ccb_queue.p_first_ccb, p_lcb->is_bonding);

    /* If link was connecting or disconnecting, clear all channels and drop the LCB */
    if ((p_lcb->link_state == LST_CONNECTING_WAIT_SWITCH) ||
            (p_lcb->link_state == LST_CONNECTING) ||
            (p_lcb->link_state == LST_CONNECT_HOLDING) ||
            (p_lcb->link_state == LST_DISCONNECTING)) {
        p_lcb->p_pending_ccb = NULL;
#if (CLASSIC_BT_INCLUDED == TRUE)
        /* For all channels, send a disconnect indication event through */
        /* their FSMs. The CCBs should remove themselves from the LCB   */
        for (p_ccb = p_lcb->ccb_queue.p_first_ccb; p_ccb; ) {
            tL2C_CCB *pn = p_ccb->p_next_ccb;

            l2c_csm_execute (p_ccb, L2CEVT_LP_DISCONNECT_IND, NULL);

            p_ccb = pn;
        }
#endif  ///CLASSIC_BT_INCLUDED == TRUE
#if (BLE_INCLUDED == TRUE)
        if (p_lcb->link_state == LST_CONNECTING &&
                l2cb.is_ble_connecting == TRUE) {
            L2CA_CancelBleConnectReq(l2cb.ble_connecting_bda);
        }
#endif
        /* Release the LCB */
        l2cu_release_lcb (p_lcb);
    }

    /* If link is connected, check for inactivity timeout */
    if (p_lcb->link_state == LST_CONNECTED) {
        /* Check for ping outstanding */
        if (p_lcb->p_echo_rsp_cb) {
            tL2CA_ECHO_RSP_CB *p_cb = p_lcb->p_echo_rsp_cb;

            /* Zero out the callback in case app immediately calls us again */
            p_lcb->p_echo_rsp_cb = NULL;

            (*p_cb) (L2CAP_PING_RESULT_NO_RESP);

            L2CAP_TRACE_WARNING ("L2CAP - ping timeout");
#if (CLASSIC_BT_INCLUDED == TRUE)
            /* For all channels, send a disconnect indication event through */
            /* their FSMs. The CCBs should remove themselves from the LCB   */
            for (p_ccb = p_lcb->ccb_queue.p_first_ccb; p_ccb; ) {
                tL2C_CCB *pn = p_ccb->p_next_ccb;

                l2c_csm_execute (p_ccb, L2CEVT_LP_DISCONNECT_IND, NULL);

                p_ccb = pn;
            }
#endif  ///CLASSIC_BT_INCLUDED == TRUE
        }

#if (SMP_INCLUDED == TRUE)
        /* If no channels in use, drop the link. */
        if (!p_lcb->ccb_queue.p_first_ccb) {
            rc = btm_sec_disconnect (p_lcb->handle, HCI_ERR_PEER_USER);

            if (rc == BTM_CMD_STORED) {
                /* Security Manager will take care of disconnecting, state will be updated at that time */
                timeout = 0xFFFF;
            } else if (rc == BTM_CMD_STARTED) {
                p_lcb->link_state = LST_DISCONNECTING;
                timeout = L2CAP_LINK_DISCONNECT_TOUT;
            } else if (rc == BTM_SUCCESS) {
                l2cu_process_fixed_disc_cback(p_lcb);
                /* BTM SEC will make sure that link is release (probably after pairing is done) */
                p_lcb->link_state = LST_DISCONNECTING;
                timeout = 0xFFFF;
            } else if (rc == BTM_BUSY) {
                /* BTM is still executing security process. Let lcb stay as connected */
                timeout = 0xFFFF;
            } else if ((p_lcb->is_bonding)
                       && (btsnd_hcic_disconnect (p_lcb->handle, HCI_ERR_PEER_USER))) {
                l2cu_process_fixed_disc_cback(p_lcb);
                p_lcb->link_state = LST_DISCONNECTING;
                timeout = L2CAP_LINK_DISCONNECT_TOUT;
            } else {
                /* probably no buffer to send disconnect */
                timeout = BT_1SEC_TIMEOUT;
            }

            if (timeout != 0xFFFF) {
                btu_start_timer (&p_lcb->timer_entry, BTU_TTYPE_L2CAP_LINK, timeout);
            }
        } else {
            /* Check in case we were flow controlled */
            l2c_link_check_send_pkts (p_lcb, NULL, NULL);
        }
#endif  ///SMP_INCLUDED == TRUE
    }
}