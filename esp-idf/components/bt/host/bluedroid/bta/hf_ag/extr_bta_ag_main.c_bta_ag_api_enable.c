#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  parse_mode; int /*<<< orphan*/  (* p_cback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_9__ {TYPE_2__ api_enable; } ;
typedef  TYPE_3__ tBTA_AG_DATA ;
typedef  int /*<<< orphan*/  tBTA_AG_CB ;
struct TYPE_10__ {int /*<<< orphan*/  (* p_cback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;TYPE_1__* scb; int /*<<< orphan*/  msbc_enabled; int /*<<< orphan*/  parse_mode; } ;
struct TYPE_7__ {int /*<<< orphan*/  negotiated_codec; } ;

/* Variables and functions */
 int /*<<< orphan*/  AG_VOICE_SETTINGS ; 
 int /*<<< orphan*/  BTA_AG_ENABLE_EVT ; 
 int /*<<< orphan*/  BTA_ID_AG ; 
 int /*<<< orphan*/  BTM_SCO_CODEC_CVSD ; 
 int /*<<< orphan*/  BTM_SCO_CODEC_MSBC ; 
 int /*<<< orphan*/  BTM_WriteVoiceSettings (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_4__ bta_ag_cb ; 
 int /*<<< orphan*/  bta_ag_collision_cback ; 
 int /*<<< orphan*/  bta_ag_version ; 
 int /*<<< orphan*/  bta_sys_collision_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bta_ag_api_enable(tBTA_AG_DATA *p_data)
{
    /* initialize control block */
    memset(&bta_ag_cb, 0, sizeof(tBTA_AG_CB));
    /* store callback function */
    bta_ag_cb.p_cback = p_data->api_enable.p_cback;
    bta_ag_cb.parse_mode = p_data->api_enable.parse_mode;
    /* check if mSBC support enabled */
    if (strcmp(bta_ag_version, "1.6") == 0) {
        bta_ag_cb.msbc_enabled = TRUE;
        bta_ag_cb.scb->negotiated_codec = BTM_SCO_CODEC_MSBC;
    } else{
        bta_ag_cb.msbc_enabled = FALSE;
        bta_ag_cb.scb->negotiated_codec = BTM_SCO_CODEC_CVSD;
    }

    /* set deault setting for eSCO/SCO */
    BTM_WriteVoiceSettings(AG_VOICE_SETTINGS);
    bta_sys_collision_register (BTA_ID_AG, bta_ag_collision_cback);
    /* call callback with enable event */
    (*bta_ag_cb.p_cback)(BTA_AG_ENABLE_EVT, NULL);
}