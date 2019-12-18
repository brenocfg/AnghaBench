#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_15__ ;

/* Type definitions */
typedef  void* tL2C_CHNL_STATE ;
struct TYPE_24__ {int /*<<< orphan*/  mode; } ;
struct TYPE_25__ {TYPE_3__ fcr; } ;
struct TYPE_26__ {scalar_t__ local_cid; TYPE_4__ peer_cfg; int /*<<< orphan*/  timer_entry; int /*<<< orphan*/  config_done; void* chnl_state; TYPE_15__* p_lcb; TYPE_2__* p_rcb; } ;
typedef  TYPE_5__ tL2C_CCB ;
typedef  int /*<<< orphan*/  tL2CAP_CFG_INFO ;
struct TYPE_27__ {void* mode; } ;
typedef  TYPE_6__ tBTM_PM_PWR_MD ;
typedef  int /*<<< orphan*/  settings ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_22__ {int /*<<< orphan*/  (* pL2CA_DataInd_Cb ) (scalar_t__,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* pL2CA_DisconnectInd_Cb ) (scalar_t__,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* pL2CA_ConfigInd_Cb ) (scalar_t__,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* pL2CA_QoSViolationInd_Cb ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_23__ {TYPE_1__ api; } ;
struct TYPE_21__ {int /*<<< orphan*/  remote_bd_addr; } ;
typedef  int /*<<< orphan*/  BT_HDR ;

/* Variables and functions */
 void* BTM_PM_MD_ACTIVE ; 
 int /*<<< orphan*/  BTM_PM_SET_ONLY_ID ; 
 int /*<<< orphan*/  BTM_SetPowerMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  BTU_TTYPE_L2CAP_CHNL ; 
 int /*<<< orphan*/  CFG_DONE_MASK ; 
 void* CST_CONFIG ; 
 void* CST_W4_L2CAP_DISCONNECT_RSP ; 
 void* CST_W4_L2CA_DISCONNECT_RSP ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  L2CAP_CHNL_CFG_TIMEOUT ; 
 int /*<<< orphan*/  L2CAP_CHNL_DISCONNECT_TOUT ; 
 scalar_t__ L2CAP_CONNECTIONLESS_CID ; 
 int /*<<< orphan*/  L2CAP_FCR_ERTM_MODE ; 
 int /*<<< orphan*/  L2CAP_PEER_CFG_OK ; 
 int /*<<< orphan*/  L2CAP_PEER_CFG_UNACCEPTABLE ; 
 int /*<<< orphan*/  L2CAP_TRACE_API (char*,scalar_t__) ; 
 int /*<<< orphan*/  L2CAP_TRACE_EVENT (char*,scalar_t__,...) ; 
#define  L2CEVT_ACK_TIMEOUT 137 
#define  L2CEVT_L2CAP_CONFIG_REQ 136 
#define  L2CEVT_L2CAP_DATA 135 
#define  L2CEVT_L2CAP_DISCONNECT_REQ 134 
#define  L2CEVT_L2CA_CONFIG_REQ 133 
#define  L2CEVT_L2CA_DATA_WRITE 132 
#define  L2CEVT_L2CA_DISCONNECT_REQ 131 
#define  L2CEVT_LP_DISCONNECT_IND 130 
#define  L2CEVT_LP_QOS_VIOLATION_IND 129 
#define  L2CEVT_TIMEOUT 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  btu_start_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btu_stop_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2c_csm_get_event_name (scalar_t__) ; 
 int /*<<< orphan*/  l2c_enqueue_peer_data (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2c_fcr_proc_ack_tout (TYPE_5__*) ; 
 int /*<<< orphan*/  l2c_fcr_proc_tout (TYPE_5__*) ; 
 int /*<<< orphan*/  l2c_link_check_send_pkts (TYPE_15__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ l2c_ucd_process_event (TYPE_5__*,scalar_t__,void*) ; 
 int /*<<< orphan*/  l2cu_disconnect_chnl (TYPE_5__*) ; 
 int /*<<< orphan*/  l2cu_process_our_cfg_req (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2cu_process_peer_cfg_req (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2cu_release_ccb (TYPE_5__*) ; 
 int /*<<< orphan*/  l2cu_send_peer_config_req (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2cu_send_peer_config_rsp (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2cu_send_peer_disc_req (TYPE_5__*) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void l2c_csm_open (tL2C_CCB *p_ccb, UINT16 event, void *p_data)
{
    UINT16                  local_cid = p_ccb->local_cid;
    tL2CAP_CFG_INFO         *p_cfg;
    tL2C_CHNL_STATE         tempstate;
    UINT8                   tempcfgdone;
    UINT8                   cfg_result;

#if (BT_TRACE_VERBOSE == TRUE)
    L2CAP_TRACE_EVENT ("L2CAP - LCID: 0x%04x  st: OPEN  evt: %s",
                       p_ccb->local_cid, l2c_csm_get_event_name (event));
#else
    L2CAP_TRACE_EVENT ("L2CAP - st: OPEN evt: %d", event);
#endif

#if (L2CAP_UCD_INCLUDED == TRUE)
    if ( local_cid == L2CAP_CONNECTIONLESS_CID ) {
        /* check if this event can be processed by UCD */
        if ( l2c_ucd_process_event (p_ccb, event, p_data) ) {
            /* The event is processed by UCD state machine */
            return;
        }
    }
#endif

    switch (event) {
    case L2CEVT_LP_DISCONNECT_IND:                  /* Link was disconnected */
        L2CAP_TRACE_API ("L2CAP - Calling Disconnect_Ind_Cb(), CID: 0x%04x  No Conf Needed",
                         p_ccb->local_cid);
        l2cu_release_ccb (p_ccb);
        if (p_ccb->p_rcb) {
            (*p_ccb->p_rcb->api.pL2CA_DisconnectInd_Cb)(local_cid, FALSE);
        }
        break;

    case L2CEVT_LP_QOS_VIOLATION_IND:               /* QOS violation         */
        /* Tell upper layer. If service guaranteed, then clear the channel   */
        if (p_ccb->p_rcb->api.pL2CA_QoSViolationInd_Cb) {
            (*p_ccb->p_rcb->api.pL2CA_QoSViolationInd_Cb)(p_ccb->p_lcb->remote_bd_addr);
        }
        break;

    case L2CEVT_L2CAP_CONFIG_REQ:                  /* Peer config request   */
        p_cfg = (tL2CAP_CFG_INFO *)p_data;

        tempstate = p_ccb->chnl_state;
        tempcfgdone = p_ccb->config_done;
        p_ccb->chnl_state = CST_CONFIG;
        p_ccb->config_done &= ~CFG_DONE_MASK;

        btu_start_timer (&p_ccb->timer_entry, BTU_TTYPE_L2CAP_CHNL, L2CAP_CHNL_CFG_TIMEOUT);

        if ((cfg_result = l2cu_process_peer_cfg_req (p_ccb, p_cfg)) == L2CAP_PEER_CFG_OK) {
            (*p_ccb->p_rcb->api.pL2CA_ConfigInd_Cb)(p_ccb->local_cid, p_cfg);
        }

        /* Error in config parameters: reset state and config flag */
        else if (cfg_result == L2CAP_PEER_CFG_UNACCEPTABLE) {
            btu_stop_timer(&p_ccb->timer_entry);
            p_ccb->chnl_state = tempstate;
            p_ccb->config_done = tempcfgdone;
            l2cu_send_peer_config_rsp (p_ccb, p_cfg);
        } else { /* L2CAP_PEER_CFG_DISCONNECT */
            /* Disconnect if channels are incompatible
             * Note this should not occur if reconfigure
             * since this should have never passed original config.
             */
            l2cu_disconnect_chnl (p_ccb);
        }
        break;

    case L2CEVT_L2CAP_DISCONNECT_REQ:                  /* Peer disconnected request */
// btla-specific ++
        /* Make sure we are not in sniff mode */
    {
        tBTM_PM_PWR_MD settings;
        memset((void *)&settings, 0, sizeof(settings));
        settings.mode = BTM_PM_MD_ACTIVE;
        BTM_SetPowerMode (BTM_PM_SET_ONLY_ID, p_ccb->p_lcb->remote_bd_addr, &settings);
    }
// btla-specific --

    p_ccb->chnl_state = CST_W4_L2CA_DISCONNECT_RSP;
    btu_start_timer (&p_ccb->timer_entry, BTU_TTYPE_L2CAP_CHNL, L2CAP_CHNL_DISCONNECT_TOUT);
    L2CAP_TRACE_API ("L2CAP - Calling Disconnect_Ind_Cb(), CID: 0x%04x  Conf Needed", p_ccb->local_cid);
    (*p_ccb->p_rcb->api.pL2CA_DisconnectInd_Cb)(p_ccb->local_cid, TRUE);
    break;

    case L2CEVT_L2CAP_DATA:                         /* Peer data packet rcvd    */
        if ((p_ccb->p_rcb) && (p_ccb->p_rcb->api.pL2CA_DataInd_Cb)) {
            (*p_ccb->p_rcb->api.pL2CA_DataInd_Cb)(p_ccb->local_cid, (BT_HDR *)p_data);
        }
        break;

    case L2CEVT_L2CA_DISCONNECT_REQ:                 /* Upper wants to disconnect */
        /* Make sure we are not in sniff mode */
    {
        tBTM_PM_PWR_MD settings;
        memset((void *)&settings, 0, sizeof(settings));
        settings.mode = BTM_PM_MD_ACTIVE;
        BTM_SetPowerMode (BTM_PM_SET_ONLY_ID, p_ccb->p_lcb->remote_bd_addr, &settings);
    }

    l2cu_send_peer_disc_req (p_ccb);
    p_ccb->chnl_state = CST_W4_L2CAP_DISCONNECT_RSP;
    btu_start_timer (&p_ccb->timer_entry, BTU_TTYPE_L2CAP_CHNL, L2CAP_CHNL_DISCONNECT_TOUT);
    break;

    case L2CEVT_L2CA_DATA_WRITE:                    /* Upper layer data to send */
        l2c_enqueue_peer_data (p_ccb, (BT_HDR *)p_data);
        l2c_link_check_send_pkts (p_ccb->p_lcb, NULL, NULL);
        break;

    case L2CEVT_L2CA_CONFIG_REQ:                   /* Upper layer config req   */
        p_ccb->chnl_state = CST_CONFIG;
        p_ccb->config_done &= ~CFG_DONE_MASK;
        l2cu_process_our_cfg_req (p_ccb, (tL2CAP_CFG_INFO *)p_data);
        l2cu_send_peer_config_req (p_ccb, (tL2CAP_CFG_INFO *)p_data);
        btu_start_timer (&p_ccb->timer_entry, BTU_TTYPE_L2CAP_CHNL, L2CAP_CHNL_CFG_TIMEOUT);
        break;

    case L2CEVT_TIMEOUT:
        /* Process the monitor/retransmission time-outs in flow control/retrans mode */
        if (p_ccb->peer_cfg.fcr.mode == L2CAP_FCR_ERTM_MODE) {
            l2c_fcr_proc_tout (p_ccb);
        }
        break;

    case L2CEVT_ACK_TIMEOUT:
        l2c_fcr_proc_ack_tout (p_ccb);
        break;
    }
}