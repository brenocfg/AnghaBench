#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  l2cap_status; int /*<<< orphan*/  l2cap_result; } ;
typedef  TYPE_4__ tL2C_CONN_INFO ;
struct TYPE_14__ {int local_cid; int /*<<< orphan*/  remote_id; TYPE_3__* p_rcb; TYPE_2__* p_lcb; int /*<<< orphan*/  timer_entry; int /*<<< orphan*/  chnl_state; } ;
typedef  TYPE_5__ tL2C_CCB ;
typedef  int /*<<< orphan*/  (* tL2CA_DISCONNECT_IND_CB ) (int,int /*<<< orphan*/ ) ;
typedef  int UINT16 ;
struct TYPE_10__ {int /*<<< orphan*/  (* pL2CA_ConnectInd_Cb ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* pL2CA_DisconnectInd_Cb ) (int,int /*<<< orphan*/ ) ;} ;
struct TYPE_12__ {int /*<<< orphan*/  psm; TYPE_1__ api; } ;
struct TYPE_11__ {int /*<<< orphan*/  remote_bd_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTU_TTYPE_L2CAP_CHNL ; 
 int /*<<< orphan*/  CST_CONFIG ; 
 int /*<<< orphan*/  CST_W4_L2CAP_DISCONNECT_RSP ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  L2CAP_CHNL_CFG_TIMEOUT ; 
 int /*<<< orphan*/  L2CAP_CHNL_CONNECT_TOUT ; 
 int /*<<< orphan*/  L2CAP_CHNL_CONNECT_TOUT_EXT ; 
 int /*<<< orphan*/  L2CAP_CHNL_DISCONNECT_TOUT ; 
 int /*<<< orphan*/  L2CAP_CONN_NO_PSM ; 
 int /*<<< orphan*/  L2CAP_CONN_OK ; 
 int /*<<< orphan*/  L2CAP_TRACE_API (char*,int) ; 
 int /*<<< orphan*/  L2CAP_TRACE_EVENT (char*,int,...) ; 
#define  L2CEVT_L2CAP_DATA 135 
#define  L2CEVT_L2CAP_INFO_RSP 134 
#define  L2CEVT_L2CA_CONNECT_RSP 133 
#define  L2CEVT_L2CA_CONNECT_RSP_NEG 132 
#define  L2CEVT_L2CA_DATA_WRITE 131 
#define  L2CEVT_L2CA_DISCONNECT_REQ 130 
#define  L2CEVT_LP_DISCONNECT_IND 129 
#define  L2CEVT_TIMEOUT 128 
 int /*<<< orphan*/  btu_start_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2c_csm_get_event_name (int) ; 
 int /*<<< orphan*/  l2cu_release_ccb (TYPE_5__*) ; 
 int /*<<< orphan*/  l2cu_send_peer_connect_rsp (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cu_send_peer_disc_req (TYPE_5__*) ; 
 int /*<<< orphan*/  osi_free (void*) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void l2c_csm_w4_l2ca_connect_rsp (tL2C_CCB *p_ccb, UINT16 event, void *p_data)
{
    tL2C_CONN_INFO          *p_ci;
    tL2CA_DISCONNECT_IND_CB *disconnect_ind = p_ccb->p_rcb->api.pL2CA_DisconnectInd_Cb;
    UINT16                  local_cid = p_ccb->local_cid;

#if (BT_TRACE_VERBOSE == TRUE)
    L2CAP_TRACE_EVENT ("L2CAP - LCID: 0x%04x  st: W4_L2CA_CON_RSP  evt: %s", p_ccb->local_cid, l2c_csm_get_event_name (event));
#else
    L2CAP_TRACE_EVENT ("L2CAP - st: W4_L2CA_CON_RSP evt: %d", event);
#endif

    switch (event) {
    case L2CEVT_LP_DISCONNECT_IND:                  /* Link was disconnected */
        L2CAP_TRACE_API ("L2CAP - Calling Disconnect_Ind_Cb(), CID: 0x%04x  No Conf Needed", p_ccb->local_cid);
        l2cu_release_ccb (p_ccb);
        (*disconnect_ind)(local_cid, FALSE);
        break;

    case L2CEVT_L2CA_CONNECT_RSP:
        p_ci = (tL2C_CONN_INFO *)p_data;

        /* Result should be OK or PENDING */
        if ((!p_ci) || (p_ci->l2cap_result == L2CAP_CONN_OK)) {
            l2cu_send_peer_connect_rsp (p_ccb, L2CAP_CONN_OK, 0);
            p_ccb->chnl_state = CST_CONFIG;
            btu_start_timer (&p_ccb->timer_entry, BTU_TTYPE_L2CAP_CHNL, L2CAP_CHNL_CFG_TIMEOUT);
        } else {
            /* If pending, stay in same state and start extended timer */
            l2cu_send_peer_connect_rsp (p_ccb, p_ci->l2cap_result, p_ci->l2cap_status);
            btu_start_timer (&p_ccb->timer_entry, BTU_TTYPE_L2CAP_CHNL, L2CAP_CHNL_CONNECT_TOUT_EXT);
        }
        break;

    case L2CEVT_L2CA_CONNECT_RSP_NEG:
        p_ci = (tL2C_CONN_INFO *)p_data;
        l2cu_send_peer_connect_rsp (p_ccb, p_ci->l2cap_result, p_ci->l2cap_status);
        l2cu_release_ccb (p_ccb);
        break;

    case L2CEVT_TIMEOUT:
        l2cu_send_peer_connect_rsp (p_ccb, L2CAP_CONN_NO_PSM, 0);
        L2CAP_TRACE_API ("L2CAP - Calling Disconnect_Ind_Cb(), CID: 0x%04x  No Conf Needed", p_ccb->local_cid);
        l2cu_release_ccb (p_ccb);
        (*disconnect_ind)(local_cid, FALSE);
        break;

    case L2CEVT_L2CA_DATA_WRITE:                    /* Upper layer data to send */
    case L2CEVT_L2CAP_DATA:                         /* Peer data packet rcvd    */
        osi_free (p_data);
        break;

    case L2CEVT_L2CA_DISCONNECT_REQ:                 /* Upper wants to disconnect */
        l2cu_send_peer_disc_req (p_ccb);
        p_ccb->chnl_state = CST_W4_L2CAP_DISCONNECT_RSP;
        btu_start_timer (&p_ccb->timer_entry, BTU_TTYPE_L2CAP_CHNL, L2CAP_CHNL_DISCONNECT_TOUT);
        break;

    case L2CEVT_L2CAP_INFO_RSP:
        /* We have feature info, so now give the upper layer connect IND */
        btu_start_timer (&p_ccb->timer_entry, BTU_TTYPE_L2CAP_CHNL, L2CAP_CHNL_CONNECT_TOUT);
        L2CAP_TRACE_API ("L2CAP - Calling Connect_Ind_Cb(), CID: 0x%04x", p_ccb->local_cid);

        (*p_ccb->p_rcb->api.pL2CA_ConnectInd_Cb) (p_ccb->p_lcb->remote_bd_addr,
                p_ccb->local_cid,
                p_ccb->p_rcb->psm,
                p_ccb->remote_id);
        break;
    }
}