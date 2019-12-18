#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ state; scalar_t__ in_use; } ;
typedef  TYPE_1__ tBTA_AG_SCB ;
typedef  scalar_t__ UINT8 ;
struct TYPE_6__ {TYPE_1__* scb; } ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*) ; 
 scalar_t__ BTA_AG_INIT_ST ; 
 scalar_t__ BTA_AG_NUM_SCB ; 
 TYPE_4__ bta_ag_cb ; 

tBTA_AG_SCB *bta_ag_get_other_idle_scb (tBTA_AG_SCB *p_curr_scb)
{
    tBTA_AG_SCB     *p_scb = &bta_ag_cb.scb[0];
    UINT8   xx;

    for (xx = 0; xx < BTA_AG_NUM_SCB; xx++, p_scb++) {
        if (p_scb->in_use && (p_scb != p_curr_scb) && (p_scb->state == BTA_AG_INIT_ST)) {
            return p_scb;
        }
    }
    /* no other scb found */
    APPL_TRACE_DEBUG("bta_ag_get_other_idle_scb: No idle AG scb");
    return NULL;
}