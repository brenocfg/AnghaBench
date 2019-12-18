#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ state; } ;
typedef  TYPE_1__ tBTA_AG_SCB ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  APPL_TRACE_ERROR (char*) ; 
 scalar_t__ BTA_AG_INIT_ST ; 
 scalar_t__ BTA_AG_OPENING_ST ; 
 int /*<<< orphan*/  bta_ag_scb_to_idx (TYPE_1__*) ; 
 int /*<<< orphan*/  bta_ag_start_open (TYPE_1__*,int /*<<< orphan*/ *) ; 

void bta_ag_resume_open (tBTA_AG_SCB *p_scb)
{
    if (p_scb) {
        APPL_TRACE_DEBUG ("bta_ag_resume_open, Handle(%d)", bta_ag_scb_to_idx(p_scb));
        /* resume opening process.  */
        if (p_scb->state == BTA_AG_INIT_ST) {
            p_scb->state = BTA_AG_OPENING_ST;
            bta_ag_start_open (p_scb, NULL);
        }
    } else {
        APPL_TRACE_ERROR ("bta_ag_resume_open, Null p_scb");
    }
}