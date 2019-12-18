#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tSDP_CB ;
struct TYPE_7__ {int /*<<< orphan*/ * pL2CA_TxComplete_Cb; int /*<<< orphan*/ * pL2CA_CongestionStatus_Cb; int /*<<< orphan*/  pL2CA_DataInd_Cb; int /*<<< orphan*/ * pL2CA_QoSViolationInd_Cb; int /*<<< orphan*/  pL2CA_DisconnectCfm_Cb; int /*<<< orphan*/  pL2CA_DisconnectInd_Cb; int /*<<< orphan*/  pL2CA_ConfigCfm_Cb; int /*<<< orphan*/  pL2CA_ConfigInd_Cb; int /*<<< orphan*/ * pL2CA_ConnectPnd_Cb; int /*<<< orphan*/  pL2CA_ConnectCfm_Cb; int /*<<< orphan*/  pL2CA_ConnectInd_Cb; } ;
struct TYPE_5__ {int /*<<< orphan*/  flush_to; void* flush_to_present; void* mtu; void* mtu_present; } ;
struct TYPE_6__ {TYPE_4__ reg_info; int /*<<< orphan*/  trace_level; int /*<<< orphan*/  max_recs_per_search; void* max_attr_list_size; TYPE_1__ l2cap_my_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_SEC_SERVICE_SDP_SERVER ; 
 int /*<<< orphan*/  BTM_SetSecurityLevel (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BT_TRACE_LEVEL_NONE ; 
 void* FALSE ; 
 int /*<<< orphan*/  L2CA_Register (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  SDP_FLUSH_TO ; 
 int /*<<< orphan*/  SDP_INITIAL_TRACE_LEVEL ; 
 int /*<<< orphan*/  SDP_MAX_DISC_SERVER_RECS ; 
 void* SDP_MTU_SIZE ; 
 int /*<<< orphan*/  SDP_PSM ; 
 int /*<<< orphan*/  SDP_SECURITY_LEVEL ; 
 int /*<<< orphan*/  SDP_SERVICE_NAME ; 
 int /*<<< orphan*/  SDP_TRACE_ERROR (char*) ; 
 void* TRUE ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ osi_malloc (int) ; 
 TYPE_2__ sdp_cb ; 
 int /*<<< orphan*/ * sdp_cb_ptr ; 
 int /*<<< orphan*/  sdp_config_cfm ; 
 int /*<<< orphan*/  sdp_config_ind ; 
 int /*<<< orphan*/  sdp_connect_cfm ; 
 int /*<<< orphan*/  sdp_connect_ind ; 
 int /*<<< orphan*/  sdp_data_ind ; 
 int /*<<< orphan*/  sdp_disconnect_cfm ; 
 int /*<<< orphan*/  sdp_disconnect_ind ; 

void sdp_init (void)
{
#if SDP_DYNAMIC_MEMORY
    sdp_cb_ptr = (tSDP_CB *)osi_malloc(sizeof(tSDP_CB));
#endif /* #if SDP_DYNAMIC_MEMORY */
    /* Clears all structures and local SDP database (if Server is enabled) */
    memset (&sdp_cb, 0, sizeof (tSDP_CB));

    /* Initialize the L2CAP configuration. We only care about MTU and flush */
    sdp_cb.l2cap_my_cfg.mtu_present       = TRUE;
    sdp_cb.l2cap_my_cfg.mtu               = SDP_MTU_SIZE;
    sdp_cb.l2cap_my_cfg.flush_to_present  = TRUE;
    sdp_cb.l2cap_my_cfg.flush_to          = SDP_FLUSH_TO;

    sdp_cb.max_attr_list_size             = SDP_MTU_SIZE - 16;
    sdp_cb.max_recs_per_search            = SDP_MAX_DISC_SERVER_RECS;

#if SDP_SERVER_ENABLED == TRUE
    /* Register with Security Manager for the specific security level */
    if (!BTM_SetSecurityLevel (FALSE, SDP_SERVICE_NAME, BTM_SEC_SERVICE_SDP_SERVER,
                               SDP_SECURITY_LEVEL, SDP_PSM, 0, 0)) {
        SDP_TRACE_ERROR ("Security Registration Server failed\n");
        return;
    }
#endif

#if SDP_CLIENT_ENABLED == TRUE
    /* Register with Security Manager for the specific security level */
    if (!BTM_SetSecurityLevel (TRUE, SDP_SERVICE_NAME, BTM_SEC_SERVICE_SDP_SERVER,
                               SDP_SECURITY_LEVEL, SDP_PSM, 0, 0)) {
        SDP_TRACE_ERROR ("Security Registration for Client failed\n");
        return;
    }
#endif

#if defined(SDP_INITIAL_TRACE_LEVEL)
    sdp_cb.trace_level = SDP_INITIAL_TRACE_LEVEL;
#else
    sdp_cb.trace_level = BT_TRACE_LEVEL_NONE;    /* No traces */
#endif

    sdp_cb.reg_info.pL2CA_ConnectInd_Cb = sdp_connect_ind;
    sdp_cb.reg_info.pL2CA_ConnectCfm_Cb = sdp_connect_cfm;
    sdp_cb.reg_info.pL2CA_ConnectPnd_Cb = NULL;
    sdp_cb.reg_info.pL2CA_ConfigInd_Cb  = sdp_config_ind;
    sdp_cb.reg_info.pL2CA_ConfigCfm_Cb  = sdp_config_cfm;
    sdp_cb.reg_info.pL2CA_DisconnectInd_Cb = sdp_disconnect_ind;
    sdp_cb.reg_info.pL2CA_DisconnectCfm_Cb = sdp_disconnect_cfm;
    sdp_cb.reg_info.pL2CA_QoSViolationInd_Cb = NULL;
    sdp_cb.reg_info.pL2CA_DataInd_Cb = sdp_data_ind;
    sdp_cb.reg_info.pL2CA_CongestionStatus_Cb = NULL;
    sdp_cb.reg_info.pL2CA_TxComplete_Cb       = NULL;

    /* Now, register with L2CAP */
    if (!L2CA_Register (SDP_PSM, &sdp_cb.reg_info)) {
        SDP_TRACE_ERROR ("SDP Registration failed\n");
    }
}