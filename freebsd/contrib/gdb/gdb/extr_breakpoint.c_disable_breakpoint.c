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
struct breakpoint {scalar_t__ type; scalar_t__ enable_state; int /*<<< orphan*/  number; } ;

/* Variables and functions */
 scalar_t__ bp_disabled ; 
 scalar_t__ bp_permanent ; 
 scalar_t__ bp_watchpoint_scope ; 
 int /*<<< orphan*/  breakpoint_modify_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_duplicates (struct breakpoint*) ; 
 int /*<<< orphan*/  modify_breakpoint_hook (struct breakpoint*) ; 

void
disable_breakpoint (struct breakpoint *bpt)
{
  /* Never disable a watchpoint scope breakpoint; we want to
     hit them when we leave scope so we can delete both the
     watchpoint and its scope breakpoint at that time.  */
  if (bpt->type == bp_watchpoint_scope)
    return;

  /* You can't disable permanent breakpoints.  */
  if (bpt->enable_state == bp_permanent)
    return;

  bpt->enable_state = bp_disabled;

  check_duplicates (bpt);

  if (modify_breakpoint_hook)
    modify_breakpoint_hook (bpt);
  breakpoint_modify_event (bpt->number);
}