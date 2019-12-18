#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  tBTA_AG_SCB ;
typedef  int /*<<< orphan*/  tBTA_AG_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_AG_SCO_CI_DATA_E ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bta_ag_sco_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void bta_ag_ci_sco_data(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data)
{
    UNUSED(p_scb);
    UNUSED(p_data);

#if (BTM_SCO_HCI_INCLUDED == TRUE )
    bta_ag_sco_event(p_scb, BTA_AG_SCO_CI_DATA_E);
#endif
}