#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ sco_codec; scalar_t__ codec_msbc_settings; scalar_t__ svc_conn; } ;
typedef  TYPE_1__ tBTA_AG_SCB ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 scalar_t__ BTA_AG_SCO_MSBC_SETTINGS_T1 ; 
 scalar_t__ BTM_SCO_CODEC_MSBC ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN bta_ag_attempt_msbc_safe_settings(tBTA_AG_SCB *p_scb)
{
    if (p_scb->svc_conn && p_scb->sco_codec == BTM_SCO_CODEC_MSBC &&
        p_scb->codec_msbc_settings == BTA_AG_SCO_MSBC_SETTINGS_T1)
        return TRUE;
    else
        return FALSE;
}