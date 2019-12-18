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
struct TYPE_7__ {int /*<<< orphan*/  (* p_cback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_9__ {TYPE_1__ api_enable; } ;
typedef  TYPE_3__ tBTA_HF_CLIENT_DATA ;
typedef  int /*<<< orphan*/  tBTA_HF_CLIENT_CB ;
struct TYPE_8__ {int /*<<< orphan*/  negotiated_codec; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* p_cback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;TYPE_2__ scb; int /*<<< orphan*/  msbc_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  AG_VOICE_SETTINGS ; 
 int /*<<< orphan*/  BTA_HF_CLIENT_ENABLE_EVT ; 
 int /*<<< orphan*/  BTA_ID_HS ; 
 int /*<<< orphan*/  BTM_SCO_CODEC_CVSD ; 
 int /*<<< orphan*/  BTM_WriteVoiceSettings (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_4__ bta_hf_client_cb ; 
 int /*<<< orphan*/  bta_hf_client_collision_cback ; 
 int /*<<< orphan*/  bta_hf_client_version ; 
 int /*<<< orphan*/  bta_sys_collision_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bta_hf_client_api_enable(tBTA_HF_CLIENT_DATA *p_data)
{
    /* initialize control block */
    memset(&bta_hf_client_cb, 0, sizeof(tBTA_HF_CLIENT_CB));

    /* store callback function */
    bta_hf_client_cb.p_cback = p_data->api_enable.p_cback;

    /* check if mSBC support enabled */
    if (strcmp(bta_hf_client_version, "1.6") == 0) {
        bta_hf_client_cb.msbc_enabled = TRUE;
    } else{
        bta_hf_client_cb.msbc_enabled = FALSE;
    }

    bta_hf_client_cb.scb.negotiated_codec = BTM_SCO_CODEC_CVSD;

    /* set same setting as AG does */
    BTM_WriteVoiceSettings(AG_VOICE_SETTINGS);

    bta_sys_collision_register (BTA_ID_HS, bta_hf_client_collision_cback);

    /* call callback with enable event */
    (*bta_hf_client_cb.p_cback)(BTA_HF_CLIENT_ENABLE_EVT, NULL);
}