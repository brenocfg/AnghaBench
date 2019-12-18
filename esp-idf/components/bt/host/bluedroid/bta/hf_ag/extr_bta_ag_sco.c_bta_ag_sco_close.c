#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ sco_idx; } ;
typedef  TYPE_2__ tBTA_AG_SCB ;
typedef  int /*<<< orphan*/  tBTA_AG_DATA ;
struct TYPE_6__ {scalar_t__ state; } ;
struct TYPE_8__ {TYPE_1__ sco; } ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*,scalar_t__) ; 
 int /*<<< orphan*/  BTA_AG_SCO_CLOSE_E ; 
 scalar_t__ BTA_AG_SCO_CODEC_ST ; 
 scalar_t__ BTM_INVALID_SCO_INDEX ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 TYPE_5__ bta_ag_cb ; 
 int /*<<< orphan*/  bta_ag_sco_event (TYPE_2__*,int /*<<< orphan*/ ) ; 

void bta_ag_sco_close(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data)
{
    UNUSED(p_data);

    /* if scb is in use */
#if (BTM_WBS_INCLUDED == TRUE )
    /* sco_idx is not allocated in SCO_CODEC_ST, we still need to move to listening state. */
    if ((p_scb->sco_idx != BTM_INVALID_SCO_INDEX) || (bta_ag_cb.sco.state == BTA_AG_SCO_CODEC_ST))
#else
    if (p_scb->sco_idx != BTM_INVALID_SCO_INDEX)
#endif
    {
        APPL_TRACE_DEBUG("bta_ag_sco_close: sco_inx = %d", p_scb->sco_idx);
        bta_ag_sco_event(p_scb, BTA_AG_SCO_CLOSE_E);
    }
}