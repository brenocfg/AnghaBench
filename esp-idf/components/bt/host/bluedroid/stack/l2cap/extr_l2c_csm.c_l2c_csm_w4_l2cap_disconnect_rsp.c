#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int local_cid; int /*<<< orphan*/  remote_cid; int /*<<< orphan*/  remote_id; int /*<<< orphan*/  p_lcb; TYPE_1__* p_rcb; } ;
typedef  TYPE_3__ tL2C_CCB ;
typedef  int /*<<< orphan*/  (* tL2CA_DISCONNECT_CFM_CB ) (int,int /*<<< orphan*/ ) ;
typedef  int UINT16 ;
struct TYPE_7__ {int /*<<< orphan*/  (* pL2CA_DisconnectCfm_Cb ) (int,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {TYPE_2__ api; } ;

/* Variables and functions */
 int /*<<< orphan*/  L2CAP_DISC_OK ; 
 int /*<<< orphan*/  L2CAP_DISC_TIMEOUT ; 
 int /*<<< orphan*/  L2CAP_TRACE_API (char*,int) ; 
 int /*<<< orphan*/  L2CAP_TRACE_EVENT (char*,int,...) ; 
#define  L2CEVT_L2CAP_DATA 133 
#define  L2CEVT_L2CAP_DISCONNECT_REQ 132 
#define  L2CEVT_L2CAP_DISCONNECT_RSP 131 
#define  L2CEVT_L2CA_DATA_WRITE 130 
#define  L2CEVT_LP_DISCONNECT_IND 129 
#define  L2CEVT_TIMEOUT 128 
 int /*<<< orphan*/  l2c_csm_get_event_name (int) ; 
 int /*<<< orphan*/  l2cu_release_ccb (TYPE_3__*) ; 
 int /*<<< orphan*/  l2cu_send_peer_disc_rsp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osi_free (void*) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void l2c_csm_w4_l2cap_disconnect_rsp (tL2C_CCB *p_ccb, UINT16 event, void *p_data)
{
    tL2CA_DISCONNECT_CFM_CB *disconnect_cfm = p_ccb->p_rcb->api.pL2CA_DisconnectCfm_Cb;
    UINT16                  local_cid = p_ccb->local_cid;

#if (BT_TRACE_VERBOSE == TRUE)
    L2CAP_TRACE_EVENT ("L2CAP - LCID: 0x%04x  st: W4_L2CAP_DISC_RSP  evt: %s", p_ccb->local_cid, l2c_csm_get_event_name (event));
#else
    L2CAP_TRACE_EVENT ("L2CAP - st: W4_L2CAP_DISC_RSP evt: %d", event);
#endif

    switch (event) {
    case L2CEVT_L2CAP_DISCONNECT_RSP:                /* Peer disconnect response */
        l2cu_release_ccb (p_ccb);
        if (disconnect_cfm) {
            L2CAP_TRACE_API ("L2CAP - Calling DisconnectCfm_Cb(), CID: 0x%04x", local_cid);
            (*disconnect_cfm)(local_cid, L2CAP_DISC_OK);
        }
        break;

    case L2CEVT_L2CAP_DISCONNECT_REQ:                /* Peer disconnect request  */
        l2cu_send_peer_disc_rsp (p_ccb->p_lcb, p_ccb->remote_id, p_ccb->local_cid, p_ccb->remote_cid);
        l2cu_release_ccb (p_ccb);
        if (disconnect_cfm) {
            L2CAP_TRACE_API ("L2CAP - Calling DisconnectCfm_Cb(), CID: 0x%04x", local_cid);
            (*disconnect_cfm)(local_cid, L2CAP_DISC_OK);
        }
        break;

    case L2CEVT_LP_DISCONNECT_IND:                  /* Link was disconnected */
    case L2CEVT_TIMEOUT:                            /* Timeout */
        l2cu_release_ccb (p_ccb);
        if (disconnect_cfm) {
            L2CAP_TRACE_API ("L2CAP - Calling DisconnectCfm_Cb(), CID: 0x%04x", local_cid);
            (*disconnect_cfm)(local_cid, L2CAP_DISC_TIMEOUT);
        }
        break;

    case L2CEVT_L2CAP_DATA:                         /* Peer data packet rcvd    */
    case L2CEVT_L2CA_DATA_WRITE:                    /* Upper layer data to send */
        osi_free (p_data);
        break;
    }
}