#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * pL2CA_TxComplete_Cb; void* pL2CA_CongestionStatus_Cb; void* pL2CA_DataInd_Cb; int /*<<< orphan*/ * pL2CA_QoSViolationInd_Cb; int /*<<< orphan*/ * pL2CA_DisconnectCfm_Cb; void* pL2CA_DisconnectInd_Cb; void* pL2CA_ConfigCfm_Cb; void* pL2CA_ConfigInd_Cb; int /*<<< orphan*/ * pL2CA_ConnectPnd_Cb; void* pL2CA_ConnectCfm_Cb; void* pL2CA_ConnectInd_Cb; int /*<<< orphan*/ * pAMP_MoveCfmRsp_Cb; int /*<<< orphan*/ * pAMP_MoveCfm_Cb; int /*<<< orphan*/ * pAMP_MoveRsp_Cb; int /*<<< orphan*/ * pAMP_MoveInd_Cb; int /*<<< orphan*/ * pAMP_TxComplete_Cb; void* pAMP_CongestionStatus_Cb; void* pAMP_DataInd_Cb; int /*<<< orphan*/ * pAMP_QoSViolationInd_Cb; int /*<<< orphan*/ * pAMP_DisconnectCfm_Cb; void* pAMP_DisconnectInd_Cb; void* pAMP_ConfigCfm_Cb; void* pAMP_ConfigInd_Cb; int /*<<< orphan*/ * pAMP_ConnectPnd_Cb; void* pAMP_ConnectCfm_Cb; void* pAMP_ConnectInd_Cb; } ;
struct TYPE_5__ {TYPE_1__ reg_info; } ;
struct TYPE_6__ {TYPE_2__ conn; } ;

/* Variables and functions */
 TYPE_3__ gap_cb ; 
 void* gap_config_cfm ; 
 void* gap_config_ind ; 
 void* gap_congestion_ind ; 
 void* gap_connect_cfm ; 
 void* gap_connect_ind ; 
 void* gap_data_ind ; 
 void* gap_disconnect_ind ; 

void gap_conn_init (void)
{
#if ((defined AMP_INCLUDED) && (AMP_INCLUDED == TRUE))
    gap_cb.conn.reg_info.pAMP_ConnectInd_Cb         = gap_connect_ind;
    gap_cb.conn.reg_info.pAMP_ConnectCfm_Cb         = gap_connect_cfm;
    gap_cb.conn.reg_info.pAMP_ConnectPnd_Cb         = NULL;
    gap_cb.conn.reg_info.pAMP_ConfigInd_Cb          = gap_config_ind;
    gap_cb.conn.reg_info.pAMP_ConfigCfm_Cb          = gap_config_cfm;
    gap_cb.conn.reg_info.pAMP_DisconnectInd_Cb      = gap_disconnect_ind;
    gap_cb.conn.reg_info.pAMP_DisconnectCfm_Cb      = NULL;
    gap_cb.conn.reg_info.pAMP_QoSViolationInd_Cb    = NULL;
    gap_cb.conn.reg_info.pAMP_DataInd_Cb            = gap_data_ind;
    gap_cb.conn.reg_info.pAMP_CongestionStatus_Cb   = gap_congestion_ind;
    gap_cb.conn.reg_info.pAMP_TxComplete_Cb         = NULL;
    gap_cb.conn.reg_info.pAMP_MoveInd_Cb            = NULL;
    gap_cb.conn.reg_info.pAMP_MoveRsp_Cb            = NULL;
    gap_cb.conn.reg_info.pAMP_MoveCfm_Cb            = NULL; //gap_move_cfm
    gap_cb.conn.reg_info.pAMP_MoveCfmRsp_Cb         = NULL; //gap_move_cfm_rsp

#else
    gap_cb.conn.reg_info.pL2CA_ConnectInd_Cb       = gap_connect_ind;
    gap_cb.conn.reg_info.pL2CA_ConnectCfm_Cb       = gap_connect_cfm;
    gap_cb.conn.reg_info.pL2CA_ConnectPnd_Cb       = NULL;
    gap_cb.conn.reg_info.pL2CA_ConfigInd_Cb        = gap_config_ind;
    gap_cb.conn.reg_info.pL2CA_ConfigCfm_Cb        = gap_config_cfm;
    gap_cb.conn.reg_info.pL2CA_DisconnectInd_Cb    = gap_disconnect_ind;
    gap_cb.conn.reg_info.pL2CA_DisconnectCfm_Cb    = NULL;
    gap_cb.conn.reg_info.pL2CA_QoSViolationInd_Cb  = NULL;
    gap_cb.conn.reg_info.pL2CA_DataInd_Cb          = gap_data_ind;
    gap_cb.conn.reg_info.pL2CA_CongestionStatus_Cb = gap_congestion_ind;
    gap_cb.conn.reg_info.pL2CA_TxComplete_Cb       = NULL;
#endif
}