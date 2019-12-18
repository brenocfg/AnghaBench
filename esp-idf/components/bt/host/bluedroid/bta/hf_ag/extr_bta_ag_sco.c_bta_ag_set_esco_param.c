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
typedef  int /*<<< orphan*/  tBTM_ESCO_PARAMS ;
struct TYPE_3__ {int /*<<< orphan*/  params; scalar_t__ param_updated; } ;
struct TYPE_4__ {TYPE_1__ sco; } ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*) ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 TYPE_2__ bta_ag_cb ; 

void bta_ag_set_esco_param(BOOLEAN set_reset, tBTM_ESCO_PARAMS *param)
{
    if(set_reset == FALSE)    /* reset the parameters to default */
    {
        bta_ag_cb.sco.param_updated = FALSE;
        APPL_TRACE_DEBUG("bta_ag_set_esco_param : Resetting ESCO parameters to default");
    }
    else
    {
        bta_ag_cb.sco.param_updated = TRUE;
        bta_ag_cb.sco.params = *param;
        APPL_TRACE_DEBUG("bta_ag_set_esco_param : Setting ESCO parameters");
    }
}