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
typedef  int /*<<< orphan*/  tBTA_AG_SCB ;
struct TYPE_3__ {scalar_t__ param; } ;
typedef  TYPE_1__ TIMER_LIST_ENT ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_AG_AUDIO_CLOSE_EVT ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  bta_ag_cback_sco (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_ag_sco_codec_nego (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bta_ag_cn_timer_cback (TIMER_LIST_ENT *p_tle)
{
    tBTA_AG_SCB *p_scb;

    if (p_tle)
    {
        p_scb = (tBTA_AG_SCB *)p_tle->param;

        if (p_scb)
        {
            /* Announce that codec negotiation failed. */
            bta_ag_sco_codec_nego(p_scb, FALSE);

            /* call app callback */
            bta_ag_cback_sco(p_scb, BTA_AG_AUDIO_CLOSE_EVT);
        }
    }
}