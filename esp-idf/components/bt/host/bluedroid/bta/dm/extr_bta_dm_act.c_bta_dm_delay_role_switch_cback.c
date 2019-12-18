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
typedef  int /*<<< orphan*/  TIMER_LIST_ENT ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_EVENT (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bta_dm_adjust_roles (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bta_dm_delay_role_switch_cback(TIMER_LIST_ENT *p_tle)
{
    UNUSED(p_tle);
    APPL_TRACE_EVENT("bta_dm_delay_role_switch_cback: initiating Delayed RS");
    bta_dm_adjust_roles (FALSE);
}