#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTA_AG_SCB ;
typedef  int /*<<< orphan*/  tBTA_AG_DATA ;
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_3__ {int /*<<< orphan*/ * p_curr_scb; } ;
struct TYPE_4__ {TYPE_1__ sco; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_AG_SCO_OPEN_E ; 
 int /*<<< orphan*/  BTA_AG_SCO_XFER_E ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 TYPE_2__ bta_ag_cb ; 
 int /*<<< orphan*/  bta_ag_sco_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void bta_ag_sco_open(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data)
{
    UINT8 event;
    UNUSED(p_data);

    /* if another scb using sco, this is a transfer */
    if (bta_ag_cb.sco.p_curr_scb != NULL && bta_ag_cb.sco.p_curr_scb != p_scb)
    {
        event = BTA_AG_SCO_XFER_E;
    }
    /* else it is an open */
    else
    {
        event = BTA_AG_SCO_OPEN_E;
    }

    bta_ag_sco_event(p_scb, event);
}