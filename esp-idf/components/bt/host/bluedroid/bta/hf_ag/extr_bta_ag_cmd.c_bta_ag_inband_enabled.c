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
struct TYPE_4__ {scalar_t__ inband_enabled; } ;
typedef  TYPE_1__ tBTA_AG_SCB ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bta_ag_other_scb_open (TYPE_1__*) ; 

BOOLEAN bta_ag_inband_enabled(tBTA_AG_SCB *p_scb)
{
    /* if feature is enabled and no other scbs connected */
    if (p_scb->inband_enabled && !bta_ag_other_scb_open(p_scb)) {
        return TRUE;
    } else {
        return FALSE;
    }
}