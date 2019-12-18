#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ call_ind; scalar_t__ callsetup_ind; scalar_t__ post_sco; scalar_t__ retry_with_sco_only; int /*<<< orphan*/  codec_msbc_settings; int /*<<< orphan*/  peer_addr; int /*<<< orphan*/  app_id; int /*<<< orphan*/  inuse_codec; scalar_t__ svc_conn; scalar_t__ codec_fallback; int /*<<< orphan*/  sco_idx; } ;
typedef  TYPE_2__ tBTA_AG_SCB ;
typedef  int /*<<< orphan*/  tBTA_AG_DATA ;
typedef  int /*<<< orphan*/  sco_state_t ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_10__ {scalar_t__ p_xfer_scb; int /*<<< orphan*/ * p_curr_scb; } ;
struct TYPE_12__ {TYPE_1__ sco; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_AG_AUDIO_CLOSE_EVT ; 
 scalar_t__ BTA_AG_CALLSETUP_NONE ; 
 scalar_t__ BTA_AG_CALL_INACTIVE ; 
 scalar_t__ BTA_AG_POST_SCO_CALL_END ; 
 int /*<<< orphan*/  BTA_AG_SCO_CONN_CLOSE_E ; 
 int /*<<< orphan*/  BTA_AG_SCO_MSBC_SETTINGS_T2 ; 
 int /*<<< orphan*/  BTA_AG_SCO_REOPEN_E ; 
 int /*<<< orphan*/  BTA_ID_AG ; 
 int /*<<< orphan*/  BTM_INVALID_SCO_INDEX ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SCO_STATE_OFF ; 
 int /*<<< orphan*/  SCO_STATE_OFF_TRANSFER ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 scalar_t__ bta_ag_attempt_msbc_safe_settings (TYPE_2__*) ; 
 TYPE_8__ bta_ag_cb ; 
 int /*<<< orphan*/  bta_ag_cback_sco (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_ag_create_sco (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_ag_scb_to_idx (TYPE_2__*) ; 
 int /*<<< orphan*/  bta_ag_sco_audio_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  bta_ag_sco_event (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_sys_sco_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_sys_sco_unuse (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void bta_ag_sco_conn_close(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data)
{
    UINT16 handle = bta_ag_scb_to_idx(p_scb);
    UNUSED(p_data);

    /* clear current scb */
    bta_ag_cb.sco.p_curr_scb = NULL;
    p_scb->sco_idx = BTM_INVALID_SCO_INDEX;

#if (BTM_WBS_INCLUDED == TRUE)
    /* codec_fallback is set when AG is initiator and connection failed for mSBC. */
    /* OR if codec is msbc and T2 settings failed, then retry Safe T1 settings */
    if ((p_scb->codec_fallback && p_scb->svc_conn) ||
         bta_ag_attempt_msbc_safe_settings(p_scb))
    {
        bta_ag_sco_event(p_scb, BTA_AG_SCO_REOPEN_E);
    }
    else if (p_scb->retry_with_sco_only && p_scb->svc_conn)
    {
        /* retry_with_sco_only is set when AG is initiator and connection failed for eSCO */
        bta_ag_create_sco(p_scb, TRUE);
    }
#else
    /* retry_with_sco_only, will be set only when AG is initiator
    ** and AG is first trying to establish an eSCO connection */
    if (p_scb->retry_with_sco_only && p_scb->svc_conn)
    {
        bta_ag_create_sco(p_scb, TRUE);
    }
#endif
    else
    {
        sco_state_t sco_state = bta_ag_cb.sco.p_xfer_scb ? SCO_STATE_OFF_TRANSFER : SCO_STATE_OFF;
#if (BTM_WBS_INCLUDED == TRUE)
        /* Indicate if the closing of audio is because of transfer */
        bta_ag_sco_audio_state(handle, p_scb->app_id, sco_state, p_scb->inuse_codec);
#else
        /* Indicate if the closing of audio is because of transfer */
        bta_ag_sco_audio_state(handle, p_scb->app_id, sco_state);
#endif
        bta_ag_sco_event(p_scb, BTA_AG_SCO_CONN_CLOSE_E);

        bta_sys_sco_close(BTA_ID_AG, p_scb->app_id, p_scb->peer_addr);

        /* if av got suspended by this call, let it resume. */
        /* In case call stays alive regardless of sco, av should not be affected. */
        if(((p_scb->call_ind == BTA_AG_CALL_INACTIVE) && (p_scb->callsetup_ind == BTA_AG_CALLSETUP_NONE))
            || (p_scb->post_sco == BTA_AG_POST_SCO_CALL_END))
        {
            bta_sys_sco_unuse(BTA_ID_AG, p_scb->app_id, p_scb->peer_addr);
        }

        /* call app callback */
        bta_ag_cback_sco(p_scb, BTA_AG_AUDIO_CLOSE_EVT);
#if (BTM_WBS_INCLUDED == TRUE)
        p_scb->codec_msbc_settings = BTA_AG_SCO_MSBC_SETTINGS_T2;
#endif
    }
    p_scb->retry_with_sco_only = FALSE;
}