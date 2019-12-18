#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_48__   TYPE_9__ ;
typedef  struct TYPE_47__   TYPE_8__ ;
typedef  struct TYPE_46__   TYPE_7__ ;
typedef  struct TYPE_45__   TYPE_6__ ;
typedef  struct TYPE_44__   TYPE_5__ ;
typedef  struct TYPE_43__   TYPE_4__ ;
typedef  struct TYPE_42__   TYPE_3__ ;
typedef  struct TYPE_41__   TYPE_30__ ;
typedef  struct TYPE_40__   TYPE_2__ ;
typedef  struct TYPE_39__   TYPE_29__ ;
typedef  struct TYPE_38__   TYPE_1__ ;
typedef  struct TYPE_37__   TYPE_10__ ;

/* Type definitions */
struct TYPE_44__ {void* connect_tick_count; int /*<<< orphan*/  wait_ack; } ;
struct TYPE_40__ {int /*<<< orphan*/  mode; } ;
struct TYPE_47__ {TYPE_2__ fcr; void* qos_present; void* flush_to_present; void* mtu_present; } ;
struct TYPE_42__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  rtrans_tout; int /*<<< orphan*/  mon_tout; } ;
struct TYPE_43__ {TYPE_3__ fcr; } ;
struct TYPE_48__ {int local_cid; int config_done; void* chnl_state; TYPE_7__* p_rcb; TYPE_30__* p_lcb; int /*<<< orphan*/  timer_entry; int /*<<< orphan*/  xmit_hold_q; TYPE_5__ fcrb; TYPE_8__ peer_cfg; TYPE_4__ our_cfg; } ;
typedef  TYPE_9__ tL2C_CCB ;
typedef  int /*<<< orphan*/  (* tL2CA_DISCONNECT_IND_CB ) (int,void*) ;
struct TYPE_37__ {int flags; int /*<<< orphan*/  result; } ;
typedef  TYPE_10__ tL2CAP_CFG_INFO ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int UINT16 ;
struct TYPE_45__ {int /*<<< orphan*/  (* pL2CA_DataInd_Cb ) (size_t,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* pL2CA_DisconnectInd_Cb ) (int,void*) ;int /*<<< orphan*/  (* pL2CA_ConfigCfm_Cb ) (int,TYPE_10__*) ;int /*<<< orphan*/  (* pL2CA_ConfigInd_Cb ) (int,TYPE_10__*) ;} ;
struct TYPE_46__ {TYPE_6__ api; } ;
struct TYPE_41__ {int /*<<< orphan*/  remote_bd_addr; } ;
struct TYPE_39__ {TYPE_1__* fixed_reg; } ;
struct TYPE_38__ {int /*<<< orphan*/  (* pL2CA_FixedData_Cb ) (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  BT_HDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTU_TTYPE_L2CAP_CHNL ; 
 void* CST_OPEN ; 
 void* CST_W4_L2CAP_DISCONNECT_RSP ; 
 void* CST_W4_L2CA_DISCONNECT_RSP ; 
 void* FALSE ; 
 int IB_CFG_DONE ; 
 size_t L2CAP_BASE_APPL_CID ; 
 int L2CAP_CFG_FLAGS_MASK_CONT ; 
 int /*<<< orphan*/  L2CAP_CFG_PENDING ; 
 int /*<<< orphan*/  L2CAP_CHNL_CFG_TIMEOUT ; 
 int /*<<< orphan*/  L2CAP_CHNL_DISCONNECT_TOUT ; 
 int /*<<< orphan*/  L2CAP_FCR_ERTM_MODE ; 
 size_t L2CAP_FIRST_FIXED_CHNL ; 
 size_t L2CAP_LAST_FIXED_CHNL ; 
 int /*<<< orphan*/  L2CAP_PEER_CFG_DISCONNECT ; 
 int /*<<< orphan*/  L2CAP_PEER_CFG_OK ; 
 int /*<<< orphan*/  L2CAP_TRACE_API (char*,int,...) ; 
 int /*<<< orphan*/  L2CAP_TRACE_EVENT (char*,...) ; 
 int /*<<< orphan*/  L2CAP_TRACE_WARNING (char*,int) ; 
#define  L2CEVT_L2CAP_CONFIG_REQ 139 
#define  L2CEVT_L2CAP_CONFIG_RSP 138 
#define  L2CEVT_L2CAP_CONFIG_RSP_NEG 137 
#define  L2CEVT_L2CAP_DATA 136 
#define  L2CEVT_L2CAP_DISCONNECT_REQ 135 
#define  L2CEVT_L2CA_CONFIG_REQ 134 
#define  L2CEVT_L2CA_CONFIG_RSP 133 
#define  L2CEVT_L2CA_CONFIG_RSP_NEG 132 
#define  L2CEVT_L2CA_DATA_WRITE 131 
#define  L2CEVT_L2CA_DISCONNECT_REQ 130 
#define  L2CEVT_LP_DISCONNECT_IND 129 
#define  L2CEVT_TIMEOUT 128 
 int OB_CFG_DONE ; 
 int RECONFIG_FLAG ; 
 void* TRUE ; 
 int /*<<< orphan*/  btu_start_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btu_stop_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fixed_queue_is_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2c_csm_get_event_name (int) ; 
 int /*<<< orphan*/  l2c_enqueue_peer_data (TYPE_9__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2c_fcr_adj_monitor_retran_timeout (TYPE_9__*) ; 
 void* l2c_fcr_renegotiate_chan (TYPE_9__*,TYPE_10__*) ; 
 int /*<<< orphan*/  l2c_fcr_start_timer (TYPE_9__*) ; 
 int /*<<< orphan*/  l2c_link_adjust_chnl_allocation () ; 
 int /*<<< orphan*/  l2c_link_check_send_pkts (TYPE_30__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_29__ l2cb ; 
 int /*<<< orphan*/  l2cu_disconnect_chnl (TYPE_9__*) ; 
 int /*<<< orphan*/  l2cu_process_our_cfg_req (TYPE_9__*,TYPE_10__*) ; 
 int /*<<< orphan*/  l2cu_process_our_cfg_rsp (TYPE_9__*,TYPE_10__*) ; 
 int /*<<< orphan*/  l2cu_process_peer_cfg_req (TYPE_9__*,TYPE_10__*) ; 
 int /*<<< orphan*/  l2cu_process_peer_cfg_rsp (TYPE_9__*,TYPE_10__*) ; 
 int /*<<< orphan*/  l2cu_release_ccb (TYPE_9__*) ; 
 int /*<<< orphan*/  l2cu_send_peer_config_req (TYPE_9__*,TYPE_10__*) ; 
 int /*<<< orphan*/  l2cu_send_peer_config_rsp (TYPE_9__*,TYPE_10__*) ; 
 int /*<<< orphan*/  l2cu_send_peer_disc_req (TYPE_9__*) ; 
 int /*<<< orphan*/  osi_free (void*) ; 
 void* osi_time_get_os_boottime_ms () ; 
 int /*<<< orphan*/  stub1 (int,void*) ; 
 int /*<<< orphan*/  stub10 (int,void*) ; 
 int /*<<< orphan*/  stub2 (int,TYPE_10__*) ; 
 int /*<<< orphan*/  stub3 (int,void*) ; 
 int /*<<< orphan*/  stub4 (int,TYPE_10__*) ; 
 int /*<<< orphan*/  stub5 (int,TYPE_10__*) ; 
 int /*<<< orphan*/  stub6 (int,void*) ; 
 int /*<<< orphan*/  stub7 (int,void*) ; 
 int /*<<< orphan*/  stub8 (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub9 (size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void l2c_csm_config (tL2C_CCB *p_ccb, UINT16 event, void *p_data)
{
    tL2CAP_CFG_INFO         *p_cfg = (tL2CAP_CFG_INFO *)p_data;
    tL2CA_DISCONNECT_IND_CB *disconnect_ind = p_ccb->p_rcb->api.pL2CA_DisconnectInd_Cb;
    UINT16                  local_cid = p_ccb->local_cid;
    UINT8                   cfg_result;

#if (BT_TRACE_VERBOSE == TRUE)
    L2CAP_TRACE_EVENT ("L2CAP - LCID: 0x%04x  st: CONFIG  evt: %s", p_ccb->local_cid, l2c_csm_get_event_name (event));
#else
    L2CAP_TRACE_EVENT ("L2CAP - st: CONFIG evt: %d", event);
#endif

    switch (event) {
    case L2CEVT_LP_DISCONNECT_IND:                  /* Link was disconnected */
        L2CAP_TRACE_API ("L2CAP - Calling Disconnect_Ind_Cb(), CID: 0x%04x  No Conf Needed", p_ccb->local_cid);
        l2cu_release_ccb (p_ccb);
        (*disconnect_ind)(local_cid, FALSE);
        break;

    case L2CEVT_L2CAP_CONFIG_REQ:                  /* Peer config request   */

        if ((cfg_result = l2cu_process_peer_cfg_req (p_ccb, p_cfg)) == L2CAP_PEER_CFG_OK) {
            L2CAP_TRACE_EVENT ("L2CAP - Calling Config_Req_Cb(), CID: 0x%04x, C-bit %d",
                               p_ccb->local_cid, (p_cfg->flags & L2CAP_CFG_FLAGS_MASK_CONT));
            (*p_ccb->p_rcb->api.pL2CA_ConfigInd_Cb)(p_ccb->local_cid, p_cfg);
        } else if (cfg_result == L2CAP_PEER_CFG_DISCONNECT) {
            /* Disconnect if channels are incompatible */
            L2CAP_TRACE_EVENT ("L2CAP - incompatible configurations disconnect");
            l2cu_disconnect_chnl (p_ccb);
        } else { /* Return error to peer so he can renegotiate if possible */
            L2CAP_TRACE_EVENT ("L2CAP - incompatible configurations trying reconfig");
            l2cu_send_peer_config_rsp (p_ccb, p_cfg);
        }
        break;

    case L2CEVT_L2CAP_CONFIG_RSP:                  /* Peer config response  */
        l2cu_process_peer_cfg_rsp (p_ccb, p_cfg);

        if (p_cfg->result != L2CAP_CFG_PENDING) {
            /* TBD: When config options grow beyong minimum MTU (48 bytes)
             *      logic needs to be added to handle responses with
             *      continuation bit set in flags field.
             *       1. Send additional config request out until C-bit is cleared in response
             */
            p_ccb->config_done |= OB_CFG_DONE;

            if (p_ccb->config_done & IB_CFG_DONE) {
                /* Verify two sides are in compatible modes before continuing */
                if (p_ccb->our_cfg.fcr.mode != p_ccb->peer_cfg.fcr.mode) {
                    l2cu_send_peer_disc_req (p_ccb);
                    L2CAP_TRACE_WARNING ("L2CAP - Calling Disconnect_Ind_Cb(Incompatible CFG), CID: 0x%04x  No Conf Needed", p_ccb->local_cid);
                    l2cu_release_ccb (p_ccb);
                    (*disconnect_ind)(local_cid, FALSE);
                    break;
                }

                p_ccb->config_done |= RECONFIG_FLAG;
                p_ccb->chnl_state = CST_OPEN;
                l2c_link_adjust_chnl_allocation ();
                btu_stop_timer (&p_ccb->timer_entry);

                /* If using eRTM and waiting for an ACK, restart the ACK timer */
                if (p_ccb->fcrb.wait_ack) {
                    l2c_fcr_start_timer(p_ccb);
                }

                /*
                ** check p_ccb->our_cfg.fcr.mon_tout and p_ccb->our_cfg.fcr.rtrans_tout
                ** we may set them to zero when sending config request during renegotiation
                */
                if ((p_ccb->our_cfg.fcr.mode == L2CAP_FCR_ERTM_MODE)
                        && ((p_ccb->our_cfg.fcr.mon_tout == 0) || (p_ccb->our_cfg.fcr.rtrans_tout))) {
                    l2c_fcr_adj_monitor_retran_timeout (p_ccb);
                }

#if (L2CAP_ERTM_STATS == TRUE)
                p_ccb->fcrb.connect_tick_count = osi_time_get_os_boottime_ms();
#endif
                /* See if we can forward anything on the hold queue */
                if (!fixed_queue_is_empty(p_ccb->xmit_hold_q)) {
                    l2c_link_check_send_pkts (p_ccb->p_lcb, NULL, NULL);
                }
            }
        }

        L2CAP_TRACE_API ("L2CAP - Calling Config_Rsp_Cb(), CID: 0x%04x", p_ccb->local_cid);
        (*p_ccb->p_rcb->api.pL2CA_ConfigCfm_Cb)(p_ccb->local_cid, p_cfg);
        break;

    case L2CEVT_L2CAP_CONFIG_RSP_NEG:              /* Peer config error rsp */
        /* Disable the Timer */
        btu_stop_timer (&p_ccb->timer_entry);

        /* If failure was channel mode try to renegotiate */
        if (l2c_fcr_renegotiate_chan(p_ccb, p_cfg) == FALSE) {
            L2CAP_TRACE_API ("L2CAP - Calling Config_Rsp_Cb(), CID: 0x%04x, Failure: %d", p_ccb->local_cid, p_cfg->result);
            (*p_ccb->p_rcb->api.pL2CA_ConfigCfm_Cb)(p_ccb->local_cid, p_cfg);
        }
        break;

    case L2CEVT_L2CAP_DISCONNECT_REQ:                  /* Peer disconnected request */
        btu_start_timer (&p_ccb->timer_entry, BTU_TTYPE_L2CAP_CHNL, L2CAP_CHNL_DISCONNECT_TOUT);
        p_ccb->chnl_state = CST_W4_L2CA_DISCONNECT_RSP;
        L2CAP_TRACE_API ("L2CAP - Calling Disconnect_Ind_Cb(), CID: 0x%04x  Conf Needed", p_ccb->local_cid);
        (*p_ccb->p_rcb->api.pL2CA_DisconnectInd_Cb)(p_ccb->local_cid, TRUE);
        break;

    case L2CEVT_L2CA_CONFIG_REQ:                   /* Upper layer config req   */
        l2cu_process_our_cfg_req (p_ccb, p_cfg);
        l2cu_send_peer_config_req (p_ccb, p_cfg);
        btu_start_timer (&p_ccb->timer_entry, BTU_TTYPE_L2CAP_CHNL, L2CAP_CHNL_CFG_TIMEOUT);
        break;

    case L2CEVT_L2CA_CONFIG_RSP:                   /* Upper layer config rsp   */
        l2cu_process_our_cfg_rsp (p_ccb, p_cfg);

        /* Not finished if continuation flag is set */
        if ( (p_cfg->flags & L2CAP_CFG_FLAGS_MASK_CONT) || (p_cfg->result == L2CAP_CFG_PENDING) ) {
            /* Send intermediate response; remain in cfg state */
            l2cu_send_peer_config_rsp (p_ccb, p_cfg);
            break;
        }

        /* Local config done; clear cached configuration in case reconfig takes place later */
        p_ccb->peer_cfg.mtu_present = FALSE;
        p_ccb->peer_cfg.flush_to_present = FALSE;
        p_ccb->peer_cfg.qos_present = FALSE;

        p_ccb->config_done |= IB_CFG_DONE;

        if (p_ccb->config_done & OB_CFG_DONE) {
            /* Verify two sides are in compatible modes before continuing */
            if (p_ccb->our_cfg.fcr.mode != p_ccb->peer_cfg.fcr.mode) {
                l2cu_send_peer_disc_req (p_ccb);
                L2CAP_TRACE_WARNING ("L2CAP - Calling Disconnect_Ind_Cb(Incompatible CFG), CID: 0x%04x  No Conf Needed", p_ccb->local_cid);
                l2cu_release_ccb (p_ccb);
                (*disconnect_ind)(local_cid, FALSE);
                break;
            }

            p_ccb->config_done |= RECONFIG_FLAG;
            p_ccb->chnl_state = CST_OPEN;
            l2c_link_adjust_chnl_allocation ();
            btu_stop_timer (&p_ccb->timer_entry);
        }

        l2cu_send_peer_config_rsp (p_ccb, p_cfg);

        /* If using eRTM and waiting for an ACK, restart the ACK timer */
        if (p_ccb->fcrb.wait_ack) {
            l2c_fcr_start_timer(p_ccb);
        }

#if (L2CAP_ERTM_STATS == TRUE)
        p_ccb->fcrb.connect_tick_count = osi_time_get_os_boottime_ms();
#endif

        /* See if we can forward anything on the hold queue */
        if ( (p_ccb->chnl_state == CST_OPEN) &&
             (!fixed_queue_is_empty(p_ccb->xmit_hold_q))) {
            l2c_link_check_send_pkts (p_ccb->p_lcb, NULL, NULL);
        }
        break;

    case L2CEVT_L2CA_CONFIG_RSP_NEG:               /* Upper layer config reject */
        l2cu_send_peer_config_rsp (p_ccb, p_cfg);
        btu_start_timer (&p_ccb->timer_entry, BTU_TTYPE_L2CAP_CHNL, L2CAP_CHNL_CFG_TIMEOUT);
        break;

    case L2CEVT_L2CA_DISCONNECT_REQ:                 /* Upper wants to disconnect */
        l2cu_send_peer_disc_req (p_ccb);
        p_ccb->chnl_state = CST_W4_L2CAP_DISCONNECT_RSP;
        btu_start_timer (&p_ccb->timer_entry, BTU_TTYPE_L2CAP_CHNL, L2CAP_CHNL_DISCONNECT_TOUT);
        break;

    case L2CEVT_L2CAP_DATA:                        /* Peer data packet rcvd    */
        L2CAP_TRACE_API ("L2CAP - Calling DataInd_Cb(), CID: 0x%04x", p_ccb->local_cid);
#if (L2CAP_NUM_FIXED_CHNLS > 0)
        if (p_ccb->local_cid >= L2CAP_FIRST_FIXED_CHNL &&
                p_ccb->local_cid <= L2CAP_LAST_FIXED_CHNL) {
            if (p_ccb->local_cid < L2CAP_BASE_APPL_CID) {
                if (l2cb.fixed_reg[p_ccb->local_cid - L2CAP_FIRST_FIXED_CHNL].pL2CA_FixedData_Cb) {
                    (*l2cb.fixed_reg[p_ccb->local_cid - L2CAP_FIRST_FIXED_CHNL].pL2CA_FixedData_Cb)
                    (p_ccb->local_cid, p_ccb->p_lcb->remote_bd_addr, (BT_HDR *)p_data);
                } else {
                    osi_free (p_data);
                }
                break;
            }
        }
#endif
        (*p_ccb->p_rcb->api.pL2CA_DataInd_Cb)(p_ccb->local_cid, (BT_HDR *)p_data);
        break;

    case L2CEVT_L2CA_DATA_WRITE:                   /* Upper layer data to send */
        if (p_ccb->config_done & OB_CFG_DONE) {
            l2c_enqueue_peer_data (p_ccb, (BT_HDR *)p_data);
        } else {
            osi_free (p_data);
        }
        break;

    case L2CEVT_TIMEOUT:
        l2cu_send_peer_disc_req (p_ccb);
        L2CAP_TRACE_API ("L2CAP - Calling Disconnect_Ind_Cb(), CID: 0x%04x  No Conf Needed",
                         p_ccb->local_cid);
        l2cu_release_ccb (p_ccb);
        (*disconnect_ind)(local_cid, FALSE);
        break;
    }
}