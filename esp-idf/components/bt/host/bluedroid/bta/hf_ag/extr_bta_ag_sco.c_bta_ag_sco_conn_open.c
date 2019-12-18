#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  codec_msbc_settings; int /*<<< orphan*/  retry_with_sco_only; int /*<<< orphan*/  air_mode; int /*<<< orphan*/  app_id; int /*<<< orphan*/  inuse_codec; int /*<<< orphan*/  peer_addr; } ;
typedef  TYPE_1__ tBTA_AG_SCB ;
typedef  int /*<<< orphan*/  tBTA_AG_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_AG_AUDIO_OPEN_EVT ; 
 int /*<<< orphan*/  BTA_AG_CI_SCO_DATA_EVT ; 
 int /*<<< orphan*/  BTA_AG_SCO_CONN_OPEN_E ; 
 int /*<<< orphan*/  BTA_AG_SCO_MSBC_SETTINGS_T2 ; 
 int /*<<< orphan*/  BTA_HFP_SCO_OUT_PKT_SIZE ; 
 int /*<<< orphan*/  BTA_ID_AG ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SCO_STATE_ON ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bta_ag_cback_sco (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_ag_scb_to_idx (TYPE_1__*) ; 
 int /*<<< orphan*/  bta_ag_sco_audio_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  bta_ag_sco_co_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_ag_sco_event (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_sys_sco_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void bta_ag_sco_conn_open(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data)
{
    UNUSED(p_data);

    bta_ag_sco_event(p_scb, BTA_AG_SCO_CONN_OPEN_E);

    bta_sys_sco_open(BTA_ID_AG, p_scb->app_id, p_scb->peer_addr);

#if (BTM_SCO_HCI_INCLUDED == TRUE)

#if (BTM_WBS_INCLUDED == TRUE)
    bta_ag_sco_audio_state(bta_ag_scb_to_idx(p_scb), p_scb->app_id, SCO_STATE_ON, p_scb->inuse_codec);
#else
    bta_ag_sco_audio_state(bta_ag_scb_to_idx(p_scb), p_scb->app_id, SCO_STATE_ON);
#endif
    /* open SCO codec if SCO is routed through transport */
    bta_ag_sco_co_open(bta_ag_scb_to_idx(p_scb), p_scb->air_mode, BTA_HFP_SCO_OUT_PKT_SIZE, BTA_AG_CI_SCO_DATA_EVT);
#endif

    /* call app callback */
    bta_ag_cback_sco(p_scb, BTA_AG_AUDIO_OPEN_EVT);

    p_scb->retry_with_sco_only = FALSE;
#if (BTM_WBS_INCLUDED == TRUE)
    /* reset to mSBC T2 settings as the preferred */
    p_scb->codec_msbc_settings = BTA_AG_SCO_MSBC_SETTINGS_T2;
#endif
}