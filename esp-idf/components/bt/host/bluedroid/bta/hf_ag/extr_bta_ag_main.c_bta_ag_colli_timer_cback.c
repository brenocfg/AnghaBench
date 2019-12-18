#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  colli_tmr_on; } ;
typedef  TYPE_1__ tBTA_AG_SCB ;
struct TYPE_6__ {scalar_t__ param; } ;
typedef  TYPE_2__ TIMER_LIST_ENT ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  bta_ag_resume_open (TYPE_1__*) ; 

__attribute__((used)) static void bta_ag_colli_timer_cback (TIMER_LIST_ENT *p_tle)
{
    tBTA_AG_SCB *p_scb;

    APPL_TRACE_DEBUG ("bta_ag_colli_timer_cback");
    if (p_tle) {
        p_scb = (tBTA_AG_SCB *)p_tle->param;
        if (p_scb) {
            p_scb->colli_tmr_on = FALSE;
            /* If the peer haven't opened AG connection     */
            /* we will restart opening process.             */
            bta_ag_resume_open (p_scb);
        }
    }
}