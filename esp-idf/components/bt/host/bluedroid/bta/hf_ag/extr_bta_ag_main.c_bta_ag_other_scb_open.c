#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ state; scalar_t__ in_use; } ;
typedef  TYPE_1__ tBTA_AG_SCB ;
struct TYPE_5__ {TYPE_1__* scb; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*) ; 
 int BTA_AG_NUM_SCB ; 
 scalar_t__ BTA_AG_OPEN_ST ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_3__ bta_ag_cb ; 

BOOLEAN bta_ag_other_scb_open(tBTA_AG_SCB *p_curr_scb)
{
    tBTA_AG_SCB     *p_scb = &bta_ag_cb.scb[0];

    for (int i = 0; i < BTA_AG_NUM_SCB; i++, p_scb++) {
        if (p_scb->in_use && p_scb != p_curr_scb && p_scb->state == BTA_AG_OPEN_ST) {
            return TRUE;
        }
    }
    /* no other scb found */
    APPL_TRACE_DEBUG("No other ag scb open");
    return FALSE;
}