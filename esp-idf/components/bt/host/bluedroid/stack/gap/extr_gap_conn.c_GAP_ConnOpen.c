#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {void* allowed_modes; void* fcr_tx_buf_size; void* fcr_rx_buf_size; void* user_tx_buf_size; void* user_rx_buf_size; int /*<<< orphan*/  preferred_mode; } ;
typedef  TYPE_3__ tL2CAP_ERTM_INFO ;
struct TYPE_14__ {int /*<<< orphan*/  mode; } ;
struct TYPE_16__ {TYPE_2__ fcr; scalar_t__ fcr_present; } ;
typedef  TYPE_4__ tL2CAP_CFG_INFO ;
typedef  int /*<<< orphan*/  tGAP_CONN_CALLBACK ;
struct TYPE_17__ {int gap_handle; int connection_id; TYPE_3__ ertm_info; int /*<<< orphan*/  psm; int /*<<< orphan*/  con_flags; int /*<<< orphan*/  con_state; TYPE_4__ cfg; void* service_id; int /*<<< orphan*/ * p_callback; int /*<<< orphan*/  rem_addr_specified; int /*<<< orphan*/ * rem_dev_address; } ;
typedef  TYPE_5__ tGAP_CCB ;
typedef  void* UINT8 ;
typedef  int UINT16 ;
struct TYPE_19__ {int /*<<< orphan*/ * pL2CA_ConnectInd_Cb; int /*<<< orphan*/ * pAMP_ConnectInd_Cb; } ;
struct TYPE_13__ {TYPE_9__ reg_info; } ;
struct TYPE_18__ {TYPE_1__ conn; } ;
typedef  scalar_t__ BOOLEAN ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int AMP_AUTOSWITCH_ALLOWED ; 
 int AMP_USE_AMP_IF_POSSIBLE ; 
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 int BTM_SEC_OUT_AUTHENTICATE ; 
 int BTM_SEC_OUT_AUTHORIZE ; 
 int BTM_SEC_OUT_ENCRYPT ; 
 int /*<<< orphan*/  BTM_SetSecurityLevel (void*,char const*,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BT_BD_ANY ; 
 int /*<<< orphan*/  GAP_CCB_FLAGS_IS_ORIG ; 
 int /*<<< orphan*/  GAP_CCB_FLAGS_SEC_DONE ; 
 int /*<<< orphan*/  GAP_CCB_STATE_CONN_SETUP ; 
 int /*<<< orphan*/  GAP_CCB_STATE_LISTENING ; 
 void* GAP_DATA_BUF_SIZE ; 
 int GAP_INVALID_HANDLE ; 
 int /*<<< orphan*/  GAP_TRACE_ERROR (char*,...) ; 
 int /*<<< orphan*/  GAP_TRACE_EVENT (char*) ; 
 scalar_t__ L2CAP_FCR_CHAN_OPT_BASIC ; 
 void* L2CAP_INVALID_ERM_BUF_SIZE ; 
 int L2CA_CONNECT_REQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  L2CA_REGISTER (int,TYPE_9__*,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bt_uuid ; 
 TYPE_5__* gap_allocate_ccb () ; 
 TYPE_7__ gap_cb ; 
 void* gap_connect_ind ; 
 int /*<<< orphan*/  gap_release_ccb (TYPE_5__*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

UINT16 GAP_ConnOpen (const char *p_serv_name, UINT8 service_id, BOOLEAN is_server,
                     BD_ADDR p_rem_bda, UINT16 psm, tL2CAP_CFG_INFO *p_cfg,
                     tL2CAP_ERTM_INFO *ertm_info, UINT16 security, UINT8 chan_mode_mask,
                     tGAP_CONN_CALLBACK *p_cb)
{
    tGAP_CCB    *p_ccb;
    UINT16       cid;
    //tBT_UUID    bt_uuid = {2, {GAP_PROTOCOL_ID}};

    GAP_TRACE_EVENT ("GAP_CONN - Open Request");

    /* Allocate a new CCB. Return if none available. */
    if ((p_ccb = gap_allocate_ccb()) == NULL) {
        return (GAP_INVALID_HANDLE);
    }

    /* If caller specified a BD address, save it */
    if (p_rem_bda) {
        /* the bd addr is not BT_BD_ANY, then a bd address was specified */
        if (memcmp (p_rem_bda, BT_BD_ANY, BD_ADDR_LEN)) {
            p_ccb->rem_addr_specified = TRUE;
        }

        memcpy (&p_ccb->rem_dev_address[0], p_rem_bda, BD_ADDR_LEN);
    } else if (!is_server) {
        /* remore addr is not specified and is not a server -> bad */
        return (GAP_INVALID_HANDLE);
    }

    /* A client MUST have specified a bd addr to connect with */
    if (!p_ccb->rem_addr_specified && !is_server) {
        gap_release_ccb (p_ccb);
        GAP_TRACE_ERROR ("GAP ERROR: Client must specify a remote BD ADDR to connect to!");
        return (GAP_INVALID_HANDLE);
    }

    /* Check if configuration was specified */
    if (p_cfg) {
        p_ccb->cfg = *p_cfg;
    }

    p_ccb->p_callback     = p_cb;

    /* If originator, use a dynamic PSM */
#if ((defined AMP_INCLUDED) && (AMP_INCLUDED == TRUE))
    if (!is_server) {
        gap_cb.conn.reg_info.pAMP_ConnectInd_Cb  = NULL;
    } else {
        gap_cb.conn.reg_info.pAMP_ConnectInd_Cb  = gap_connect_ind;
    }
#else
    if (!is_server) {
        gap_cb.conn.reg_info.pL2CA_ConnectInd_Cb = NULL;
    } else {
        gap_cb.conn.reg_info.pL2CA_ConnectInd_Cb = gap_connect_ind;
    }
#endif

    /* Register the PSM with L2CAP */
    if ((p_ccb->psm = L2CA_REGISTER (psm, &gap_cb.conn.reg_info,
                                     AMP_AUTOSWITCH_ALLOWED | AMP_USE_AMP_IF_POSSIBLE)) == 0) {
        GAP_TRACE_ERROR ("GAP_ConnOpen: Failure registering PSM 0x%04x", psm);
        gap_release_ccb (p_ccb);
        return (GAP_INVALID_HANDLE);
    }

    /* Register with Security Manager for the specific security level */
    p_ccb->service_id = service_id;
    if (!BTM_SetSecurityLevel ((UINT8)!is_server, p_serv_name,
                               p_ccb->service_id, security, p_ccb->psm, 0, 0)) {
        GAP_TRACE_ERROR ("GAP_CONN - Security Error");
        gap_release_ccb (p_ccb);
        return (GAP_INVALID_HANDLE);
    }

    /* Fill in eL2CAP parameter data */
    if ( p_ccb->cfg.fcr_present ) {
        if (ertm_info == NULL) {
            p_ccb->ertm_info.preferred_mode = p_ccb->cfg.fcr.mode;
            p_ccb->ertm_info.user_rx_buf_size = GAP_DATA_BUF_SIZE;
            p_ccb->ertm_info.user_tx_buf_size = GAP_DATA_BUF_SIZE;
            p_ccb->ertm_info.fcr_rx_buf_size = L2CAP_INVALID_ERM_BUF_SIZE;
            p_ccb->ertm_info.fcr_tx_buf_size = L2CAP_INVALID_ERM_BUF_SIZE;
        } else {
            p_ccb->ertm_info = *ertm_info;
        }
    }

    /* optional FCR channel modes */
    if (ertm_info != NULL) {
        p_ccb->ertm_info.allowed_modes =
            (chan_mode_mask) ? chan_mode_mask : (UINT8)L2CAP_FCR_CHAN_OPT_BASIC;
    }

    if (is_server) {
        p_ccb->con_flags |= GAP_CCB_FLAGS_SEC_DONE; /* assume btm/l2cap would handle it */
        p_ccb->con_state = GAP_CCB_STATE_LISTENING;
        return (p_ccb->gap_handle);
    } else {
        /* We are the originator of this connection */
        p_ccb->con_flags = GAP_CCB_FLAGS_IS_ORIG;

        /* Transition to the next appropriate state, waiting for connection confirm. */
        p_ccb->con_state = GAP_CCB_STATE_CONN_SETUP;

        /* mark security done flag, when security is not required */
        if ((security & (BTM_SEC_OUT_AUTHORIZE | BTM_SEC_OUT_AUTHENTICATE | BTM_SEC_OUT_ENCRYPT) ) == 0) {
            p_ccb->con_flags |= GAP_CCB_FLAGS_SEC_DONE;
        }

        /* Check if L2CAP started the connection process */
        if (p_rem_bda && ((cid = L2CA_CONNECT_REQ (p_ccb->psm, p_rem_bda, &p_ccb->ertm_info, &bt_uuid)) != 0)) {
            p_ccb->connection_id = cid;
            return (p_ccb->gap_handle);
        } else {
            gap_release_ccb (p_ccb);
            return (GAP_INVALID_HANDLE);
        }
    }
}