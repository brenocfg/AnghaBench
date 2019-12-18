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
struct TYPE_4__ {int /*<<< orphan*/  in_use; } ;
typedef  TYPE_1__ tBTA_AG_SCB ;
typedef  int UINT16 ;
struct TYPE_5__ {TYPE_1__* scb; } ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*,int) ; 
 int /*<<< orphan*/  APPL_TRACE_WARNING (char*,int) ; 
 int BTA_AG_NUM_SCB ; 
 TYPE_3__ bta_ag_cb ; 

tBTA_AG_SCB *bta_ag_scb_by_idx(UINT16 idx)
{
    tBTA_AG_SCB     *p_scb;
    /* verify index */
    if (idx > 0 && idx <= BTA_AG_NUM_SCB) {
        p_scb = &bta_ag_cb.scb[idx - 1];
        if (!p_scb->in_use) {
            p_scb = NULL;
            APPL_TRACE_WARNING("ag scb idx %d not allocated", idx);
        }
    } else {
        p_scb = NULL;
        APPL_TRACE_DEBUG("ag scb idx %d out of range", idx);
    }
    return p_scb;
}