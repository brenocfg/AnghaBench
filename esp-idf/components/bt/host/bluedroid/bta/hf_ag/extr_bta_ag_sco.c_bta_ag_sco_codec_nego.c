#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  codec_updated; } ;
typedef  TYPE_1__ tBTA_AG_SCB ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_AG_SCO_CLOSE_E ; 
 int /*<<< orphan*/  BTA_AG_SCO_CN_DONE_E ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  bta_ag_sco_event (TYPE_1__*,int /*<<< orphan*/ ) ; 

void bta_ag_sco_codec_nego(tBTA_AG_SCB *p_scb, BOOLEAN result)
{
    if(result == TRUE)
    {
        /* Subsequent sco connection will skip codec negotiation */
        p_scb->codec_updated = FALSE;

        bta_ag_sco_event(p_scb, BTA_AG_SCO_CN_DONE_E);
    }
    else    /* codec negotiation failed */
        bta_ag_sco_event(p_scb, BTA_AG_SCO_CLOSE_E);
}