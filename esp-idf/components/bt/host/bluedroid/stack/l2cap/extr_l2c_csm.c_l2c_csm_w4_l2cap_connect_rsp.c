#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  l2cap_result; int /*<<< orphan*/  remote_cid; } ;
typedef  TYPE_3__ tL2C_CONN_INFO ;
struct TYPE_13__ {int local_cid; int flags; int /*<<< orphan*/  timer_entry; int /*<<< orphan*/  chnl_state; int /*<<< orphan*/  remote_cid; TYPE_2__* p_rcb; } ;
typedef  TYPE_4__ tL2C_CCB ;
typedef  int /*<<< orphan*/  (* tL2CA_DISCONNECT_IND_CB ) (int,int /*<<< orphan*/ ) ;
typedef  int /*<<< orphan*/  (* tL2CA_CONNECT_CFM_CB ) (int,int /*<<< orphan*/ ) ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int UINT16 ;
struct TYPE_10__ {int /*<<< orphan*/  (* pL2CA_ConnectPnd_Cb ) (int) ;int /*<<< orphan*/  (* pL2CA_ConnectCfm_Cb ) (int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* pL2CA_DisconnectInd_Cb ) (int,int /*<<< orphan*/ ) ;} ;
struct TYPE_11__ {TYPE_1__ api; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTU_TTYPE_L2CAP_CHNL ; 
 int CCB_FLAG_NO_RETRY ; 
 int /*<<< orphan*/  CST_CLOSED ; 
 int /*<<< orphan*/  CST_CONFIG ; 
 int /*<<< orphan*/  CST_W4_L2CAP_DISCONNECT_RSP ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HCI_ERR_PEER_USER ; 
 int /*<<< orphan*/  L2CAP_CHNL_CFG_TIMEOUT ; 
 int /*<<< orphan*/  L2CAP_CHNL_CONNECT_TOUT ; 
 int /*<<< orphan*/  L2CAP_CHNL_CONNECT_TOUT_EXT ; 
 int /*<<< orphan*/  L2CAP_CHNL_DISCONNECT_TOUT ; 
 int /*<<< orphan*/  L2CAP_CONN_NO_LINK ; 
 int /*<<< orphan*/  L2CAP_CONN_OK ; 
 int /*<<< orphan*/  L2CAP_CONN_TIMEOUT ; 
 int /*<<< orphan*/  L2CAP_TRACE_API (char*,int,...) ; 
 int /*<<< orphan*/  L2CAP_TRACE_EVENT (char*,int,...) ; 
#define  L2CEVT_L2CAP_CONNECT_RSP 136 
#define  L2CEVT_L2CAP_CONNECT_RSP_NEG 135 
#define  L2CEVT_L2CAP_CONNECT_RSP_PND 134 
#define  L2CEVT_L2CAP_DATA 133 
#define  L2CEVT_L2CAP_INFO_RSP 132 
#define  L2CEVT_L2CA_DATA_WRITE 131 
#define  L2CEVT_L2CA_DISCONNECT_REQ 130 
#define  L2CEVT_LP_DISCONNECT_IND 129 
#define  L2CEVT_TIMEOUT 128 
 int /*<<< orphan*/  btu_start_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2c_csm_get_event_name (int) ; 
 int /*<<< orphan*/  l2c_fcr_chk_chan_modes (TYPE_4__*) ; 
 int /*<<< orphan*/  l2cu_release_ccb (TYPE_4__*) ; 
 int /*<<< orphan*/  l2cu_send_peer_connect_req (TYPE_4__*) ; 
 int /*<<< orphan*/  l2cu_send_peer_disc_req (TYPE_4__*) ; 
 int /*<<< orphan*/  osi_free (void*) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int) ; 
 int /*<<< orphan*/  stub4 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void l2c_csm_w4_l2cap_connect_rsp (tL2C_CCB *p_ccb, UINT16 event, void *p_data)
{
    tL2C_CONN_INFO          *p_ci = (tL2C_CONN_INFO *)p_data;
    tL2CA_DISCONNECT_IND_CB *disconnect_ind = p_ccb->p_rcb->api.pL2CA_DisconnectInd_Cb;
    tL2CA_CONNECT_CFM_CB    *connect_cfm = p_ccb->p_rcb->api.pL2CA_ConnectCfm_Cb;
    UINT16                  local_cid = p_ccb->local_cid;

#if (BT_TRACE_VERBOSE == TRUE)
    L2CAP_TRACE_EVENT ("L2CAP - LCID: 0x%04x  st: W4_L2CAP_CON_RSP  evt: %s", p_ccb->local_cid, l2c_csm_get_event_name (event));
#else
    L2CAP_TRACE_EVENT ("L2CAP - st: W4_L2CAP_CON_RSP evt: %d", event);
#endif

    switch (event) {
    case L2CEVT_LP_DISCONNECT_IND:                  /* Link was disconnected */
        /* Send disc indication unless peer to peer race condition AND normal disconnect */
        /* *((UINT8 *)p_data) != HCI_ERR_PEER_USER happens when peer device try to disconnect for normal reason */
        p_ccb->chnl_state = CST_CLOSED;
        if ((p_ccb->flags & CCB_FLAG_NO_RETRY) || !p_data || (*((UINT8 *)p_data) != HCI_ERR_PEER_USER)) {
            L2CAP_TRACE_API ("L2CAP - Calling Disconnect_Ind_Cb(), CID: 0x%04x  No Conf Needed",
                             p_ccb->local_cid);
            l2cu_release_ccb (p_ccb);
            (*disconnect_ind)(local_cid, FALSE);
        }
        p_ccb->flags |= CCB_FLAG_NO_RETRY;
        break;

    case L2CEVT_L2CAP_CONNECT_RSP:                  /* Got peer connect confirm */
        p_ccb->remote_cid = p_ci->remote_cid;
        p_ccb->chnl_state = CST_CONFIG;
        btu_start_timer (&p_ccb->timer_entry, BTU_TTYPE_L2CAP_CHNL, L2CAP_CHNL_CFG_TIMEOUT);
        L2CAP_TRACE_API ("L2CAP - Calling Connect_Cfm_Cb(), CID: 0x%04x, Success", p_ccb->local_cid);

        (*p_ccb->p_rcb->api.pL2CA_ConnectCfm_Cb)(local_cid, L2CAP_CONN_OK);
        break;

    case L2CEVT_L2CAP_CONNECT_RSP_PND:              /* Got peer connect pending */
        p_ccb->remote_cid = p_ci->remote_cid;
        btu_start_timer (&p_ccb->timer_entry, BTU_TTYPE_L2CAP_CHNL, L2CAP_CHNL_CONNECT_TOUT_EXT);
        if (p_ccb->p_rcb->api.pL2CA_ConnectPnd_Cb) {
            L2CAP_TRACE_API ("L2CAP - Calling Connect_Pnd_Cb(), CID: 0x%04x", p_ccb->local_cid);
            (*p_ccb->p_rcb->api.pL2CA_ConnectPnd_Cb)(p_ccb->local_cid);
        }
        break;

    case L2CEVT_L2CAP_CONNECT_RSP_NEG:              /* Peer rejected connection */
        L2CAP_TRACE_API ("L2CAP - Calling Connect_Cfm_Cb(), CID: 0x%04x, Failure Code: %d", p_ccb->local_cid, p_ci->l2cap_result);
        l2cu_release_ccb (p_ccb);
        (*connect_cfm)(local_cid, p_ci->l2cap_result);
        break;

    case L2CEVT_TIMEOUT:
        L2CAP_TRACE_API ("L2CAP - Calling Connect_Cfm_Cb(), CID: 0x%04x, Timeout", p_ccb->local_cid);
        l2cu_release_ccb (p_ccb);
        (*connect_cfm)(local_cid, L2CAP_CONN_TIMEOUT);
        break;

    case L2CEVT_L2CA_DISCONNECT_REQ:                 /* Upper wants to disconnect */
        /* If we know peer CID from connect pending, we can send disconnect */
        if (p_ccb->remote_cid != 0) {
            l2cu_send_peer_disc_req (p_ccb);
            p_ccb->chnl_state = CST_W4_L2CAP_DISCONNECT_RSP;
            btu_start_timer (&p_ccb->timer_entry, BTU_TTYPE_L2CAP_CHNL, L2CAP_CHNL_DISCONNECT_TOUT);
        } else {
            l2cu_release_ccb (p_ccb);
        }
        break;

    case L2CEVT_L2CA_DATA_WRITE:                    /* Upper layer data to send */
    case L2CEVT_L2CAP_DATA:                         /* Peer data packet rcvd    */
        osi_free (p_data);
        break;

    case L2CEVT_L2CAP_INFO_RSP:
        /* Need to have at least one compatible channel to continue */
        if (!l2c_fcr_chk_chan_modes(p_ccb)) {
            l2cu_release_ccb (p_ccb);
            (*connect_cfm)(local_cid, L2CAP_CONN_NO_LINK);
        } else {
            /* We have feature info, so now send peer connect request */
            btu_start_timer (&p_ccb->timer_entry, BTU_TTYPE_L2CAP_CHNL, L2CAP_CHNL_CONNECT_TOUT);
            l2cu_send_peer_connect_req (p_ccb);          /* Start Connection     */
        }
        break;
    }
}